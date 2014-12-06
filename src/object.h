
#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <stdint.h>

enum type_obj
{
	OBJ_UNSET,
	OBJ_STRING,		// <len>:<string>
	OBJ_INTEGER,		// i<integer>e
	OBJ_LIST,		// l<object1>...<objectN>e
	OBJ_MAP			// d<string><object1>...<string><objectN>e
};

typedef struct obj_t obj_t;

struct obj_t
{
	uint8_t    type;
	void       *value;
};


obj_t* obj_new(uint8_t type);
void obj_destroy(obj_t **obj);

void obj_get_str(obj_t *obj, char **value);
uint8_t obj_set_str(obj_t *obj, size_t len, char *value);
void obj_get_int(obj_t *obj, uint32_t *value);
uint8_t obj_set_int(obj_t *obj, uint32_t value);

#endif
