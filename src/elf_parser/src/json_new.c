#include "utils.h"
#include "json_new.h"


void
init_prop(object *obj, void *data, uint8_t data_type)
{
	obj->data_type = data_type;
	obj->child[0] = data;
	obj->child[1] = NULL;
	obj->len = 0;
}


int8_t
init_parent(object *obj, size_t len)
{
	object **children = malloc(len * sizeof(object *));

	if (children == NULL) {
		return -1;
	}

	for (register size_t i = 0; i < len; i++) {
		children[i] = NULL;
	}

	obj->child[0] = NULL;
	obj->child[1] = (void *) children;
	obj->len = len;

	return 0;
}


object *
new_obj(const char *key, uint8_t type, ...)
{
	object *obj = malloc(sizeof(object));
	va_list args;

	if (type > 1 || obj == NULL) {
		return NULL;
	}

	va_start(args, type);

	obj->hash_key = create_hash_key(key);
	obj->child_type = type;

	if (type == 0) {
		init_prop(obj, va_arg(args, void *), (uint8_t) va_arg(args, int));
	} else if (type == 1) {
		if (init_parent(obj, va_arg(args, size_t)) < 0) {
			free(obj);
			return NULL;
		}
	}

	va_end(args);

	return obj;
}
