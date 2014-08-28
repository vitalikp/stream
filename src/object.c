#include <stdlib.h>
#include <string.h>

#include "object.h"

struct obj_t
{
	uint8_t    type;
	void       *value;
};

uint8_t obj_new(obj_t **obj)
{
	obj_t *p = calloc(1, sizeof(obj_t));
	if (!p)
	     return -1;

	p->type = OBJ_UNSET;

	*obj = p;

	return 0;
}

void obj_destroy(obj_t **obj)
{
	obj_t *p = *obj;
	switch (p->type)
	{
		case OBJ_STRING:
		case OBJ_INTEGER:
			free(p->value);
			break;
		case OBJ_LIST:
			// TODO implement destroy list
			break;
		case OBJ_MAP:
			// TODO implement destroy map
			break;
	}

	free(p);

	*obj = NULL;
}

uint8_t obj_get_type(obj_t *obj)
{
	return obj->type;
}

void obj_get_str(obj_t *obj, char **value)
{
	*value = obj->value;
}

uint8_t obj_set_str(obj_t *obj, size_t len, char *value)
{
	obj->type = OBJ_STRING;

	void *p = malloc(len + 1);
	if (!p)
	     return -1;

	memcpy(p, value, len);
	obj->value = p;

	return 0;
}

void obj_get_int(obj_t *obj, uint32_t *value)
{
	*value = *(uint32_t*)obj->value;
}

uint8_t obj_set_int(obj_t *obj, uint32_t value)
{
	obj->type = OBJ_INTEGER;

	uint32_t *p = malloc(sizeof(uint32_t));
	if (!p)
	     return -1;

	*p = value;
	obj->value = p;

	return 0;
}

void obj_unset(obj_t *obj)
{
	switch (obj->type)
	{
		case OBJ_STRING:
		case OBJ_INTEGER:
			free(obj->value);
			break;
		case OBJ_LIST:
			// TODO implement unset list
			break;
		case OBJ_MAP:
			// TODO implement unset map
			break;
	}

	obj->type = OBJ_UNSET;
}
