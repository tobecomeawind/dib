#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "node.h"
#include "hash.h"
#include "files.h"

static Node* nodeConstruct_iml (EntityType* etptr, Data* dptr, Relation** rptr);

// TODO как вариант в nodeConstruct_iml передавать ссылки на функции

extern char* createPath(const char* filename);

Node* nodeConstructTmp(char* name, char *data, Tokens dataTypeToken)
{
	Node* nptr; 

	void*    voidData  = (void*) data;
	uint64_t hashValue = hash(name);
	
	EntityType* etptr = nodeEntityTypeConstructTmp(name,
                                                   hashValue,
                                                   NODE_TEMP_FILE);	
	Data*       dptr  = dataConstruct(data, dataTypeToken, true);

	Relation**  rptr  = (Relation**) malloc(sizeof(Relation*)); 

	nptr = nodeConstruct_iml(etptr, dptr, rptr);	
	
	return nptr;
}


Node* nodeConstruct(char*    name,
                    uint64_t hashValue,
                    void*    data,
                    Tokens   dataTypeToken)
{
	Node*  nptr;	// node pointer
	
	EntityType* etptr = entityTypeConstruct(name, hashValue);
	Data*       dptr  = dataConstruct(data, dataTypeToken, false);

	Relation**  rptr  = (Relation**) malloc(sizeof(Relation*)); 

	nptr = nodeConstruct_iml(etptr, dptr, rptr);
	
	return nptr;
}


static Node* nodeConstruct_iml (EntityType* etptr, Data* dptr, Relation** rptr)
{
	Node* nptr;

	nptr = (Node*) malloc(sizeof(Node));

	if ( !nptr ) return NULL;

	nptr->type      = etptr;
	nptr->data      = dptr;
	nptr->rsize     = 0; // TODO rework
	nptr->relations = rptr;

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

void addRelation(Node* node, Relation* rel)
{	
	// TODO rework to chech if rel alread in relations
	Relation** relrealloc(Relation** rmptr, size_t nsize);	
	
	node->relations[node->rsize++] = rel;
	
	node->relations = relrealloc(node->relations, node->rsize);
}


void del_relation();
