
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

int bc_read_string(char *in, char **str)
{
	uint32_t size = 0;

	size_t i = 0;
	while (in[i] != ':')
	{
		size *= 10;
		if (in[i] < '0' || in[i] > '9')
			return 0;

		size += in[i] - '0';
		i++;
	}
	i++;

	if (size < 1)
		return 0;

	char *p = malloc(size+1);
	if (!p)
		return 0;

	memcpy(p, in + i, size);
	i += size;
	p[size] = '\0';

	*str = p;

	return i+1;
}

int bc_read_int(FILE *in, int *val)
{
	uint32_t p = 0;

	if (fscanf(in, "%de", &p) != 1)
	     return -1;

	*val = p;

	return 0;
}
