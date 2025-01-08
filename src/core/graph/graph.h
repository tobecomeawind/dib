#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#include "node.h"

typedef struct entity_type_array_t {

	EntityType* etptr;	
	Node**      array;

} EntityTypeArray; 

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
void linkNodes (Graph* gptr, Node* source, Node* dest, const char* relName);

#endif
