#ifndef FUN_OBJECT_H
#define FUN_OBJECT_H

#include <stddef.h>

typedef struct fun_object *(*fun_constructor)(void *arg);

typedef void (*fun_destructor)(struct fun_object *self);

typedef void (*fun_visitor)(struct fun_object *obj, void *arg);

typedef void (*fun_traversal)(struct fun_object *self,
			      fun_visitor visit,
			      void *arg);

typedef size_t (*fun_hasher)(struct fun_object *self);

typedef int *(*fun_comparison)(struct fun_object *self,
			       struct fun_object *other);

typedef struct fun_object *(*fun_to_repr)(struct fun_object *self);

typedef struct fun_object *(*fun_to_str)(struct fun_object *self);

struct fun_type {
	const char *name;
	fun_constructor create;
	fun_destructor destroy;
	fun_traversal traverse;
	fun_hasher hash;
	fun_comparison is_equal;
	fun_to_repr to_repr;
	fun_to_str to_str;
};

#define FUN_OBJECT_GC_HEAD \
	int color; \
	struct fun_object *next; \
	struct fun_object *prev;

#define FUN_OBJECT_HEAD struct fun_object obj_base;

#define FUN_OBJECT_CAST(obj) ((struct fun_object *) obj)

struct fun_object {
	FUN_OBJECT_GC_HEAD
	struct fun_type *type;
};

struct fun_object *fun_create(struct fun_type *type, void *arg);

#endif
