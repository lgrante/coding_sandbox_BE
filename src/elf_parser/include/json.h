#ifndef __JSON_H__
#define __JSON_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>


#define CHILD_TYPES 2
#define NO_CHILDREN 0
#define NO_DATA 0
#define NO_KEY 0


typedef struct {

	/*
	 * Stores the number of bytes stored in child in order to know how to cast it.
	 *
	 * Call CAST_DATA() macro function to automatically cast the data.
	 */
	uint8_t data_type;

	/*
	 * The key of the object_t to retrieve its data.
	 *
	 * On object_t initialization, the key is given as a string.
	 * Then the create_hash() function creates an unique hash of the string and
	 * is stored in hash_key property.
	 *
	 * The aim of this transformation is to reduce the complexity of the
	 * algorithm that is supposed to retrieve an object_t.
	 * (Instead of comparing one string with each one only one value is tested
	 * for each child object_t.
	 */
	unsigned long hash_key;

	/*
	 * Stores two addresses:
	 * 1 -> the data address if the object_t child is a leaf in the data tree.
	 * 2 -> the address of the its child object_t if its a parent in the data tree.
	 */
	void *child[CHILD_TYPES];
	
	/*
	 * Store the index of the child node to get into the child array property.
	 * To get the child node:
	 *
	 * 	obj->child[obj->child_type];
	 * 	
	 * Or just call the macro function:
	 * 	
	 * 	CHILD(obj);
	 *
	 * Also with this property you know wether you have to treat the current
	 * object_t as a parent object_t or a not the data tree.
	 */
	uint8_t child_type;

	/*
	 * Store the number of children if its a parent object_t.
	 * So it's the size of the child[1] array property.
	 */
	size_t len;
} object_t;


#define CHILD(obj) (obj->child[obj->type])


// TODO: Define this macro function which cast the data of the object_t in 
// the good type.
//
// #define CAST_DATA(obj) ()


// TODO: Define this macro function which is replaced during compiling time
// by the C type name of the variable that stores the value of the object_t data.
//
// #define TYPE(obj) ()


object_t *
new_obj(const char *key, uint8_t type, ...);

void *
obj_resolve(object_t *obj, const char *path);


#define RESOLVE(obj, path) (CAST_DATA(obj_resolve(obj, path))


#endif
