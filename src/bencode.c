
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

	*str = p;
	p[size] = '\0';

	while (size > 0)
	{
		*(p++) = in[i++];
		size--;
	}

	return i;
}

int bc_read_int(char *in, int *val)
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
