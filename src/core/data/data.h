#ifndef DATA_H
#define DATA_H

#include "types.h"
#include <stdint.h>

typedef struct Data{
	vtypes  type;
	void*   info;
} Data;

Data* data_construct(void* data, uint8_t type);
void  data_destruct (Data* dptr);

#endif
