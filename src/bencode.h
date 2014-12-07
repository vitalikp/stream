
#ifndef __BENCODE_H_
#define __BENCODE_H_

#include "object.h"


#define BC_DELIM		':'
#define BC_EOF			'e'


int bc_decode_type(char c);
size_t bc_read_lenstr(char *in, size_t *len);
size_t bc_read_string(char *in, char **str);
size_t bc_read_int(char *in, uint32_t *val);

#endif
