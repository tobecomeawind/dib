#include "algs.h"
#include <string.h>

int binsearch(void* *buf, int size,
		      void *target,
			  vtypes type)
{
	//-----------------------------------------	
	//Simple binsearch, but with type off array
	//-----------------------------------------	
	
	int low, high, mid;
	int mediateResult;

	low  = 0;
	high = size;

	while(low <= high){
		mid = (low + high) / 2;
		
		mediateResult = compare(target, buf, mid, type);

		if(mediateResult > 0){       // right
			low  = mid + 1;	
		}else if(mediateResult < 0){ // left
			high = mid - 1; 
		}else{
			return 1;
		}
	}
	
	return 0;
}

int compare(void* target, void* buffer, int index, vtypes type)
{
	//----------------------	
	//compare for binsearch
	//----------------------

	switch(type){
		case(CHAR):
			return strcmp((char*) target, ((char**)buffer)[index]);		
		case(INT):	
			return *((int*) target) - (((int*)buffer)[index]);		
		case(FLOAT):	
			return (int) (*((float*) target) - (((float*)buffer)[index]));		
	}	
}
