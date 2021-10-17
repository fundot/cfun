#include "fun_gc.h"

static struct fun_object *root_set = NULL;

static struct fun_object *white_set = NULL;

static struct fun_object *gray_set = NULL;

static struct fun_object *black_set = NULL;

static int white = 0;

void fun_gc_push_root(struct fun_object *root)
{
	root->prev = NULL;
	root->next = root_set;
	if (root_set != NULL)
		root_set->prev = root;
	root_set = root;
}

struct fun_object *fun_gc_pop_root()
{
	struct fun_object *root = root_set;
	if (root->next != NULL)
		root_set->next->prev = NULL;
	root->next = NULL;
	root_set = root->next;
	return root;
}

struct fun_object *fun_create(struct fun_type *type, void *arg)
{
	struct fun_object *obj = type->create(arg);
	obj->color = white;
	obj->next = white_set;
	if (white_set != NULL)
		white_set->prev = obj;
	white_set = obj;
	obj->prev = NULL;
	return obj;
}

static void move_to_gray(struct fun_object *obj, void *arg)
{
	if (obj->color != white)
		return;
	if (obj->prev != NULL)
		obj->prev->next = obj->next;
	else
		white_set = obj->next;
	if (obj->next != NULL)
		obj->next->prev = obj->prev;
	obj->prev = NULL;
	obj->next = gray_set;
	gray_set = obj;
}

static void move_to_black(struct fun_object *obj, void *arg)
{
	if (obj->prev != NULL)
		obj->prev->next = obj->next;
	else
		gray_set = obj->next;
	if (obj->next != NULL)
		obj->next->prev = obj->prev;
	obj->prev = NULL;
	obj->next = black_set;
	black_set = obj;
}

void fun_gc_collect()
{
	struct fun_object *curr = root_set;
	while (curr != NULL) {
		curr->type->traverse(curr, move_to_gray, NULL);
		curr = curr->next;
	}
	while (gray_set != NULL) {
		curr = gray_set;
		move_to_black(gray_set, NULL);
		curr->type->traverse(curr, move_to_gray, NULL);
	}
	while (white_set != NULL) {
		curr = white_set;
		white_set = white_set->next;
		curr->type->destroy(curr);
	}
	white_set = black_set;
	black_set = NULL;
	white = !white;
}
