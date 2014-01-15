
#include "bencode.h"


int bc_read_string(FILE *in, char **str)
{
	uint32_t size;

	if (fscanf(in, "%d:", &size) != 1)
	     return -1;
	if (size < 1)
	     return -2;

	char *p = malloc(size+1);

	int i=0;
	while (i<size)
	     p[i++] = getc(in);
	p[i] = '\0';

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

void bc_read_list(FILE *in)
{
	char c;
	
	printf("[");
	while ((c = getc(in)) != EOF)
	{
	     if (c == 'e')
	          break;

	     ungetc(c, in);
	     bc_read(in);
	     
	     printf(",");
	}
	printf("]\n");
}

void bc_read_dict(FILE *in)
{
	char c;

	printf("\n{\n");
	while ((c = getc(in)) != EOF)
	{
	     if (c == 'e')
	          break;

	     // string key
	     char *key = NULL;
	     ungetc(c, in);
	     if (bc_read_string(in, &key) != 0)
	     {
	          printf("fail read key!\n");
	          break;
	     }

	     // value
	     printf("\t<%s>:\t", key);

	     bc_read(in);

	     printf("\n");
	}
	printf("}\n");
}

void bc_read(FILE *in)
{
	char c;

	switch ((c = getc(in)))
	{
	     case 'i':// integer
	         {
	              int val;
	              bc_read_int(in, &val);
	              printf("%d", val);
	         }
	         break;
	     case 'l':// list
	         bc_read_list(in);
	         break;
	     case 'd':// dictionary
	         bc_read_dict(in);
	         break;
	     default: // string
	         if (c>='0' && c<='9')
	         {
	              char *str = NULL;
	              ungetc(c, in);
	              bc_read_string(in, &str);
	              printf("'%s'", str);
	              if (str)
	                   free(str);
	         }
	         break;
	}
}
