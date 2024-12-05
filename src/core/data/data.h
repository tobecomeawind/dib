#ifndef DATA_H
#define DATA_H

#include "types.h"
#include "tokens.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct Data{
	vtypes  type;
	void*   info;
} Data;

Data* dataConstruct(void* data, Tokens type, bool isFromCli);
void  dataDestruct (Data* dptr);

#endif
