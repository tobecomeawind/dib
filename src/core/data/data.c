#include "data.h"
#include <stdlib.h>
#include <string.h>

static vtypes TokenToVarType(Tokens, void*);

Data* data_construct(void* data, Tokens type)
{
	Data* dptr; // data pointer	
	
	dptr = (Data*) malloc(sizeof(Data));
	
	dptr->type = TokenToVarType(type, data);
	dptr->info = data;	

	return dptr;
}


static vtypes TokenToVarType(Tokens token, void* data)
{
	switch(token){
		case K_CHAR:
			return CHAR | strlen((char*) data);	
		case K_INT:	
			return INT;
		case K_FLOAT:
			return FLOAT;
		default:
			return 0;	
	}
}


void data_destruct(Data* dptr)
{
	free(dptr);	
}
