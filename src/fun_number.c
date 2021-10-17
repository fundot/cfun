#include "fun_number.h"
#include "fun_memory.h"

#include <stdio.h>

struct fun_type fun_int_type = { .name = "int",
				 .create = (fun_constructor) fun_int_create,
				 .destroy = (fun_destructor) fun_int_destroy,
				 .traverse = NULL,
				 .hash = (fun_hasher) fun_int_hash,
				 .is_equal = (fun_comparison) fun_int_is_equal,
				 .to_repr = (fun_to_repr) fun_int_to_repr,
				 .to_str = NULL };

struct fun_int *fun_int_create(void *arg)
{
	struct fun_int *num = fun_malloc(sizeof(*num));
	FUN_OBJECT_CAST(num)->type = &fun_int_type;
	num->num = *(int *) arg;
	return num;
}

void fun_int_destroy(struct fun_int *self)
{
	fun_free(self);
}

size_t fun_int_hash(struct fun_int *self)
{
	return self->num;
}

int fun_int_is_equal(struct fun_int *self, struct fun_object *other)
{
	if (other->type == &fun_int_type)
		return self->num == ((struct fun_int *) other)->num;
	if (other->type == &fun_float_type)
		return self->num == ((struct fun_float *) other)->num;
	return 0;
}

struct fun_str *fun_int_to_repr(struct fun_int *self)
{
	int buf_size = snprintf(NULL, 0, "%d", self->num) + 1;
	char buf[buf_size];
	snprintf(buf, buf_size, "%d", self->num);
	return (struct fun_str *) fun_create(&fun_str_type, buf);
}

struct fun_type fun_float_type = { .name = "float",
				   .create = (fun_constructor) fun_float_create,
				   .destroy =
					   (fun_destructor) fun_float_destroy,
				   .traverse = NULL,
				   .hash = (fun_hasher) fun_float_hash,
				   .is_equal =
					   (fun_comparison) fun_float_is_equal,
				   .to_repr = (fun_to_repr) fun_float_to_repr,
				   .to_str = NULL };

struct fun_float *fun_float_create(void *arg)
{
	struct fun_float *num = fun_malloc(sizeof(*num));
	FUN_OBJECT_CAST(num)->type = &fun_float_type;
	num->num = *(double *) arg;
	return num;
}

void fun_float_destroy(struct fun_float *self)
{
	fun_free(self);
}

size_t fun_float_hash(struct fun_float *self)
{
	return (size_t) self;
}

int fun_float_is_equal(struct fun_float *self, struct fun_object *other)
{
	if (other->type == &fun_int_type)
		return self->num == ((struct fun_int *) other)->num;
	if (other->type == &fun_float_type)
		return self->num == ((struct fun_float *) other)->num;
	return 0;
}

struct fun_str *fun_float_to_repr(struct fun_float *self)
{
	int buf_size = snprintf(NULL, 0, "%f", self->num) + 1;
	char buf[buf_size];
	snprintf(buf, buf_size, "%f", self->num);
	return (struct fun_str *) fun_create(&fun_str_type, buf);
}
