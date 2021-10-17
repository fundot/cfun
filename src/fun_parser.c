#include "fun_parser.h"
#include "fun_dict.h"
#include "fun_list.h"
#include "fun_number.h"
#include "fun_symbol.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int is_punctuation(int ch)
{
	return ispunct(ch) && ch != '_' && ch != ',';
}

static int is_whitespace(int ch)
{
	return isspace(ch) || ch == ',';
}

static struct fun_list *parse_list(const char *str)
{
	struct fun_list *lst =
		(struct fun_list *) fun_create(&fun_list_type, NULL);
	if (str[1] == ']')
		return lst;
	for (size_t i = 1; str[i] != '\0'; ++i) {
		fun_list_push(lst, fun_parse(str + i));
		while (!is_whitespace(str[++i])) {}
		if (str[i] == ']')
			return lst;
	}
	return lst;
}

static struct fun_dict *parse_dict(const char *str)
{
	struct fun_dict *dct =
		(struct fun_dict *) fun_create(&fun_dict_type, NULL);
	if (str[1] == '}')
		return dct;
	for (size_t i = 1; str[i] != '\0'; ++i) {
		struct fun_object *key = fun_parse(str + i);
		while (!is_whitespace(str[++i])) {}
		struct fun_object *value = fun_parse(str + i);
		while (!is_whitespace(str[++i])) {}
		fun_dict_set(dct, key, value);
		if (str[i] == '}')
			return dct;
	}
	return dct;
}

static struct fun_number *parse_number(const char *str)
{
	int i;
	double f;
	sscanf(str, "%lf", &f);
	i = (int) f;
	if (i == f)
		return (struct fun_number *) fun_create(&fun_int_type, &i);
	return (struct fun_number *) fun_create(&fun_float_type, &f);
}

static struct fun_symbol *parse_symbol(const char *str)
{
	char buf[128 + 1] = { '\0' };
	size_t i = 0;
	while (!is_punctuation(str[i]) && !is_whitespace(str[i])) {
		buf[i] = str[i];
		++i;
	}
	struct fun_str *s = (struct fun_str *) fun_create(&fun_str_type, buf);
	return (struct fun_symbol *) fun_create(&fun_symbol_type, (void *) s);
}

struct fun_object *fun_parse(const char *str)
{
	while (is_whitespace(str[0]))
		++str;
	if (str[0] == '[')
		return (struct fun_object *) parse_list(str);
	if (str[0] == '{')
		return (struct fun_object *) parse_dict(str);
	if (str[0] == '-' || isdigit(str[0]))
		return (struct fun_object *) parse_number(str);
	return (struct fun_object *) parse_symbol(str);
}
