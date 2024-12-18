#ifndef HASH_H
#define HASH_H

#define SEED 969
#include <stdint.h>
#include <stdbool.h>
#include "node.h"
 
typedef struct HashNode{
	
	Node*            data;
	struct HashNode* next;

} HashNode;


typedef struct {

	uint8_t    size;  // sizeof array
	HashNode** array; // array	
					  
} HashTable;


uint64_t   hash                  (char* val);
HashTable* hashTableInit         (uint8_t size);
void       hashTableInsert       (HashTable* table, Node* data);
void       hashTableDestruct     (HashTable* htptr);
bool       hashTableSearchByName (HashTable* table, char* name);
void       hashTableDeleteByName (HashTable* table, char* name); 

#endif
