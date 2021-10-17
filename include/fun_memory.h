#ifndef FUN_MEMORY_H
#define FUN_MEMORY_H

#include <stddef.h>

void *fun_malloc(size_t size);

void *fun_calloc(size_t num, size_t size);

void *fun_realloc(void *ptr, size_t size);

void fun_free(void *ptr);

#endif
