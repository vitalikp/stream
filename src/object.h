
#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <stdlib.h>
#include <stdint.h>


#define OBJ_STRING		0x1			// <len>:<string>
#define OBJ_INTEGER		0x2			// i<integer>e
#define OBJ_LIST		0x3			// l<object1>...<objectN>e
#define OBJ_MAP			0x4			// d<string><object1>...<string><objectN>e


typedef struct obj_t obj_t;

struct obj_t
{
	uint8_t    type;
	void       *value;
};

static inline void* OBJ_VAL(obj_t *obj)
{
	return !obj?NULL:obj->value;
}


obj_t* obj_new(uint8_t type);
void obj_destroy(obj_t **obj);

void obj_get_str(obj_t *obj, char **value);
uint8_t obj_set_str(obj_t *obj, size_t len, char *value);
void obj_get_int(obj_t *obj, uint32_t *value);

#endif
