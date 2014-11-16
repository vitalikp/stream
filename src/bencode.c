
#include "bencode.h"


int bc_decode_type(char c)
{
	if (c == 'i')
		return BC_INTEGER;		// integer

	if (c == 'l')
		return BC_LIST;			// list

	if (c == 'd')
		return BC_DICT;			// dictionary

	return BC_STRING;			// string
}

int bc_read_string(FILE *in, char **str)
{
	uint32_t size;

	if (fscanf(in, "%d:", &size) != 1)
	     return -1;
	if (size < 1)
	     return -2;

	char *p = malloc(size+1);
	if (!p)
		return -3;

	fread(p, 1, size, in);
	p[size] = '\0';

	*str = p;

	return 0;
}

int bc_read_int(FILE *in, int *val)
{
	uint32_t p = 0;

	if (fscanf(in, "%de", &p) != 1)
	     return -1;

	*val = p;

	return 0;
}
