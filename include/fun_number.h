#ifndef FUN_NUMBER_H
#define FUN_NUMBER_H

#include "fun_str.h"

#define FUN_NUMBER_HEAD struct fun_number num_base;

struct fun_number {
	FUN_OBJECT_HEAD
};

extern struct fun_type fun_int_type;

struct fun_int {
	FUN_NUMBER_HEAD
	int num;
};

struct fun_int *fun_int_create(void *arg);

void fun_int_destroy(struct fun_int *self);

size_t fun_int_hash(struct fun_int *self);

int fun_int_is_equal(struct fun_int *self, struct fun_object *other);

struct fun_str *fun_int_to_repr(struct fun_int *self);

extern struct fun_type fun_float_type;

struct fun_float {
	FUN_NUMBER_HEAD
	double num;
};

struct fun_float *fun_float_create(void *arg);

void fun_float_destroy(struct fun_float *self);

size_t fun_float_hash(struct fun_float *self);

int fun_float_is_equal(struct fun_float *self, struct fun_object *other);

struct fun_str *fun_float_to_repr(struct fun_float *self);

#endif
