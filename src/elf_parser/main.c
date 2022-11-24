#include <stdio.h>
#include "json_new.h"


int main()
{
	//
	// TODO: test each function from json.c file.
	//
	object *root = new_obj(NULL, 1, 5);

	if (root->child_type == 0) {
		printf("Property type\n");
	} else {
		printf("Parent type with %ld children.\n", root->len);
	}

	return 0;
}
