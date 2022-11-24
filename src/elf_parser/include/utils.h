#ifndef __UTILS_H__
#define __UTILS_H__


#include <stddef.h>
#include <stdlib.h>


unsigned long
create_hash_key(const char *key);

char *
get_next_key(char **path);


#endif
