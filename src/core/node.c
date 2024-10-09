#include "node.h"
#include "hash.h"

#include <stdlib.h>

Node* node_construct(char* name, Data* data)
{
	Node* nptr;	             // node pointer

	EntityType etptr = {
		.typename = name,
		.hash     = hash(name)	
	};

	nptr = (Node*) malloc(sizeof(Node));

	nptr->type      = &etptr;
	nptr->data      = data;
	nptr->rsize     = 0;
	nptr->relations = (Relation**) malloc(sizeof(Relation*)); 
	
	return nptr;
}


void node_destruct(Node* node)
{
	data_destruct(node->data);
	
	for(size_t i = 0; i < node->rsize; i++)
		relation_destruct(node->relations[i]);	
		
	free(node->relations);
	free(node);
}


void add_relation(Node* node, Relation* rel)
{	
	Relation** relrealloc(Relation** rmptr, size_t nsize);	
	
	node->relations[node->rsize++] = rel;
	
	node->relations = relrealloc(node->relations, node->rsize);
}


void del_relation();
