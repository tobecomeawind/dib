#include <stdlib.h>
#include <stdint.h>

#include "graph.h"
#include "node.h"
#include "relation.h"


static Node* dfs (Node* base, Node* nptr, Node* target);
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
	if (gptr->head == source) 
		return linkNodes_iml(source, dest, relName);
				
	if ( !dfs(gptr->head, gptr->head, source) ) return;

	linkNodes_iml(source, dest, relName);
}

static void linkNodes_iml (Node* source, Node* destination, const char* relName)
{
	Relation* rel = relationConstruct(relName, destination);
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
