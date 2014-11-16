
#ifndef __BENCODE_H_
#define __BENCODE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#define BC_STRING		0x1
#define BC_INTEGER		0x2
#define BC_LIST			0x3
#define BC_DICT			0x4

#define BC_EOF			'e'


int bc_decode_type(char c);

#endif
