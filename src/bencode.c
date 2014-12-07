
#include "bencode.h"


int bc_decode_type(char c)
{
	if (c == 'i')
		return OBJ_INTEGER;		// integer

	if (c == 'l')
		return OBJ_LIST;		// list

	if (c == 'd')
		return OBJ_DICT;		// dictionary

	return OBJ_STRING;			// string
}

size_t bc_read_lenstr(char *in, size_t *len)
{
	size_t size = 0;

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

	*len = size;

	return i;
}

size_t bc_read_string(char *in, char **str)
{
	size_t size = 0;

	size_t i = 0;
	i += bc_read_lenstr(in, &size);

	if (size < 1)
		return 0;

	char *p = malloc(size+1);
	if (!p)
		return 0;

	*str = p;
	p[size] = '\0';

	while (size > 0)
	{
		*(p++) = in[i++];
		size--;
	}

	return i;
}

size_t bc_read_int(char *in, uint32_t *val)
{
	uint32_t p = 0;

	size_t i = 0;
	if (in[i] == '-')
	{
		if (in[i+1] == BC_EOF)		// if '-'
			return 0;

		if (in[i+1] == '0')			// if '-0'
			return 0;

		i++;
	}

	while (in[i] != BC_EOF)
	{
		p *= 10;
		if (in[i] < '0' || in[i] > '9')
			return 0;

		p += in[i] - '0';
		i++;
	}
	i++;

	if (in[0] == '-')
		p = -p;

	*val = p;

	return i;
}
