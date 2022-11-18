#include "json.h"


object_t *
create_object()
{
	object_t obj = malloc(sizeof(struct object));

	if (obj == NULL) {
		return NULL;
	}
	obj->hash_key = 0;
	obj->children = (void *) NULL;
	obj->length = 0;

	return obj;
}


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

	if (object->length == 0 || object->children == NULL) {
		return NULL;
	}

	object_t **children = (object_t **) object->children;

	for (register size_t i = 0; i < object->length; i++) {
		if (children[i]->hash_key == hask_key) {
			const object_t match = (object_t *) children[i];

			return match;
		}
	}
}


void *
object_resolve(object_t *object, const char *path, void *value, size_t length)
{
	char *key = NULL;

	while ((key = get_next_key(&path)) != NULL) {
		void *match = object_find(match, key);

		if (match = NULL) {
			return NULL;
		}

		if (match->length > 1 && match->children != NULL) {
			object_t **children = (object_t **) match->children;

			return object_resolve(children, path, value);
		}

		match->children = value;
		match->length = length;
		return match;
	}
	return NULL;
}


/*
object_t
object_delete_property(object_t *object, const char *path);


void
object_json_export(object_t *object, const char *filepath);
*/
