#ifndef FUN_SYMBOL_H
#define FUN_SYMBOL_H

#include "fun_str.h"

extern struct fun_type fun_symbol_type;

struct fun_symbol {
	FUN_OBJECT_HEAD
	struct fun_str *str;
};

struct fun_symbol *fun_symbol_create(struct fun_str *str);

void fun_symbol_destroy(struct fun_symbol *self);

size_t fun_symbol_hash(struct fun_symbol *self);

int fun_symbol_is_equal(struct fun_symbol *self, struct fun_object *other);

struct fun_str *fun_symbol_to_repr(struct fun_symbol *self);

#endif
