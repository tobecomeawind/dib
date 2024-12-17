#ifndef HASH_H
#define HASH_H

#define SEED 969
#include <stdint.h>

typedef struct HashNode{
	
	uint64_t         hashVal;
	char*            data;
	struct HashNode* next;

} HashNode;


typedef struct {

	uint8_t    size;  // sizeof array
	HashNode** array; // array	
					  
} HashTable;

uint64_t   hash          (char* val);
HashTable* hashTableInit (uint8_t size);

#endif
