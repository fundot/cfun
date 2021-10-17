#include "fun_symbol.h"
#include "fun_memory.h"

#include <string.h>

struct fun_type fun_symbol_type = {
	.name = "symbol",
	.create = (fun_constructor) fun_symbol_create,
	.destroy = (fun_destructor) fun_symbol_destroy,
	.traverse = NULL,
	.hash = (fun_hasher) fun_symbol_hash,
	.is_equal = (fun_comparison) fun_symbol_is_equal,
	.to_repr = (fun_to_repr) fun_symbol_to_repr,
	.to_str = NULL
};

struct fun_symbol *fun_symbol_create(struct fun_str *str)
{
	struct fun_symbol *sym = fun_malloc(sizeof(*sym));
	FUN_OBJECT_CAST(sym)->type = &fun_symbol_type;
	sym->str = fun_str_create(str->c_str);
	return sym;
}

void fun_symbol_destroy(struct fun_symbol *self)
{
	fun_str_destroy(self->str);
	fun_free(self);
}

size_t fun_symbol_hash(struct fun_symbol *self)
{
	return fun_str_hash(self->str);
}

int fun_symbol_is_equal(struct fun_symbol *self, struct fun_object *other)
{
	if (other->type != &fun_symbol_type)
		return 0;
	return fun_str_is_equal(
		self->str,
		(struct fun_object *) ((struct fun_symbol *) other)->str);
}

struct fun_str *fun_symbol_to_repr(struct fun_symbol *self)
{
	return (struct fun_str *) fun_create(&fun_str_type, self->str->c_str);
}
