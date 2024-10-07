#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "graph.h"
#include "types.h"
#include "hash.h"

int main(void)
{	
	Node *Tom, *Lucy;	


	Tom  = node_construct("Person",
			              data_construct((void*)"Tom",
					      CHAR));	
	
	Lucy = node_construct("Person",
			              data_construct((void*)"Lucy",
						  CHAR));	

	Tom->vtable->add_relation(Tom,
			                  relation_construct("Loves",
								                  Lucy));	

	Lucy->vtable->add_relation(Lucy,
			                   relation_construct("Loves",
								                   Tom));	
	
	Tom ->vtable->destruct(Tom);
	Lucy->vtable->destruct(Lucy);
	
	return 0;
}



Node* node_construct(char* name, Data* data)
{
	Node* nptr;	             // node pointer
	
	static NodeVtable tptr = {
		.destruct     = node_destruct,
		.add_relation = add_relation,
		.del_relation = NULL
	};

	EntityType etptr = {
		.typename = name,
		.hash     = hash(name)	
	};

	nptr = (Node*) malloc(sizeof(Node));

	nptr->type      = &etptr;
	nptr->data      = data;
	nptr->rsize     = 0;
	nptr->relations = (Relation**) malloc(sizeof(Relation*));
	nptr->vtable    = &tptr; 
	
	return nptr;
}

void node_destruct(Node* node)
{
	(node->data)->destruct(node->data);
	
	for(size_t i = 0; i < node->rsize; i++)
		(node->relations[i])->destruct(node->relations[i]);	
		
	free(node->relations);
	free(node);
}


Data* data_construct(void* data, uint8_t type)
{
	Data* dptr; // data pointer	
	
	dptr = (Data*) malloc(sizeof(Data));

	dptr->type     = type;
	dptr->info     = data;	
	dptr->destruct = &data_destruct;

	return dptr;
}

void data_destruct(Data* dptr)
{
	free(dptr);	
}

Relation* relation_construct(char* name, Node* destination)
{
	Relation* rptr; // relation pointer	

	EntityType etptr = {
		.typename = name,	
		.hash     = hash(name)
	}; 

	rptr = (Relation*) malloc(sizeof(Relation));

	rptr->name     = name;	
	rptr->dest     = destination;
	rptr->destruct = &relation_destruct;

	return rptr;
}

void relation_destruct(Relation* rptr)
{
	free(rptr);	
}

void add_relation(Node* node, Relation* rel)
{	
	Relation** relrealloc(Relation** rmptr, size_t nsize);	
	
	node->relations[node->rsize++] = rel;
	
	node->relations = relrealloc(node->relations, node->rsize);
}

Relation** relrealloc(Relation** rmptr, size_t nsize)
{
	Relation** nrmptr; // new relation massive pointer	
	
	nrmptr = (Relation**) malloc(nsize * sizeof(Relation*));

	for(size_t i = 0; i < nsize; i++)
		nrmptr[i] = rmptr[i];
	
	free(rmptr);

	return nrmptr;
}


