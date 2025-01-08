#include <stdlib.h>
#include <stdint.h>

#include "graph.h"
#include "node.h"
#include "entity_type.h"
#include "relation.h"
#include "algs.h"

static Node* dfs (Node* base, Node* nptr, Node* target);
static void linkNodes_iml (Node* source, Node* destination,const char* relName);
static EntitiesArray* initEntitiesArray(void);



Graph* graphInit(Node* head)
{
	Graph* gptr = (Graph*) malloc(sizeof(Graph));	
	
	gptr->nodes = 1;	
	gptr->rels  = head->rsize;	
	gptr->head  = head;
	
	gptr->array = initEntitiesArray();

	return gptr;
}


void addNode (Graph* gptr, Node* nptr)
{
	if ( !gptr ) return;	
	if ( !nptr ) return;	

	EntityTypeArray** arr = gptr->array->noRelArray;
	uint8_t           size = gptr->array->size;
	uint8_t index;


	index = binsearch((void*)arr, size,(void*) nptr->etptr, bsENTITY_TYPE_HASH);


}

static EntitiesArray* initEntitiesArray(void)
{
	EntitiesArray* tmpArr = (EntitiesArray*) malloc(sizeof(EntitiesArray));

	if ( !tmpArr ) return NULL;

	tmpArr->size  = 1;
	tmpArr->noRelArray = (EntityTypeArray**) malloc(sizeof(EntityTypeArray*));

	if ( !tmpArr ) return NULL;

	return tmpArr;
}




void linkNodes (Graph* gptr, Node* source, Node* dest, const char* relName)
{
	if (gptr->head == source) 
		return linkNodes_iml(source, dest, relName);
				
	if ( !dfs(gptr->head, gptr->head, source) ) return;

	linkNodes_iml(source, dest, relName);

	gptr->nodes++;
	gptr->rels++;
}


static void linkNodes_iml (Node* source, Node* destination, const char* relName)
{
	Relation* rel = relationConstruct(relName, destination);
	
	if ( !rel ) return;	
	
	addRelation(source, rel);		
}


// depth first search 
static Node* dfs (Node* base, Node* cur, Node* target)
{
	//----------------------------
	// Function to check
	// exist target in gptr or not
	//----------------------------
	
	Relation** rels = cur->relations;
	uint8_t    size = cur->rsize;
	Node*      dest;

	// cur == base
	if ( !cur ) return NULL;

	if ( cur == target ) return cur;

	if ( !size ) return NULL;

	for (uint8_t i = 0; i < size; ++i) {
		dest = rels[i]->dest;	
		if ( dest != base && (cur = dfs(base, dest, target)) )
			return cur;
	}

	return NULL;
}
