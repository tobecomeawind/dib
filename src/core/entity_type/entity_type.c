#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "entity_type.h"
#include "hash.h"
#include "deserialization.h"
#include "serialization.h"
#include "files.h"

static EntityType* entityTypeNew (const char* typeName, uint64_t hashValue);

static HashTable* NodeEntitiesTempTable;

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
	clearFile(NODE_TEMP_FILE);
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


EntityType* nodeEntityTypeConstructTmp (const char* typeName,
                                        uint64_t    hashValue,
                                        const char* subdir)
{
    return entityTypeConstructTmp(NodeEntitiesTempTable,
                                  typeName,
                                  hashValue,
                                  subdir);
}





void entityTypeDestruct(EntityType* fuckYou)
{
	if ( !fuckYou ) return;	
	if ( fuckYou->typeName) free(fuckYou->typeName);	
	free(fuckYou);
}

