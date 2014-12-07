
#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "object.h"


list_t* list_new(const uint32_t len)
{
	list_t *p = calloc(1, sizeof(list_t));
	if (!p)
		return NULL;

	p->len = len;
	p->value = calloc(len, sizeof(obj_t*));
	if (!p->value)
	{
		free(p);
		return NULL;
	}

	return p;
}

void list_destroy(list_t **list)
{
	list_t *obj = *list;

	uint16_t i = 0;
	for (i = 0; i<obj->size;i++)
		if (obj->value[i])
		{
#ifdef DEBUG
	if (obj->value[i]->type == OBJ_STRING)
		printf("[destroy] list: index=[%d] '%s'\n", obj->size,  obj->value[i]->value);
	if (obj->value[i]->type == OBJ_INTEGER)
		printf("[destroy] list: index=[%d] '%d'\n", obj->size,  *(uint32_t*)obj->value[i]->value);
#endif
			obj_destroy(&obj->value[i]);
		}

	free(obj->value);

	free(obj);

	*list = NULL;
}

uint8_t list_add(list_t *list, obj_t *value)
{
	if (list->size == list->len)
	{
		list->value = realloc(list->value, sizeof(obj_t*)*(list->len+LIST_CAPACITY));
		if (!list->value)
		{
			list->len = 0;
			return -1;
		}
		list->len += LIST_CAPACITY;
	}

#ifdef DEBUG
	if (value && value->type == OBJ_STRING)
		printf("[add] list: index=[%d] '%s'\n", list->size,  value->value);
	if (value && value->type == OBJ_INTEGER)
		printf("[add] list: index=[%d] '%d'\n", list->size,  *(uint32_t*)value->value);
#endif

	list->value[list->size++] = value;

	return 0;
}

void list_remove(list_t *list, uint32_t index)
{
	if (index < 0 || index > list->size)
		return;

#ifdef DEBUG
	obj_t *value = list->value[index];
	if (value && value->type == OBJ_STRING)
		printf("[remove] list: index=[%d] '%s'\n", index, value->value);
	if (value && value->type == OBJ_INTEGER)
		printf("[remove] list: index=[%d] '%d'\n", index, *(uint32_t*)value->value);
#endif
	list->size--;
	uint32_t i = index;
	while (i < list->size)
	{
		list->value[i] = list->value[i + 1];
		i++;
	}
	list->value[list->size] = NULL;
}
