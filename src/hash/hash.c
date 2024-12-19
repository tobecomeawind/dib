#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hash.h"

static uint8_t   hashNodeIndex    (HashNode*   hnptr,   uint8_t size);
static uint8_t   hashIndex        (uint64_t    hashVal, uint8_t size);
static HashNode* hashNodeInit     (EntityType* data );
static void      hashNodeDestruct (HashNode*   hnptr);
static bool      hashTableSearch  (HashTable*  table,   uint64_t hashVal);
static void      hashTableDelete  (HashTable*  table,   uint64_t hashVal);
static inline uint64_t getHash(HashNode* hashNode);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// In this folder
//
// Word "Node" != Node of Graph (/src/core/node)
//
// Word "Node" = Hash Node(node of hash table bucket linked list)
//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


uint64_t hash(char* val)
{
	//----------------------------------------
	// Main hash function for string(Entities)
	//----------------------------------------
	
	uint64_t hashval = 0;
	uint8_t  len_s   = strlen(val);
	
	for(uint8_t i = 0; i < len_s; i++)
		hashval += (uint64_t) pow(SEED, len_s - (i+1)) * val[i];
	
	return hashval;	
}


HashNode* hashNodeConstruct (EntityType* etptr)
{
	return hashNodeInit(etptr);
}

static HashNode* hashNodeInit (EntityType* data)
{
	//----------------------
	// Hash Node Constructor
	//----------------------
		
	HashNode* hnptr = (HashNode*) malloc(sizeof(HashNode));	

	hnptr->data = data;
	hnptr->next = NULL;

	return hnptr;
}

static void hashNodeDestruct (HashNode* hnptr)
{
	//---------------------
	// Hash Node Destructor
	//---------------------
		
	if (!hnptr) return;
	
	//free(hnptr->data);
	entityTypeDestruct(hnptr->data);	
	free(hnptr);
}

static void hashNodeDelete (HashNode* node, uint64_t hashVal)
{	
	//--------------------
	// Delete Node in List
	//--------------------
	
	for (;node; node = node->next) {
		HashNode* nextNode = node->next;
		
		// name nextNode equals deleteNode

		if (nextNode && getHash(nextNode) == hashVal) { // if we find node
			node->next = nextNode->next; // jumping by one node
			hashNodeDestruct(nextNode);
			return;
		}
	}
}


HashTable* hashTableInit (uint8_t size)
{
	//-----------------------
	// Hash Table Constructor
	//-----------------------
	
	HashTable* htptr = (HashTable*) malloc(sizeof(HashTable));
	
	htptr->size = size;

	htptr->array = (HashNode**) malloc(sizeof(HashNode*) * size);	

	return htptr;
}

void hashTableDestruct (HashTable* htptr)
{
	//----------------------
	// Hash Table Destructor
	//----------------------
	
	if (!htptr) return;

	for (uint8_t i = 0; i < htptr->size; i++) {
		HashNode* tmp = htptr->array[i];	
		HashNode* next;	
		
		for (;tmp;) {
			next = tmp->next;
			hashNodeDestruct(tmp);
			tmp = next;
		} 
	}
	
	free(htptr->array);
	free(htptr);
}


void hashTableInsert (HashTable* table, EntityType* data)
{
	//---------------------------------
	// Insert data in hash table bucket
	//---------------------------------
	
	HashNode* hnptr       = hashNodeInit(data);	
	uint8_t   insertIndex = hashNodeIndex(hnptr, table->size);
	HashNode* tmp         = table->array[insertIndex];	

	// if bucket is empty
	if (!tmp) {
		table->array[insertIndex] = hnptr;
		return;
	}

	for (;tmp->next; tmp = tmp->next) // go to last node of bucket linked list	
		if (getHash(tmp) == getHash(hnptr)) return; 
                                                    // if we find equals hash
													// we break the function
													// node with equal hash
													// exists
	
	tmp->next = hnptr; // add last value
}


bool hashTableSearchByName (HashTable* table, char* name)
{
	//------------------------
	// Search Node by Name
	// Public Function
	// Wrap of hashTableSearch
	//-------------------------
	
	uint64_t hashName = hash(name);	
		
	return hashTableSearch(table, hashName);			
}


static bool hashTableSearch (HashTable* table, uint64_t hashVal)
{
	//----------------------
	// Search Node by hash
	// return true if exists
	//----------------------
		
	uint8_t   searchIndex = hashIndex(hashVal, table->size);	
	HashNode* tmp         = table->array[searchIndex]; // node by bucket index

	if (tmp) // if bucket exists	
		for (;tmp; tmp = tmp->next) // check list  
			if (getHash(tmp) == hashVal)
				return true; // if hash`s equals
			
	return false;
}



void hashTableDeleteByName (HashTable* table, char* name) 
{
	//------------------------
	// Delete Node by Name
	// Public Function
	// Wrap of hashTableDelete
	//------------------------
	
	uint64_t hashName = hash(name);

	hashTableDelete(table, hashName);
}

static void hashTableDelete (HashTable* table, uint64_t hashVal)
{
	//--------------------
	// Delete Node by Hash
	//--------------------

	uint8_t   deleteIndex = hashIndex(hashVal, table->size);	
	HashNode* tmp         = table->array[deleteIndex];

	if (tmp) { // if bucket not empty	
		if (getHash(tmp) == hashVal) { // if first bucket hash
						    	       // equal
									   // delete node hash
			table->array[deleteIndex] = tmp->next;
			hashNodeDestruct(tmp);
			return;
		}
		
		hashNodeDelete(tmp, hashVal); // search in bucket list
	}

}



static uint8_t hashNodeIndex (HashNode* hnptr, uint8_t size)
{
	//------------------
	// Wrap if hashIndex
	// But with Node
	//------------------
	
	return hashIndex(getHash(hnptr), size);
}

static uint8_t hashIndex(uint64_t hashVal, uint8_t size)
{
	//-----------------------
	// Return Index of bucket
	//-----------------------
	
	return (uint8_t)(hashVal % size);	
}

static inline uint64_t getHash(HashNode* hashNode)
{
	return hashNode->data->hashVal;
}
