#include "data.h"
#include <stdlib.h>
#include <string.h>

static vtypes TokenToVarType(Tokens, char*);

Data* data_construct(char* data, Tokens type)
{
	Data* dptr; // data pointer
	
	dptr = (Data*) malloc(sizeof(Data));
	
	dptr->type = TokenToVarType(type, data);
	dptr->info = (void*) data;	

	return dptr;
}


static vtypes TokenToVarType(Tokens token, char* data)
{
	int    intVar;
	double floatVar;	

	switch(token){
		case K_CHAR:
			return CHAR | strlen((char*) data);	
		case K_INT:
			intVar = atoi(data);	
			data   = (char*) &intVar;
			return INT;
		case K_FLOAT:
			floatVar = atof(data);	
			data     = (char*) &floatVar;
			return FLOAT;
		default:
			return 0;	
	}
}


void data_destruct(Data* dptr)
{
	free(dptr);	
}
