#ifndef FUN_LIST_H
#define FUN_LIST_H

#include "fun_str.h"

extern struct fun_type fun_list_type;

struct fun_list {
	FUN_OBJECT_HEAD
	struct fun_object **elems;
	size_t capacity;
	size_t size;
};

struct fun_list *fun_list_create(void *arg);

void fun_list_destroy(struct fun_list *self);

void fun_list_push(struct fun_list *self, struct fun_object *obj);

struct fun_object *fun_list_pop(struct fun_list *self);

struct fun_object *fun_list_get(struct fun_list *self, size_t idx);

void fun_list_set(struct fun_list *self, size_t idx, struct fun_object *obj);

void fun_list_traverse(struct fun_list *self, fun_visitor visit, void *arg);

struct fun_str *fun_list_to_repr(struct fun_list *self);

#endif
