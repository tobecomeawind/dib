#include "algs.h"
#include "tokens.h"
#include <string.h>


static int compare(void* target, void* buffer, int index, bstypes type);


int binsearch(void* *buf, int size,
		      void *target,
			  bstypes type)
{
	//-----------------------------------------	
	//Simple binsearch, but with type off array
	//-----------------------------------------	
	
	int low, high, mid;
	int mediateResult;

	low  = 0;
	high = size - 1;

	while(low <= high){
		mid = (low + high) / 2;
		
		mediateResult = compare(target, buf, mid, type);

		if(mediateResult > 0){       // right
			low  = mid + 1;	
		}else if(mediateResult < 0){ // left
			high = mid - 1; 
		}else{
			switch(type){
				case(bsTOKEN):
					//if word in keywords
					return mid;
			}

			//for another case
			return 1;
		}
	}

	switch(type){
		case(bsTOKEN):
			//if no word in keywords
			return -1;
	}

	return 0;
}

static int compare(void* target, void* buffer, int index, bstypes type)
{
	//----------------------	
	//compare for binsearch
	//----------------------

	switch(type){
		case(bsCHAR):
			return strcmp((char*) target, ( (char**)buffer )[index]);		
		case(bsTOKEN):
			return strcmp((char*)target, (( (Token*)buffer) + index)->data);	
		case(bsINT):	
			return *((int*) target) - (( (int*)buffer )[index]);		
		case(bsFLOAT):	
			return (int) (*((float*) target) - (( (float*)buffer )[index]));		
	}	
}
