#include <stdlib.h>
#include <stdint.h>

#include "graph.h"
#include "node.h"
#include "entity_type.h"
#include "relation.h"
#include "algs.h"
#include "data.h"
#include "hash.h"
#include "deserialization.h"
#include "serialization.h"

static Node* dfs (Node* base, Node* nptr, Node* target);
static void linkNodes_iml (Node* source, Node* destination,const char* relName);
static EntitiesArray* initEntitiesArray(void);
static Node* nodeSearchArray (EntitiesArray* arr, Node* target);

static EntityTypeArray* initEntityTypeArray(EntityType* etptr);
static void insertNewEntityType (EntitiesArray*    arr,
                                 EntityType*       etptr,
                                 uint8_t           index);
static void insertNode (EntityTypeArray* etaptr, Node* nptr);

static inline bool nodeCompare(Node* source, Node* target);
static Node* isNodeExist (Graph* gptr, Node* target);


extern char* createPath(const char* filename);
// этот файл пахнет говном


// Relation Entities Temp Table
static HashTable* RelEntitiesTempTable;


void initRelEntitiesTempTable (void)
{
	char* path = createPath(REL_TEMP_FILE);
	RelEntitiesTempTable = initTableFromFile(path);
	free(path);
}

void destructRelEntitiesTempTable (void)
{
	hashTableDestruct(RelEntitiesTempTable);
}

void debug_printFreeEntitiesArray (Graph* gptr)
{	
	EntitiesArray*    eaptr = gptr->array;	
	EntityTypeArray** arr   = eaptr->noRelArray;

	EntityTypeArray*  tmpEntityTypeArray;
	EntityType*       tmpEntity;
	Node*             tmpNode;
		
	
	for (uint8_t i = 0; i < eaptr->size; ++i) {
		
		tmpEntityTypeArray = arr[i];
		tmpEntity = tmpEntityTypeArray->etptr;	
		
		printf("%i. %s\n", i + 1, (char*)tmpEntity->typeName);	
		
		for (uint8_t j = 0; j < tmpEntityTypeArray->size; ++j) {
			tmpNode = tmpEntityTypeArray->array[j];
			printf("\t%i. %s\n", j + 1, (char*)tmpNode->data->info);	
		}
		putc('\n', stdout);	
	}	
}


Graph* graphInit(Node* head)
{
	//--------------------------------------------------
	// init graph
	// and
	// init array of arrays with nodes without relations
	//--------------------------------------------------

	Graph* gptr = (Graph*) malloc(sizeof(Graph));	
	
	gptr->nodes = 1;	
	gptr->rels  = head->rsize;	
	gptr->head  = head;
	
	gptr->array = initEntitiesArray();

	return gptr;
}


void addNode (Graph* gptr, Node* nptr)
{
	//---------------------------------------------
	// Add node to array of nodes without relations
	//---------------------------------------------
		
	if ( !gptr || !nptr) return;	

	EntityTypeArray** arr   = gptr->array->noRelArray;
	uint8_t           size  = gptr->array->size;
	int8_t            index = 0;
	
	// check if array is empty	
	if ( size == 0 ) {
		insertNewEntityType(gptr->array, nptr->type, index);
		goto insertNodePoint;
	}
   
   	index = binsearch((void**)arr, size,(void*) nptr->type, bsENTITY_TYPE);
	
    if ( index > 0 ) {// if entity type not exists
	
		index -= 1;	 // skip 0 value
					 // check algs.c file
	} else {
		index *= -1;	    
		insertNewEntityType(gptr->array, nptr->type, index);	
	}
	
	insertNodePoint:
		insertNode(gptr->array->noRelArray[index], nptr);	
}


EntityType* relEntityTypeConstructTmp (const char* typeName,
                                       uint64_t    hashValue,
                                       const char* subdir)
{
    return entityTypeConstructTmp(RelEntitiesTempTable,
                                  typeName,
                                  hashValue,
                                  subdir);
}


void linkNodes (Graph* gptr, Node* source, Node* dest, const char* relName)
{
	//-------------------------------------------
	// Create relation beetween two nodes
	//
	// LINK (Person:Vasya, Person:Masha, LOVED_IN
	//
	// source  = Person:Vasya
	// target  = Person:Masha
	// relName = LOVED_IN
	//-------------------------------------------
	
	//TODO need free(source) and free(dest) cause this temp values 	

	if ( !gptr || !source || !dest || !relName ) return;
	
			
	// check if source exist in graph or source exists in no rel array		
	if ( !(source = isNodeExist(gptr, source)) ) return;	
	
	if ( !(dest   = isNodeExist(gptr, dest)) ) return;

	gptr->nodes++;
	gptr->rels++;
		
	linkNodes_iml(source, dest, relName);
}




static void insertNewEntityType (EntitiesArray*    arr,
                                 EntityType*       etptr,
                                 uint8_t           index)
{
	//--------------------------------------------------
	// Insert Entity Array to array with arrays of nodes
	//--------------------------------------------------
	
	if ( !arr || !etptr) return;
	
	EntityTypeArray*  newEntityType = initEntityTypeArray(etptr);
	EntityTypeArray** tmpArr;

	if ( !newEntityType ) return;
	
	tmpArr = (EntityTypeArray**) realloc(arr->noRelArray,
                                      sizeof(EntityTypeArray*)*((arr->size)+1));	
	
	if ( !tmpArr ) {
		free(newEntityType);	
		return; 
	}	

	arr->noRelArray = tmpArr;
	
	for (uint8_t i = arr->size; i > index; --i)
		arr->noRelArray[i] = arr->noRelArray[i - 1]; 	

	arr->size += 1;
	
	arr->noRelArray[index] = newEntityType;
}


static void insertNode (EntityTypeArray* etaptr, Node* nptr)
{		
	//------------------------------
	// Insert Node without relations
	// to array 
	//------------------------------
	
	if ( !etaptr || !nptr ) return;
	
	int8_t index = 0;	

	if ( etaptr->size == 0 ) {
		etaptr->size += 1;
		goto insertPoint;
	}

	index = binsearch((void**)etaptr->array, etaptr->size, (void*)nptr, bsNODE);

	if ( index > 0 ) return; // nptr already exists
		
	index *= -1;

	etaptr->array = (Node**) realloc(etaptr->array,
                                     sizeof(Node*) * ((etaptr->size)+1));			
	
	if ( !etaptr->array ) return; 		
	
	for (uint8_t i = etaptr->size; i > index; --i)
		etaptr->array[i] = etaptr->array[i - 1]; 	
	
	etaptr->size += 1;

	insertPoint:	
		etaptr->array[index] = nptr;
}


static EntitiesArray* initEntitiesArray(void)
{
	//--------------------------------------------------
	// Init array where arrays of node without relations
	// and this arrays sorted by EntityType
	//--------------------------------------------------
	
	EntitiesArray* tmpArr = (EntitiesArray*) malloc(sizeof(EntitiesArray));

	if ( !tmpArr ) return NULL;

	tmpArr->size       = 0;
	tmpArr->noRelArray = (EntityTypeArray**) malloc(sizeof(EntityTypeArray*));

	if ( !tmpArr ) return NULL;

	return tmpArr;
}

static EntityTypeArray* initEntityTypeArray(EntityType* etptr)
{
	//---------------------------------------
	// Init Array with nodes without relation
	//---------------------------------------
	
	EntityTypeArray* etaptr = (EntityTypeArray*)malloc(sizeof(EntityTypeArray));

	if ( !etaptr ) return NULL;

	etaptr->etptr = etptr;	
	etaptr->size  = 0;
	etaptr->array = (Node**) malloc(sizeof(Node*));

	if ( !etaptr->array ) return NULL;

	return etaptr; 
}

static void linkNodes_iml (Node* source, Node* destination, const char* relName)
{
	//--------------------------------
	// linkNodes implementation
	// create relation beetween  nodes
	//--------------------------------
	
	Relation* rel = relationConstructTmp(relName, destination);
	
	if ( !rel ) return;	
	
	addRelation(source, rel);		
}


static Node* isNodeExist (Graph* gptr, Node* target)
{
	Node* tmpNode;	
	
	if ( tmpNode = dfs(gptr->head, gptr->head, target) ) 
		return tmpNode;

	if ( tmpNode = nodeSearchArray(gptr->array, target) ) 
		return tmpNode;
	

	//free(nptr)
	
	return NULL;	
}



static Node* nodeSearchArray (EntitiesArray* arr, Node* target)
{
	//----------------------------------------
	// Search node in no relations node array
	//----------------------------------------

	if ( !arr || !target ) return NULL;	
	
	Node*            tmpNode;
	EntityTypeArray* tmpArray;
	int8_t           index;	
	
	index = binsearch((void**)arr->noRelArray,
	                arr->size,
                    (void*)(target->type),
                    bsENTITY_TYPE);

	if ( index < 0 ) return NULL;

	tmpArray = arr->noRelArray[index - 1]; 
	
    index = binsearch((void**)tmpArray->array,
                      tmpArray->size,
                      (void*)target,
                      bsNODE); 	

	if ( index < 0 ) return NULL;

	tmpNode = tmpArray->array[index - 1];

	if ( !nodeCompare(tmpNode, target) ) return NULL;	
	
	return tmpNode;
}



//TODO write bfs it work faster
// depth first search 
static Node* dfs (Node* base, Node* cur, Node* target)
{
	//----------------------------
	// Function to check
	// exist target in gptr or not
	//----------------------------
	if ( !base || !cur ) return NULL;	

	Relation** rels = cur->relations;
	uint8_t    size = cur->rsize;
	Node*      dest;

	if ( nodeCompare(cur, target) ) return cur;

	if ( !size ) return NULL;

	for (uint8_t i = 0; i < size; ++i) {
		dest = rels[i]->dest;	
		if ( dest != base && (cur = dfs(base, dest, target)) )
			return cur;
	}

	return NULL;
}


static inline bool nodeCompare(Node* source, Node* target)
{
	if ( !source || !target ) return false;
	if ( source->type != target->type )	return false;

	return dataCompare(source->data, target->data);
}

