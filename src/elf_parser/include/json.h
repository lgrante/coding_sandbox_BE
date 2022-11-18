#ifndef __JSON_H__
#define __JSON_H__

#include <stddef.h>
#include <stdlib.h>


struct object {
	unsigned long hash_key;
	void *children;
	size_t length;
};

typedef struct object object_t;


object_t *
create_object();

void *
object_find(object_t *object, const char *key);

void *
object_resolve(object_t *object, const char *path, void *value);

object_t *
object_delete(object_t *object, const char *path);

void
object_json_export(object_t *object, const char *filepath);


#endif
