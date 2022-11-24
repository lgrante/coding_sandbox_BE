#ifndef __JSON_H__
#define __JSON_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


struct object {
	unsigned long hash_key;
	void *children;
	size_t length;
	uint8_t has_children;
};

typedef struct object object_t;


object_t *
create_object(const char *key, void *value, size_t len, uint8_t has_children);

void *
object_resolve(object_t **object, const char *path, object_t *value);

object_t *
object_delete(object_t *object, const char *path);

void
object_json_export(object_t *object, const char *filepath);


#endif
