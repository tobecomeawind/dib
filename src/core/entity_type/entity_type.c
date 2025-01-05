#include "entity_type.h"
#include "hash.h"
#include "deserialization.h"
#include "serialization.h"

#include <stdlib.h>
#include <stdio.h>

static EntityType* entityTypeNew (char* typeName, uint64_t hashValue);


static HashTable* EntitiesTempTable;


static inline void actualizeTable () // update table to last info
{
	EntitiesTempTable = hashTableDeserialize();	
}


void printEntities (void)
{
	HashNode** entities = EntitiesTempTable->array;
	HashNode* tmpNode;

	for (uint8_t i = 0; i < EntitiesTempTable->size - 1; ++i) {
		tmpNode = entities[i];	
		while (tmpNode) {
			printf("%s\n", tmpNode->data->typeName);	
			tmpNode = tmpNode->next;
		}
	}
}

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

