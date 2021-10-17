#include "fun_list.h"
#include "fun_memory.h"
#include "fun_str.h"

struct fun_type fun_list_type = { .name = "list",
				  .create = (fun_constructor) fun_list_create,
				  .destroy = (fun_destructor) fun_list_destroy,
				  .traverse = (fun_traversal) fun_list_traverse,
				  .hash = NULL,
				  .is_equal = NULL,
				  .to_repr = (fun_to_repr) fun_list_to_repr,
				  .to_str = NULL };

struct fun_list *fun_list_create(void *arg)
{
	struct fun_list *lst = fun_malloc(sizeof(*lst));
	FUN_OBJECT_CAST(lst)->type = &fun_list_type;
	lst->capacity = 1;
	lst->size = 0;
	lst->elems = fun_calloc(lst->capacity, sizeof(*lst->elems));
	return lst;
}

void fun_list_destroy(struct fun_list *self)
{
	fun_free(self->elems);
	fun_free(self);
}

void fun_list_push(struct fun_list *self, struct fun_object *obj)
{
	if (self->size == self->capacity) {
		self->capacity *= 2;
		size_t capacity = self->capacity * sizeof(*self->elems);
		self->elems = fun_realloc(self->elems, capacity);
	}
	self->elems[self->size++] = obj;
}

struct fun_object *fun_list_pop(struct fun_list *self)
{
	return self->elems[--self->size];
}

struct fun_object *fun_list_get(struct fun_list *self, size_t idx)
{
	return self->elems[idx];
}

void fun_list_set(struct fun_list *self, size_t idx, struct fun_object *obj)
{
	self->elems[idx] = obj;
}

void fun_list_traverse(struct fun_list *self, fun_visitor visit, void *arg)
{
	for (size_t i = 0; i < self->size; ++i)
		visit(self->elems[i], arg);
}

struct fun_str *fun_list_to_repr(struct fun_list *self)
{
	struct fun_list *str_builder = fun_list_create(NULL);
	fun_list_push(str_builder, fun_create(&fun_str_type, "["));
	if (self->size == 0) {
		fun_list_push(str_builder, fun_create(&fun_str_type, "]"));
		return fun_str_join((struct fun_object *) str_builder);
	}
	for (size_t i = 0; i < self->size; ++i) {
		struct fun_object *obj = self->elems[i];
		fun_list_push(str_builder, obj->type->to_repr(obj));
		fun_list_push(str_builder, fun_create(&fun_str_type, ", "));
	}
	fun_list_pop(str_builder);
	fun_list_push(str_builder, fun_create(&fun_str_type, "]"));
	return fun_str_join((struct fun_object *) str_builder);
}
