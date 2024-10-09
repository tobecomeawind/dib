#include "data.h"
#include <stdlib.h>

Data* data_construct(void* data, uint8_t type)
{
	Data* dptr; // data pointer	
	
	dptr = (Data*) malloc(sizeof(Data));

	dptr->type     = type;
	dptr->info     = data;	

	return dptr;
}

void data_destruct(Data* dptr)
{
	free(dptr);	
}
