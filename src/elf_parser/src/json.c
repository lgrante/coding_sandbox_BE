#include "utils.h"
#include "json.h"


void
init_prop(object_t *obj, void *data, uint8_t data_type)
{
	obj->data_type = data_type;
	obj->child[0] = data;
	obj->child[1] = NULL;
	obj->len = 0;
}


int8_t
init_parent(object_t *obj, size_t len)
{
	object_t **children = malloc(len * sizeof(object_t *));

	THROW_IF(children, INIT_CHILD_FAILED, -1);

	for (register size_t i = 0; i < len; i++) {
		children[i] = NULL;
	}

	obj->child[0] = NULL;
	obj->child[1] = (void *) children;
	obj->len = len;

	return 0;
}


object_t *
new_obj(const char *key, uint8_t type, ...)
{
	object_t *obj = malloc(sizeof(object_t));
	va_list args;

	THROW_IF(type == 0 || type == 1, BAD_DATA_TYPE, NULL);
	THROW_IF(obj != NULL, INIT_OBJECT_FAILED, NULL);

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


void *
object_get_child(object_t *obj, const char *key)
{
	unsigned long hash_key = create_hash_key(key);
	
	THROW_IF(obj != NULL, OBJECT_NULL, NULL);

	void *child = CHILD(obj);

	if (obj->data_type == 0 && hash_key == obj->hash_key) {
		return child;
	} else if (obj->data_type == 1) {
		object_t **children = (object_t **) child;

		for (register size_t i = 0; i < obj->len; i++) {
			if (children[i]->hash_key == hash_key) {
				return CHILD(children[i], key);
			}
		}
	}	
	
	return NULL;
}










