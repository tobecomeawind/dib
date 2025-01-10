#ifndef HASH_H
#define HASH_H

#define SEED 969
#include <stdint.h>
#include <stdbool.h>

#include "node.h"
#include "entity_type.h"

typedef struct HashNode{
	
	EntityType*      data;
	struct HashNode* next;

} HashNode;


typedef struct {

	uint8_t    size;  // sizeof array
	HashNode** array; // array	
					  
} HashTable;

EntityType* entityTypeConstructTmp (HashTable*  table,
                                    const char* typeName,
                                    uint64_t    hashValue,
                                    const char* subdir);

uint64_t    hash                  (const char* word);
HashTable*  hashTableInit         (uint8_t size);
void        hashTableInsert       (HashTable*  table, EntityType* data);
void        hashTableDestruct     (HashTable*  htptr);
EntityType* hashTableSearchByName (HashTable*  table, const char* name);
EntityType* hashTableSearchByHash (HashTable*  table, uint64_t hashVal);
void        hashTableDeleteByName (HashTable*  table, char* name); 
HashNode*   hashNodeConstruct     (EntityType* etptr);
HashTable*  initTableFromFile     (const char* filename);

#endif
