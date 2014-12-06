#include <stdlib.h>
#include <string.h>

#include "object.h"


obj_t* obj_new(void)
{
	obj_t *p = calloc(1, sizeof(obj_t));
	if (!p)
	     return NULL;

	p->type = OBJ_UNSET;

	return p;
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
	memset(p + len, 0, 1);
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
