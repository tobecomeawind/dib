#include "entity_type.h"
#include "hash.h"
#include "deserialization.h"
#include "serialization.h"

#include <stdlib.h>


static EntityType* entityTypeNew (char* typeName, uint64_t hashValue);


static HashTable* EntitiesTempTable;

void initEntitiesTempTable (void)
{
	HashTable* table;
	if ( !(table = hashTableDeserialize()) ) 
		table = hashTableInit(1); // if no data in file,
								  // create new file
	
	EntitiesTempTable = table;
}


static EntityType* entityTypeNew (char* typeName, uint64_t hashValue)
{
	EntityType* etptr = (EntityType*) malloc(sizeof(EntityType));
	
	etptr->typeName = typeName;
	etptr->hashVal  = (hashValue) ? hashValue: hash(typeName);		

	return etptr;
}



EntityType* entityTypeConstruct (char* typeName, uint64_t hashValue)
{
	return entityTypeNew(typeName, hashValue);	
}


EntityType* entityTypeConstructTmp (char* typeName, uint64_t hashValue)
{
	//------------------------------------------------
	// Create new Entity and push in Entities Tmp File
	// or
	// get entitity ptr from Entities Temp Table 
	//------------------------------------------------


	EntityType* etptr;

	if ( !(etptr = hashTableSearchByHash(EntitiesTempTable, hashValue)) ) {
		etptr = entityTypeNew(typeName, hashValue);
		hashTableInsert(EntitiesTempTable, etptr);
		hashTableSerialize(EntitiesTempTable);
	}	
	
	return etptr;
}	



void entityTypeDestruct(EntityType* fuckYou)
{
	free(fuckYou);
}

