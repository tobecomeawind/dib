#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <stdbool.h>

#include "types.h"
#include "tokens.h"

typedef struct Data{
	vtypes  type;
	void*   info;
} Data;

Data*   dataConstruct(void* data, Tokens type, bool isFromCli);
inline void    dataDestruct (Data* dptr);
uint8_t getDataSize  (Data* dptr);
int8_t  dataCompare  (Data* source, Data* target);
Tokens  getTypeOfData(char* data);

#endif
