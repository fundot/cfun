#ifndef FUN_DICT_H
#define FUN_DICT_H

#include "fun_list.h"
#include "fun_str.h"

extern struct fun_type fun_dict_type;

struct fun_dict {
	FUN_OBJECT_HEAD
	struct fun_object **keys;
	struct fun_object **values;
	size_t capacity;
	size_t size;
};

struct fun_dict *fun_dict_create(void *arg);

void fun_dict_destroy(struct fun_dict *self);

void fun_dict_set(struct fun_dict *self,
		  struct fun_object *key,
		  struct fun_object *value);

struct fun_object *fun_dict_remove(struct fun_dict *self,
				   struct fun_object *key);

struct fun_object *fun_dict_get(struct fun_dict *self, struct fun_object *key);

void fun_dict_traverse(struct fun_dict *self, fun_visitor visit, void *arg);

struct fun_str *fun_dict_to_repr(struct fun_dict *self);

#endif
