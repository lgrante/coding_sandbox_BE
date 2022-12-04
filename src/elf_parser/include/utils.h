#ifndef __UTILS_H__
#define __UTILS_H__


#include <stddef.h>
#include <stdlib.h>


#define THROW_IF(value, message, throw_value) {\
	if (value <= 0) {\
		if (message != (char *) NULL) {\
			dprintf(2, "Error: %s.\n", message);\
		}\
		return throw_value;\
	}\
}



unsigned long
create_hash_key(const char *key);

char *
get_next_key(char **path);


#endif
