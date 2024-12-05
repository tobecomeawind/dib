#include "node.h"
#include "hash.h"
#include "serialization.h"

#include <stdlib.h>
#include <stdbool.h>

bool isDataFromCli = false;

Node* nodeConstructFromCli(char* name, char *data, Tokens dataTypeToken)
{
	Node* nptr; 
	void* voidData = (void*) data;

	isDataFromCli = true;
	nptr          = nodeConstruct(name, 0, voidData, dataTypeToken);	

	return nptr;
}


Node* nodeConstruct(char*    name,
                    uint64_t hashValue,
                    void*    data,
                    Tokens   dataTypeToken)
{
	Node*  nptr;	// node pointer
	Node** testnptr; 
	
	EntityType etptr = {
		.typename = name,
		.hash     = (hashValue) ? hashValue : hash(name),
	};

	nptr = (Node*) malloc(sizeof(Node));

	nptr->type      = &etptr;
	nptr->data      = dataConstruct(data, dataTypeToken, isDataFromCli);
	nptr->rsize     = 0;
	nptr->relations = (Relation**) malloc(sizeof(Relation*)); 

	isDataFromCli = false;	
	
	testnptr = &nptr;	

	entityArraySerialize(testnptr, 1);

	return nptr;
}


void nodeDestruct(Node* node)
{
	dataDestruct(node->data);
	
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
