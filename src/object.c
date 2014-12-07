#include <string.h>

#include "object.h"
#include "types/list.h"


obj_t* obj_new(uint8_t type)
{
	obj_t *p = malloc(sizeof(obj_t));
	if (!p)
	     return NULL;

	p->type = type;
	switch (p->type)
	{
		case OBJ_INTEGER:
			p->value = malloc(sizeof(uint32_t));
			if (!p->value)
			{
				free(p);
				return NULL;
			}
			break;
		case OBJ_LIST:
			p->value = list_new(LIST_CAPACITY);
			break;
		default:
			p->value = NULL;
	}

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
			list_destroy((list_t**)&(p->value));
			break;
		case OBJ_DICT:
			// TODO implement destroy map
			break;
	}

	free(p);

	*obj = NULL;
}

void obj_get_str(obj_t *obj, char **value)
{
	*value = obj->value;
}

uint8_t obj_set_str(obj_t *obj, size_t len, char *value)
{
	obj->type = OBJ_STRING;

	char *p = malloc(len + 1);
	if (!p)
	     return -1;

	p[len] = '\0';
	size_t i = 0;
	while (len > 0)
	{
		*(p++) = value[i++];
		len--;
	}

	obj->value = p;

	return 0;
}

void obj_get_int(obj_t *obj, uint32_t *value)
{
	*value = *(uint32_t*)obj->value;
}
