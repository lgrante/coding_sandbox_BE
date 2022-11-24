#include "json.h"


unsigned long
create_hash_key(const char *key)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *key++)) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}


object_t *
create_object(const char *key, void *value, size_t len, uint8_t has_children)
{
	object_t *obj = malloc(sizeof(struct object));

	if (obj == NULL) {
		return NULL;
	}

	if (has_children) {
		obj->children = malloc(len * sizeof(object_t *));

		if (obj->children == NULL) {
			return NULL;
		}
	} else {
		obj->children = value;
	}

	obj->hash_key = key == NULL ? 0 : create_hash_key(key);
	obj->length = len;
	obj->has_children = has_children;

	return obj;
}


char *
get_next_key(char **path)
{
	register size_t i = 0;
	char *key = NULL;

	if (*path == NULL || (*path)[0] == 0) {
		return NULL;
	}

	for (; (*path)[i] && (*path)[i] != '.'; i++);

	if ((key = malloc((i + 1) * sizeof(char))) == NULL) {
		return NULL;
	}

	for (i = 0; (*path)[i] && (*path)[i] != '.'; i++) {
		key[i] = (*path)[i];
	}

	key[i] = 0;
	*path = *path + i + ((*path)[i] != 0);

	return key;
}


void *
object_find(object_t *object, const char *key)
{
	const unsigned long hash_key = create_hash_key(key);

	if (object->has_children == 0 || object->length == 0 || object->children == NULL) {
		return NULL;
	}

	object_t **children = (object_t **) object->children;

	for (register size_t i = 0; i < object->length; i++) {
		if (children[i]->hash_key == hash_key) {
			object_t *match = (object_t *) children[i];

			return match;
		}
	}
}


void
object_add_children(object_t *object, object_t *child)
{
	if (object->has_children == 0 || object->length == 0 || object->children == NULL) {
		object->children = malloc(sizeof(object_t *));
		object->length = 1;
		object->has_children = 1;
	}

	const object_t **children = (object_t **) object->children;
	object_t **new_children = malloc((object->length + 1) * sizeof(object_t *));

	for (register size_t i = 0; i < object->length; i++) {
		new_children[i] = children[i];
	}

	new_children[object->length] = child;
	free(object->children);
	object->length = object->length + 1;
}


void *
object_resolve(object_t **object, const char *path, object_t *value)
{
	const char *path_copy = strdup(path);
	char *key =  get_next_key(&path);
	object_t *match = (object_t *) object_find(*object, key);

	if (match == NULL) {
		if (value->children == NULL && value->length == 0) {
			return NULL;
		}

		if (strcmp(path_copy, key) != 0) {
			object_t *child = create_object(key, NULL, 1, 1);

			object_add_children(*object, child);
		} else {
			free(*object);
			*object = value;
			return (*object)->children;
		}

		free(key);
		free(path_copy);
	}
	return object_resolve(object, path, value);
}


/*
object_t
object_delete_property(object_t *object, const char *path);


void
object_json_export(object_t *object, const char *filepath);
*/
