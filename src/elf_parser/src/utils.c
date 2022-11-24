#include "utils.h"


unsigned long
create_hash_key(const char *key)
{
	unsigned long hash = 5381;
	int c;

	if (key == NULL) {
		return 0;
	}

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
