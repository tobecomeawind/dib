#include "data.h"
#include <stdlib.h>
#include <string.h>

static vtypes DataToVarType(Tokens, char*);

Data* data_construct(char* data, Tokens type)
{
	Data* dptr; // data pointer
	
	dptr = (Data*) malloc(sizeof(Data));
	
	dptr->type = DataToVarType(type, data);
	dptr->info = (void*) data;	

	return dptr;
}


static vtypes DataToVarType(Tokens token, char* data)
{
	int*    intVar;
	double* floatVar;	

	switch(token){
		case K_CHAR:
			return CHAR | strlen((char*) data);	
		case K_INT:
			intVar  = (int*) data;
			*intVar = atoi(data);	
			return INT;
		case K_FLOAT:
			floatVar  = (double*) data;	
			*floatVar = atof(data);
			return FLOAT;
		default:
			return 0;	
	}
}


void data_destruct(Data* dptr)
{
	free(dptr);	
}
