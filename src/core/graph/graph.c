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
#include "files.h"

static Node* dfs (Node* base, Node* cur, Node* target);
static void linkNodes_iml (Node* source, Node* destination,const char* relName);

static EntitiesArray* initEntitiesArray (void);
static void       destructEntitiesArray (EntitiesArray* arrptr);

static Node* nodeSearchArray (EntitiesArray* arr, Node* target);

static EntityTypeArray* initEntityTypeArray(EntityType* etptr);
static void         destructEntityTypeArray(EntityTypeArray* etaptr);

static void insertNewEntityType (EntitiesArray*    arr,
                                 EntityType*       etptr,
                                 uint8_t           index);
static void   insertNode (EntityTypeArray* etaptr, Node* nptr);

static Graph* graphInit_iml    (void);
static void   graphDestruct_iml(Graph* gptr);

static inline bool nodeCompare(Node* source, Node* target);
static Node* isNodeExist (Graph* gptr, Node* target);


static void shiftArray (void** array, uint8_t size, uint8_t index, bool right);
static void nodeDeleteFromArray (EntityTypeArray* etaptr, uint8_t index);


// этот файл пахнет говном


// Relation Entities Temp Table
static HashTable* RelEntitiesTempTable;

static Graph*     MainGraph;

void initRelEntitiesTempTable (void)
{
	char* path = createPath(REL_TEMP_FILE);
	RelEntitiesTempTable = initTableFromFile(path);
	free(path);
}

void destructRelEntitiesTempTable (void)
{
	hashTableDestruct(RelEntitiesTempTable);
	clearFile(REL_TEMP_FILE);
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

void initMainGraph (void)
{
	MainGraph = graphInit_iml();
}

void destructMainGraph (void)
{
	graphDestruct_iml(MainGraph);
}

static Graph* graphInit_iml(void)
{
	//--------------------------------------------------
	// init graph
	// and
	// init array of arrays with nodes without relations
	//--------------------------------------------------

	//TODO graph serialization

	Graph* gptr = (Graph*) malloc(sizeof(Graph));	
	
	gptr->nodes = 0;	
	gptr->rels  = 0;	
	gptr->head  = NULL;
	
	gptr->array = initEntitiesArray();

	return gptr;
}

static void graphDestruct_iml(Graph* gptr)
{
	destructEntitiesArray(gptr->array);	
	free(gptr);					
}

void appendNode (Node* nptr)
{
	//---------------------------------------------
	// Add node to array of nodes without relations
	//---------------------------------------------
		
	if ( !nptr ) return;	

	EntityTypeArray** arr   = MainGraph->array->noRelArray;
	uint8_t           size  = MainGraph->array->size;
	int8_t            index = 0;
	
	// check if array is empty	
	if ( size == 0 ) {
		insertNewEntityType(MainGraph->array, nptr->type, index);
		goto insertNodePoint;
	}
   
   	index = binsearch((void**)arr, size,(void*) nptr->type, bsENTITY_TYPE);
	
    if ( index > 0 ) {// if entity type not exists
	
		index -= 1;	 // skip 0 value
					 // check algs.c file
	} else {
		index *= -1;	    
		insertNewEntityType(MainGraph->array, nptr->type, index);	
	}
	
	insertNodePoint:
		insertNode(arr[index], nptr);
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


bool linkNodes (Node* source, Node* dest, const char* relName)
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
	
	if ( !source || !dest || !relName ) return false;
	
	// check if source exist in graph or source exists in no rel array		
	
	// if no head we add head and dont check source to exists	
	if ( !MainGraph->head ) MainGraph->head = source;
	else if ( !(source = isNodeExist(MainGraph, source)) ) return false;	
			
	if ( !(dest = isNodeExist(MainGraph, dest)) ) return false;

	MainGraph->nodes++;
	MainGraph->rels++;
		
	linkNodes_iml(source, dest, relName);
	return true;
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
	arr->size += 1;
	
	shiftArray((void**)arr->noRelArray, arr->size, index, true);
	
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
	etaptr->size += 1;

	shiftArray((void**)etaptr->array, etaptr->size, index, true);

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

static void destructEntitiesArray (EntitiesArray* arrptr)
{
	for (uint8_t i = 0; i < arrptr->size; ++i) 
		destructEntityTypeArray(arrptr->noRelArray[i]);	
	free(arrptr);	
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

static void destructEntityTypeArray(EntityTypeArray* etaptr)
{
	for (uint8_t i = 0; i < etaptr->size; ++i)	
		nodeDestruct(etaptr->array[i]);

	free(etaptr->etptr);
	free(etaptr);
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
	Node* tmpNode = NULL;	
	
	if ( tmpNode = dfs(gptr->head, gptr->head, target) ) 
		goto exit;

	if ( tmpNode = nodeSearchArray(gptr->array, target) ) 
		goto exit;
	
	exit:
		return tmpNode;	
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
	
	index = binsearch((void**)( arr->noRelArray ),
	                arr->size,
                    (void*)(target->type),
                    bsENTITY_TYPE);

	if ( index <= 0 ) return NULL;

	tmpArray = arr->noRelArray[index - 1]; 
	
    index = binsearch((void**)( tmpArray->array ),
                      tmpArray->size,
                      (void*)target,
                      bsNODE); 	

	if ( index <= 0 ) return NULL;

	tmpNode = tmpArray->array[index - 1];

	if ( !nodeCompare(tmpNode, target) ) return NULL;			

	nodeDeleteFromArray(tmpArray, index - 1);

	return tmpNode;
}


static void nodeDeleteFromArray (EntityTypeArray* etaptr, uint8_t index)
{
	if ( !etaptr ) return;
	
	Node** tmpArray = NULL; 

	shiftArray((void**) etaptr->array, etaptr->size, index, false);
	
	if ( etaptr->size - 1 > 0) {
		tmpArray = (Node**) realloc(etaptr->array,
       	                         sizeof(Node*) * ((etaptr->size) - 1));
		if ( !tmpArray ) return;
	}

	etaptr->array = tmpArray;
	etaptr->size -= 1; 	
}


static void shiftArray (void** array, uint8_t size, uint8_t index, bool right)
{
	//--------------------------------
	// Shift all values off array by 1
	// to left or right
	// start on index
	//
	// Example array = [1, 2, 3, 4] 
	// size = 3
	// index = 1
	// right = true
	//
	// result = [1, NULL, 2, 3]
	//--------------------------------

	if ( right ) {
		for (uint8_t i = size - 1; i > index; --i)
			array[i] = array[i - 1];	
	} else {
		for (uint8_t i = index; i < size; ++i)
			array[i] = array[i + 1];	
	}
}

// TODO write bfs it work faster
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

	return dataCompare(source->data, target->data) == 0;
}

