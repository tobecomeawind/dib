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

static EntityTypeArray* initEntityTypeArray(EntityType* etptr);
static void insertNewEntityType (EntitiesArray*    arr,
                                 EntityType*       etptr,
                                 uint8_t           index);
static void insertNode (EntityTypeArray* etaptr, Node* nptr);

// этот файл пахнет говном

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
	if ( !gptr || !nptr) return;	

	EntityTypeArray** arr = gptr->array->noRelArray;
	uint8_t           size = gptr->array->size;
	int8_t index;
	
	// check if array is empty	
	if ( gptr->array->size == 1 ) {
		index = 0;
		insertNewEntityType(gptr->array, nptr->type, index);
		goto insertNodePoint;
	}
   
   	index = binsearch((void**)arr, size,(void*) nptr->type, bsENTITY_TYPE);
	
    if ( index < 0 ) {// if entity type not exists
		index *= -1;	    
		insertNewEntityType(gptr->array, nptr->type, index);
	}	
	
	insertNodePoint:
		insertNode(gptr->array->noRelArray[index], nptr);	
}

static void insertNewEntityType (EntitiesArray*    arr,
                                 EntityType*       etptr,
                                 uint8_t           index)
{
	if ( !arr || !etptr) return;
	
	EntityTypeArray* newEntityType = initEntityTypeArray(etptr); 	

	if ( !newEntityType ) return;

	arr->noRelArray = (EntityTypeArray**) realloc(arr->noRelArray, arr->size+1);			
	if ( !arr->noRelArray ) return; 		
	arr->size += 1;
	
	for (uint8_t i = arr->size; i > index; --i)
		arr->noRelArray[i] = arr->noRelArray[i - 1]; 	

	arr->noRelArray[index] = newEntityType;
}


static void insertNode (EntityTypeArray* etaptr, Node* nptr)
{		
	if ( !etaptr || !nptr ) return;
	
	int8_t index;	

	if ( etaptr->size == 1 ) {
		index = 0;
		etaptr->size += 1;
		goto insertPoint;
	}
	index = binsearch((void**)etaptr->array, etaptr->size, (void*)nptr, bsNODE);

	if ( index >= 0 ) return; // nptr already exists
			
	etaptr->array = (Node**) realloc(etaptr->array, etaptr->size+1);			
	
	if ( !etaptr->array ) return; 		
	etaptr->size += 1;
	
	for (uint8_t i = etaptr->size; i > index; --i)
		etaptr->array[i] = etaptr->array[i - 1]; 	
	

	insertPoint:	
		etaptr->array[index] = nptr;
}


static EntitiesArray* initEntitiesArray(void)
{
	EntitiesArray* tmpArr = (EntitiesArray*) malloc(sizeof(EntitiesArray));

	if ( !tmpArr ) return NULL;

	tmpArr->size       = 1;
	tmpArr->noRelArray = (EntityTypeArray**) malloc(sizeof(EntityTypeArray*));

	if ( !tmpArr ) return NULL;

	return tmpArr;
}

static EntityTypeArray* initEntityTypeArray(EntityType* etptr)
{
	EntityTypeArray* etaptr = (EntityTypeArray*)malloc(sizeof(EntityTypeArray));

	if ( !etaptr ) return NULL;

	etaptr->etptr = etptr;	
	etaptr->size  = 1;
	etaptr->array = (Node**) malloc(sizeof(Node*));

	if ( !etaptr->array ) return NULL;

	return etaptr; 
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


//TODO write bfs it work faster
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
