#include "fundot.h"

#include <stdio.h>

int main(void)
{
	char input[1024] = { '\0' };
	fgets(input, 1024, stdin);
	printf("%s", input);
	struct fun_object *obj = fun_parse(input);
	fun_print(obj);
	printf("\n");
	fun_gc_collect();
	return 0;
}
