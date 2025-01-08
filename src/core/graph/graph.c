#include <stdlib.h>
#include <stdint.h>

#include "graph.h"
#include "node.h"
#include "relation.h"


static Node* dfs (Graph* gptr, Node* nptr, Node* target);
static void linkNodes_iml (Node* source, Node* destination,const char* relName);


Graph* graphInit(Node* head)
{
	Graph* gptr = (Graph*) malloc(sizeof(Graph));	
	
	gptr->nodes = 0;	
	gptr->rels  = 0;	
	gptr->head  = head;
	
	return gptr;
}


void linkNodes (Graph* gptr, Node* source, Node* dest, const char* relName)
{
	if (gptr->head == source || gptr->head == dest) 
		return linkNodes_iml(source, dest, relName);
				
	if ( !dfs(gptr, gptr->head, source) ) NULL;

	linkNodes_iml(source, dest, relName);
}

static void linkNodes_iml (Node* source, Node* destination, const char* relName)
{
	Relation* rel = relationConstruct(relName, destination);
	addRelation(source, rel);		
}


// depth first search 
static Node* dfs (Graph* gptr, Node* cur, Node* target)
{
	//----------------------------
	// Function to check
	// exist target in gptr or not
	//----------------------------
	
	Node* base = gptr->head;
	Relation** rels = cur->relations;

	// cur == base
	if ( !cur ) return NULL;

	if ( cur == target ) return cur;

	if ( !cur->rsize ) return NULL;

	for (uint8_t i = 0; i < cur->rsize; ++i)	
		if ( cur = dfs(gptr, rels[i]->dest, target) )
			return cur;

	return NULL;
}



