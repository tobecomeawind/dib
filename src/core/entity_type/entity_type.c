#include "entity_type.h"
#include "hash.h"
#include "deserialization.h"
#include <stdlib.h>


static EntityType* entityTypeNew (char* typename, uint64_t hashValue);

HashTable* EntitiesTempTable;


void initEntitiesTempTable ()
{
	HashTable* table;

	if ( !(table = hashTableDeserialize()) ) 
		table = hashTableInit(1); // if no data in file,
								  // create new file
	

	EntitiesTempTable = table;
}


static EntityType* entityTypeNew (char* typename, uint64_t hashValue)
{
	EntityType* etptr = (EntityType*) malloc(sizeof(EntityType));
	
	etptr->typename = typename;
	etptr->hashVal  = (hashValue) ? hashValue: hash(typename);		

	return etptr;
}



EntityType* entityTypeConstruct (char* typename, uint64_t hashValue)
{
	return entityTypeNew(typename, hashValue);	
}


EntityType* entityTypeConstructTmp (char* typename, uint64_t hashValue)
{
	//------------------------------------------------
	// Create new Entity and push in Entities Tmp File
	// or
	// get entitity ptr from Entities Temp Table 
	//------------------------------------------------


	EntityType* etptr;

	if ( !(etptr = hashTableSearchByHash(EntitiesTempTable, hashValue)) ) {
		etptr = entityTypeNew(typename, hashValue);
	}
	
	return etptr;
}	



void entityTypeDestruct(EntityType* fuckYou)
{
	free(fuckYou);
}

