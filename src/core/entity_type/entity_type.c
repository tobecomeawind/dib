#include "entity_type.h"
#include "hash.h"

#include <stdlib.h>


EntityType* entityTypeConstruct(char* typename, uint64_t hashValue)
{
	EntityType* etptr = (EntityType*) malloc(sizeof(EntityType));
	
	etptr->typename = typename;
	etptr->hashVal  = (hashValue) ? hashValue: hash(typename);
	
	return etptr;
}	


void entityTypeDestruct(EntityType* fuckYou)
{
	free(fuckYou);
}

