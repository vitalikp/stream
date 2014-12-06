
#ifndef __BENCODE_H_
#define __BENCODE_H_

#include <stdlib.h>
#include <stdint.h>


#define BC_STRING		0x1			// <len>:<string>
#define BC_INTEGER		0x2			// i<integer>e
#define BC_LIST			0x3			// l<object1>...<objectN>e
#define BC_DICT			0x4			// d<string><object1>...<string><objectN>e

#define BC_EOF			'e'


int bc_decode_type(char c);
int bc_read_string(char *in, char **str);
int bc_read_int(char *in, int *val);

#endif
