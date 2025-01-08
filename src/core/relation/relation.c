#include <stdlib.h>

#include "relation.h"
#include "hash.h"
#include "node.h"

Relation* relationConstruct(const char* name, Node* destination)
{	
	Relation* rptr = (Relation*) malloc(sizeof(Relation));
	if ( !rptr ) return NULL;

	// TODO need create another hashTable for rel Entities
	EntityType* etptr = entityTypeConstructTmp(name, hash(name));
	if ( !etptr ) return NULL;

	rptr->type     = etptr;
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
