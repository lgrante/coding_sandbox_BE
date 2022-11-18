#include "json.h"
#include <stdio.h>
#include <string.h>


#define KEYS_NB 4

unsigned long 
create_hash_key(const char *key);

int main()
{
	object_t *obj = create_object();

	const char *tab[KEYS_NB] = {
		"coucou",
		"prout",
		"hello",
		"anotherKey"
	};

	obj->props = malloc(KEYS_NB * sizeof(struct property *));
	obj->length = KEYS_NB;

	if (obj->props == NULL) {
		return -1;
	}

	for (register int i = 0; i <  KEYS_NB; i++) {
		(obj->props)[i] = malloc(sizeof(struct property));

		if ((obj->props)[i] == NULL) {
			free(obj->props);
			free(obj);
			return -1;
		}

		const char *value = "a random value";

		(obj->props[i])->hash_key = create_hash_key(tab[i]);
		obj->props[i]->value = (void *) strdup(value);
	}

	struct property *match = object_find(obj, "prout");

	printf("Key: %ld\nValue: %s\n\n", match->hash_key, (char *) match->value);

	return 0;
}
