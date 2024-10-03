#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "graph.h"
#include "types.h"


int main(void)
{	
	Node* root;
	Node* root1;
	Node* root2;
	
	int          a = 8;
	enum vtypes  b = INT;	

	root  = node_construct(data_construct((void*)(&a), b));	
	root1 = node_construct(data_construct((void*)(&a), b));	
	root2 = node_construct(data_construct((void*)(&a), b));	
	
		
	root->vtable->add_relation(root,
			           relation_construct("Root to Root 1", 
								                   root1));	
	
	root1->vtable->add_relation(root1,
		                relation_construct("Root1 to Root 2", 
							                         root2));	
	root2->vtable->add_relation(root2, 
			            relation_construct("Root2 to Root ", 
							                         root));	
	

	root->vtable->destruct(root);
	root1->vtable->destruct(root1);
	root2->vtable->destruct(root2);
	
	return 0;
}



Node* node_construct(Data* data)
{
	Node* nptr;	             // node pointer
	//static NodeVtable tptr; // table pointer	
	
	static NodeVtable tptr = {
		.destruct     = node_destruct,
		.add_relation = add_relation,
		.del_relation = NULL
	};

	nptr = (Node*) malloc(sizeof(Node));

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


