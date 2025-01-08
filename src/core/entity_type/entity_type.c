#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "entity_type.h"
#include "hash.h"
#include "deserialization.h"
#include "serialization.h"

static EntityType* entityTypeNew (const char* typeName, uint64_t hashValue);


static HashTable* EntitiesTempTable;


void printEntities (void)
{
	HashNode** entities = EntitiesTempTable->array;
	HashNode* tmpNode;

	for (uint8_t i = 0; i < EntitiesTempTable->size; ++i) {
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

void destructEntitiesTempTable (void)
{
	hashTableDestruct(EntitiesTempTable);
}

static EntityType* entityTypeNew (const char* typeName, uint64_t hashValue)
{
	EntityType* etptr = (EntityType*) malloc(sizeof(EntityType));
	
	etptr->typeName = malloc(strlen(typeName) + 1);
	strcpy(etptr->typeName, typeName);

	etptr->hashVal  = (hashValue) ? hashValue: hash(typeName);		

	return etptr;
}



EntityType* entityTypeConstruct (const char* typeName, uint64_t hashValue)
{
	return entityTypeNew(typeName, hashValue);	
}


EntityType* entitiesTempTableSearchByHash (uint64_t hashValue)
{
	return hashTableSearchByHash(EntitiesTempTable, hashValue);	
}	

EntityType* entityTypeConstructTmp (const char* typeName, uint64_t hashValue)
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
	if ( !fuckYou ) return;	
	if ( fuckYou->typeName) free(fuckYou->typeName);	
	free(fuckYou);
}

