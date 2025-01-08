#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#include "node.h"


typedef struct graph_t {

	uint8_t nodes;
	uint8_t rels;	

	Node* head;	
} Graph;

Graph* graphInit(Node* head);
void linkNodes (Graph* gptr, Node* source, Node* dest, const char* relName);

#endif
