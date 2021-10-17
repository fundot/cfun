#include "fun_io.h"
#include "fun_str.h"

#include <stdio.h>

void fun_print(struct fun_object *obj)
{
	fun_to_str to_str = obj->type->to_str;
	if (to_str == NULL)
		to_str = obj->type->to_repr;
	if (to_str == NULL)
		return;
	struct fun_object *str_obj = to_str(obj);
	if (str_obj->type != &fun_str_type)
		return;
	struct fun_str *str = (struct fun_str *) str_obj;
	printf("%s", str->c_str);
}
