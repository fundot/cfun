#include "fun_str.h"
#include "fun_memory.h"

#include <string.h>

struct fun_type fun_str_type = { .name = "str",
				 .create = (fun_constructor) fun_str_create,
				 .destroy = (fun_destructor) fun_str_destroy,
				 .traverse = NULL,
				 .hash = (fun_hasher) fun_str_hash,
				 .is_equal = (fun_comparison) fun_str_is_equal,
				 .to_repr = (fun_to_repr) fun_str_to_repr,
				 .to_str = (fun_to_str) fun_str_to_str };

struct fun_str *fun_str_create(char *c_str)
{
	struct fun_str *str = fun_malloc(sizeof(*str));
	FUN_OBJECT_CAST(str)->type = &fun_str_type;
	str->c_str = fun_malloc((strlen(c_str) + 1) * sizeof(*str->c_str));
	strcpy(str->c_str, c_str);
	return str;
}

void fun_str_destroy(struct fun_str *self)
{
	fun_free(self->c_str);
	fun_free(self);
}

size_t fun_str_hash(struct fun_str *self)
{
	size_t hash = 5381;
	const char *str = self->c_str;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

int fun_str_is_equal(struct fun_str *self, struct fun_object *other)
{
	if (other->type != &fun_str_type)
		return 0;
	struct fun_str *str = (struct fun_str *) other;
	return strcmp(self->c_str, str->c_str) == 0;
}

struct fun_str *fun_str_concatenate(struct fun_str *lhs, struct fun_str *rhs)
{
	char c_str[strlen(lhs->c_str) + strlen(rhs->c_str) + 1];
	strcpy(c_str, lhs->c_str);
	strcat(c_str, rhs->c_str);
	return (struct fun_str *) fun_create(&fun_str_type, c_str);
}

static void join_help(struct fun_str *self, void *arg)
{
	struct fun_str **str_ptr = arg;
	*str_ptr = fun_str_concatenate(*str_ptr, self);
}

struct fun_str *fun_str_join(struct fun_object *iterable)
{
	struct fun_str *str = (struct fun_str *) fun_create(&fun_str_type, "");
	iterable->type->traverse(iterable, (fun_visitor) join_help, &str);
	return str;
}

struct fun_str *fun_str_to_repr(struct fun_str *self)
{
	struct fun_str *repr =
		(struct fun_str *) fun_create(&fun_str_type, "\"");
	repr = fun_str_concatenate(repr, self);
	repr = fun_str_concatenate(
		repr, (struct fun_str *) fun_create(&fun_str_type, "\""));
	return repr;
}

struct fun_str *fun_str_to_str(struct fun_str *self)
{
	return self;
}
