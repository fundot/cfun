#include "fun_dict.h"
#include "fun_memory.h"
#include "fun_str.h"

#define DEFAULT_LOAD_FACTOR 0.75

struct fun_type fun_dict_type = { .name = "dict",
				  .create = (fun_constructor) fun_dict_create,
				  .destroy = (fun_destructor) fun_dict_destroy,
				  .traverse = NULL,
				  .hash = NULL,
				  .is_equal = NULL,
				  .to_repr = (fun_to_repr) fun_dict_to_repr,
				  .to_str = NULL };

struct fun_dict *fun_dict_create(void *arg)
{
	struct fun_dict *dct = fun_malloc(sizeof(*dct));
	FUN_OBJECT_CAST(dct)->type = &fun_dict_type;
	dct->capacity = 1;
	dct->size = 0;
	dct->keys = fun_calloc(dct->capacity, sizeof(*dct->keys));
	dct->values = fun_calloc(dct->capacity, sizeof(*dct->values));
	return dct;
}

void fun_dict_destroy(struct fun_dict *self)
{
	fun_free(self->keys);
	fun_free(self->values);
	fun_free(self);
}

static void fun_dict_set_directly(struct fun_dict *self,
				  struct fun_object *key,
				  struct fun_object *value)
{
	size_t i = key->type->hash(key) % self->capacity;
	while (self->keys[i] != NULL) {
		if (key->type->is_equal(key, self->keys[i])) {
			self->values[i] = value;
			return;
		}
		if (i == self->capacity - 1)
			i = 0;
		else
			++i;
	}
	self->keys[i] = key;
	self->values[i] = value;
	++self->size;
}

void fun_dict_set(struct fun_dict *self,
		  struct fun_object *key,
		  struct fun_object *value)
{
	if ((double) self->size / self->capacity >= DEFAULT_LOAD_FACTOR) {
		struct fun_object **old_keys = self->keys;
		struct fun_object **old_values = self->values;
		size_t old_capacity = self->capacity;
		size_t old_size = self->size;
		self->capacity *= 2;
		self->keys = fun_calloc(self->capacity, sizeof(*self->keys));
		self->values =
			fun_calloc(self->capacity, sizeof(*self->values));
		for (size_t i = 0; i < old_capacity; ++i) {
			if (old_keys[i] == NULL)
				continue;
			fun_dict_set_directly(self, old_keys[i], old_values[i]);
			self->size = old_size;
		}
		fun_free(old_keys);
		fun_free(old_values);
	}
	fun_dict_set_directly(self, key, value);
}

struct fun_object *fun_dict_remove(struct fun_dict *self,
				   struct fun_object *key)
{
	return NULL;
}

struct fun_object *fun_dict_get(struct fun_dict *self, struct fun_object *key)
{
	size_t i = key->type->hash(key) % self->capacity;
	while (self->keys[i] != NULL) {
		if (key->type->is_equal(key, self->keys[i]))
			return self->values[i];
		if (i == self->capacity - 1)
			i = 0;
		else
			++i;
	}
	return NULL;
}

void fun_dict_traverse(struct fun_dict *self, fun_visitor visit, void *arg)
{
	for (size_t i = 0; i < self->capacity; ++i) {
		if (self->keys[i] == NULL)
			continue;
		visit(self->keys[i], arg);
		visit(self->values[i], arg);
	}
}

struct fun_str *fun_dict_to_repr(struct fun_dict *self)
{
	struct fun_list *str_builder = fun_list_create(NULL);
	fun_list_push(str_builder, fun_create(&fun_str_type, "{"));
	if (self->size == 0) {
		fun_list_push(str_builder, fun_create(&fun_str_type, "}"));
		return fun_str_join((struct fun_object *) str_builder);
	}
	for (size_t i = 0; i < self->capacity; ++i) {
		struct fun_object *key = self->keys[i];
		if (key == NULL)
			continue;
		fun_list_push(str_builder, key->type->to_repr(key));
		fun_list_push(str_builder, fun_create(&fun_str_type, ": "));
		struct fun_object *value = self->values[i];
		fun_list_push(str_builder, value->type->to_repr(value));
		fun_list_push(str_builder, fun_create(&fun_str_type, ", "));
	}
	fun_list_pop(str_builder);
	fun_list_push(str_builder, fun_create(&fun_str_type, "}"));
	return fun_str_join((struct fun_object *) str_builder);
}
