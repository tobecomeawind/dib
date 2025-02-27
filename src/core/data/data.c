#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static vtypes DataToVarType(Tokens, void*);

bool DataCliCheck = false;

Data* dataConstruct(void* data, Tokens type, bool isFromCli)
{
	Data* dptr; // data pointer

	DataCliCheck = isFromCli;

	dptr = (Data*) malloc(sizeof(Data));
	
	dptr->type = DataToVarType(type, data);
	dptr->info = data;	

	return dptr;
}

uint8_t getDataSize(Data* dptr)
{
	switch ( dptr->type ) {
		case ( INT ):
			return sizeof(int);
		case ( FLOAT ):
			return sizeof(double);	
		default: // case only with constants cause we use if	
			if ( dptr->type & CHAR ) // CHAR
				return dptr->type;	
	}	
}

int8_t dataCompare (Data* source, Data* target)
{	
	switch ( source->type ) {
		case ( INT ):
			return *((int*)(source->info)) - *((int*)(target->info)); 
		case ( FLOAT ):
			return *((double*)(source->info)) - *((double*)(target->info)); 
		case ( CHAR | FLOAT ):
			return strcmp(((char*)(source->info)), ((char*)(target->info)));
	}
}	

static vtypes DataToVarType(Tokens dataType, void* data)
{
	int*    intVar;
	double* floatVar;

	if (DataCliCheck && dataType != getTypeOfData(data)){
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


inline void dataDestruct(Data* dptr)
{
	if ( !dptr ) return;
	if ( dptr->info ) free(dptr->info);	
	
	free(dptr);	
}


Tokens getTypeOfData(char* data)
{
	Tokens dataType = K_CHAR;		

	while (*data++) {

		if ( isdigit(*data) && dataType != K_FLOAT )
			dataType = K_INT;	
			

		if ( *data == '.' ) {
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
