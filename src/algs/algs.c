#include <string.h>

#include "algs.h"
#include "tokens.h"
#include "entity_type.h"
#include "graph.h"

static int compare(void* target, void** buffer, int index, bstypes type);
static inline int stringCompare (char* targetWord, char* bufWord);


int8_t binsearch(void** buf, uint8_t size, void* target, bstypes type)
{
	//----------------------------------------	
	//Simple binsearch, but with type of array
	//----------------------------------------	

	if ( !buf || !target ) return -1;


	uint8_t low, high, mid;
	uint8_t mediateResult;

	low  = 0;
	high = size - 1;

	while ( low <= high ) {
		mid = (low + high) / 2;
		
		mediateResult = compare(target, buf, mid, type);

		if ( mediateResult > 0 ) {       // right
			low  = mid + 1;	
		} else if ( mediateResult < 0 ) { // left
			high = mid - 1; 
		} else {
			switch ( type ) {
				case( bsTOKEN ):
				case( bsENTITY_TYPE ):
					//if word in keywords
					return mid;
			}

			//for another case
			return 1;
		}
	}

	switch ( type ) {
		case( bsTOKEN ):
		case( bsENTITY_TYPE ):
			//if no word in keywords
			//we return insert position
			return -1 * low;
	}

	return 0;
}

static int compare(void* target, void** buffer, int index, bstypes type)
{
	//----------------------	
	//compare for binsearch
	//----------------------

	switch ( type ) {
		case ( bsCHAR ):
			return strcmp((char*) target, ( (char**)buffer )[index]);		
		case ( bsTOKEN ):
			return strcmp((char*)target, (( (Token*)buffer) + index)->data);	
		case ( bsINT ):	
			return *((int*) target) - (( (int*)buffer )[index]);		
		case ( bsFLOAT ):	
			return (int) (*((float*) target) - (( (float*)buffer )[index]));
		case ( bsENTITY_TYPE ):
			return stringCompare((char*)(( (EntityType*) target )->typeName ), (char*)(( (EntityTypeArray**)buffer )[index])->etptr->typeName);
		case ( bsNODE ):
			return stringCompare((char*)(((Node*)target)->data->info), (char*)(((Node**)buffer)[index])->data->info);		
	}	
}
 

static inline int stringCompare (char* targetWord, char* bufWord)
{
	//-----------------------------------------------
	// strcmp(), but we check if value not initialise
	// skip SIGSEGV
	//-----------------------------------------------
	
	//if ( !bufWord ) return -1;
	
	return strcmp(targetWord, bufWord);	
}




