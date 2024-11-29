#ifndef DATA_H
#define DATA_H

#include "types.h"
#include "tokens.h"
#include <stdint.h>

typedef struct Data{
	vtypes  type;
	void*   info;
} Data;

Data* data_construct(char* data, Tokens type);
void  data_destruct (Data* dptr);

#endif
