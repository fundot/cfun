#ifndef FUN_STR_H
#define FUN_STR_H

#include "fun_object.h"

extern struct fun_type fun_str_type;

struct fun_str {
	FUN_OBJECT_HEAD
	char *c_str;
};

struct fun_str *fun_str_create(char *str);

void fun_str_destroy(struct fun_str *self);

size_t fun_str_hash(struct fun_str *self);

int fun_str_is_equal(struct fun_str *self, struct fun_object *other);

struct fun_str *fun_str_to_repr(struct fun_str *self);

struct fun_str *fun_str_to_str(struct fun_str *self);

struct fun_str *fun_str_concatenate(struct fun_str *lhs, struct fun_str *rhs);

struct fun_str *fun_str_join(struct fun_object *iterable);

#endif
