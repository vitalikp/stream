
#ifndef __LIST_H_
#define __LIST_H_

#include "object.h"


#define LIST_CAPACITY	10

typedef struct list_t list_t;

struct list_t
{
	uint32_t   size;
	uint32_t   len;
	obj_t      **value;
};


list_t* list_new(const uint32_t len);
void list_destroy(list_t **list);

uint8_t list_add(list_t *list, obj_t *obj);
void list_remove(list_t *list, uint32_t index);

#endif
