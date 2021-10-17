#ifndef FUN_GC_H
#define FUN_GC_H

#include "fun_object.h"

void fun_gc_push_root(struct fun_object *root);

struct fun_object *fun_gc_pop_root();

void fun_gc_collect();

#endif
