#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "entity_type.h"
#include "hash.h"
#include "deserialization.h"
#include "serialization.h"

static EntityType* entityTypeNew (const char* typeName, uint64_t hashValue);


static HashTable* NodeEntitiesTempTable;

extern char* createPath(const char* subdir);

void printEntities (void)
{
	HashNode** entities = NodeEntitiesTempTable->array;
	HashNode* tmpNode;

	for (uint8_t i = 0; i < NodeEntitiesTempTable->size; ++i) {
		tmpNode = entities[i];	
		while (tmpNode) {
			printf("%s\n", tmpNode->data->typeName);	
			tmpNode = tmpNode->next;
		}
	}
}

void initNodeEntitiesTempTable (void)
{
	char* path = createPath(NODE_TEMP_FILE);	
	NodeEntitiesTempTable = initTableFromFile(path);
	free(path);
}

void destructNodeEntitiesTempTable (void)
{
	hashTableDestruct(NodeEntitiesTempTable);
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


EntityType* searchByHashNodeEntitiesTempTable (uint64_t hashValue)
{
	return hashTableSearchByHash(NodeEntitiesTempTable, hashValue);	
}	

EntityType* entityTypeConstructTmp (const char* typeName, uint64_t hashValue)
{
	//------------------------------------------------
	// Create new Entity and push in Entities Tmp File
	// or
	// get entitity ptr from Entities Temp Table 
	//------------------------------------------------


	EntityType* etptr;
	char* path = createPath(NODE_TEMP_FILE);

	if ( !(etptr = hashTableSearchByHash(NodeEntitiesTempTable, hashValue)) ) {
		etptr = entityTypeNew(typeName, hashValue);
		hashTableInsert(NodeEntitiesTempTable, etptr);
		hashTableSerialize(NodeEntitiesTempTable, path);
	}

	free(path);	
	
	return etptr;
}	



void entityTypeDestruct(EntityType* fuckYou)
{
	if ( !fuckYou ) return;	
	if ( fuckYou->typeName) free(fuckYou->typeName);	
	free(fuckYou);
}

