#include "node.h"
#include "hash.h"

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
	
	nptr = (Node*) malloc(sizeof(Node));

	nptr->type      = entityTypeConstruct(name, hashValue);
	nptr->data      = dataConstruct(data, dataTypeToken, isDataFromCli);
	nptr->rsize     = 0;
	nptr->relations = (Relation**) malloc(sizeof(Relation*)); 

	isDataFromCli = false;	

		
	return nptr;
}



void nodeDestruct(Node* node)
{
	dataDestruct(node->data);
	
	for(size_t i = 0; i < node->rsize; i++)
		relationDestruct(node->relations[i]);	
	
	//entityTypeDestruct(node->type);	
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
