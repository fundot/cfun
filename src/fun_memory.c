#include <stdlib.h>

void *fun_malloc(size_t size)
{
	return malloc(size);
}

void *fun_calloc(size_t num, size_t size)
{
	return calloc(num, size);
}

void *fun_realloc(void *ptr, size_t size)
{
	return realloc(ptr, size);
}

void fun_free(void *ptr)
{
	free(ptr);
}
