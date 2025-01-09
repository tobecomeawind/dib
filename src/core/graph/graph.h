#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdint.h>

#include "node.h"



// Array of nodes without relations
// [Node1, Node2, Node3, ...]
typedef struct entity_type_array_t {

	EntityType* etptr;	
	Node**      array;
	uint8_t     size;

} EntityTypeArray; 



// Array of arrays of nodes without relations
// [EntityTypeArray1, EntityTypeArray2, EntityTypeArray3, ...]
//     |                  |                 |
// [ Node1,           [ Node1,          [ Node1,
//   Node2,             Node2,            Node2,
//   Node3,             Node3,            Node3,
//   ...   ]             ...   ]          ...    ]
//
// like hash table
// all nodes sorted by EntityType 
typedef struct no_relations_entities_array_t {
	
	uint8_t size;
	EntityTypeArray** noRelArray;

} EntitiesArray;




typedef struct graph_t {

	uint8_t nodes;
	uint8_t rels;	

	Node* head;	
	
	EntitiesArray* array;
	
} Graph;





Graph* graphInit(Node* head);
void linkNodes  (Graph* gptr, Node* source, Node* dest, const char* relName);
void addNode    (Graph* gptr, Node* nptr);

#endif
