#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static vtypes DataToVarType(Tokens, char*);
static Tokens getTypeOfData(char*);

Data* data_construct(char* data, Tokens type)
{
	Data* dptr; // data pointer
	
	dptr = (Data*) malloc(sizeof(Data));
	
	dptr->type = DataToVarType(type, data);
	dptr->info = (void*) data;	

	return dptr;
}


static vtypes DataToVarType(Tokens dataType, char* data)
{
	int*    intVar;
	double* floatVar;

	if (dataType != getTypeOfData(data)){
		printf("\nInvalid Data Type\n");
		return 0;	
	}	

	switch (dataType){
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


static Tokens getTypeOfData(char* data)
{
	Tokens dataType = K_CHAR;	

	while (*data++) {

		if (isdigit(*data) && dataType != K_FLOAT){
			dataType = K_INT;	
		}		

		if (*data == '.') {
			switch (dataType) {
				case K_INT:
					dataType = K_FLOAT;
					break;
				case K_FLOAT:
					dataType = K_CHAR;
					break;
			}
		}
	
	}

	return dataType;	
}
