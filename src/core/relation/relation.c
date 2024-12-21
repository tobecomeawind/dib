#include <stdlib.h>
#include "relation.h"
#include "hash.h"

Relation* relationConstruct(char* name, Node* destination)
{
	Relation* rptr; // relation pointer	

	EntityType etptr = {
		.typename = name,	
		.hashVal     = hash(name)
	}; 

	rptr = (Relation*) malloc(sizeof(Relation));

	rptr->type     = &etptr;
	rptr->dest     = destination;

	return rptr;
}

void relationDestruct(Relation* rptr)
{
	free(rptr);	
}

Relation** relrealloc(Relation** rmptr, size_t nsize)
{
	Relation** nrmptr; // new relation massive pointer	
	
	nrmptr = (Relation**) malloc(nsize * sizeof(Relation*));

	for(size_t i = 0; i < nsize; i++)
		nrmptr[i] = rmptr[i];
	
	free(rmptr);

	return nrmptr;
}
