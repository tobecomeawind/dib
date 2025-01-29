#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "deserialization.h"
#include "serialization.h"
#include "entity_type.h"
#include "node.h"
#include "types.h"
#include "graph.h"
#include "algs.h"

static void hashNodeSerialize (HashNode*   tableNode, FILE* tmpfp);
static void entitySerialize   (EntityType* entity,    FILE* fp);

static inline void hashSerialize (uint64_t hash, FILE* fp);
static void nodeSerialize (Node* nptr, FILE* tmpfp);

static void relationSerialize (Relation* rptr, FILE* tmpfp);

void hashTableSerialize (HashTable* table, const char* filename)
{
	//-----------------------
	// Serialize a hash table
	// Table of Entities
	//-----------------------
	
	FILE* tmpfp;
	
	tmpfp = fopen(filename, "w");

	fputc(table->size, tmpfp);

	for (uint8_t i = 0; i < table->size; ++i)
		hashNodeSerialize(table->array[i], tmpfp);	
	 	
	fputc(EOF, tmpfp);
	fclose(tmpfp);
}


static void hashNodeSerialize (HashNode* tableNode, FILE* tmpfp)
{
	//-------------------------------
	// Serialize a hash node of table
	//-------------------------------
	
	if ( !tableNode ) {	
		fputc(0, tmpfp);
		return;	
	}

	for (;tableNode;) {		
		entitySerialize(tableNode->data, tmpfp);

		if (tableNode = tableNode->next)  // if next node exists
			fputc('>', tmpfp);            // we put "flag" byte	
	}									  // to show the current node
										  // have a next node
										  // bucket with list		
}


void graphSerialize (Graph* gptr, const char* filename)
{
	//------------------
	// Serialize a graph
	//------------------
	
	if ( !gptr ) return;		
	
	FILE* fp = fopen(filename, "w");
	if ( !fp ) return;

	Queue* qptr = queueConstruct();
	if ( !qptr ) return;

	Node* cur = gptr->head;
	Node* tmp;
			
	do {	
		nodeSerialize(cur, fp);
		
		for (uint8_t i = 0; i < cur->rsize; ++i)
			queuePush(qptr, (void*)(cur->relations[i]->dest));
		
		
		do {
			tmp = cur;
			cur = (Node*) queuePop(qptr);
		} while ( cur && (tmp->id != cur->id) );

	} while ( cur );

	queueDestruct(qptr);

	fputc(EOF, fp);
	fclose(fp);
}



static void nodeSerialize (Node* nptr, FILE* tmpfp)
{
	//-----------------
	// Serialize a node
	//-----------------
	
	// in file
	//|id|entity hash size|entity hash|data type|data size|data|rsize|relations|

	if ( !nptr || !tmpfp ) return;

	uint8_t dataSize = 0;

	// |id|
	fputc(nptr->id, tmpfp);
	
	// |entity hash size|entity hash|	
	hashSerialize(nptr->type->hashVal, tmpfp);	
	
	// |data type|
	fputc(nptr->data->type, tmpfp);
	// |data size|	
	fputc(dataSize = getDataSize(nptr->data), tmpfp);
	// |data|	
	fwrite(nptr->data, 1, dataSize, tmpfp);	
	
	if ( nptr->rsize > 0 ) {
		// |rsize|
		fputc(nptr->rsize, tmpfp);

		// |relations|
		for (uint8_t i = 0; i < nptr->rsize; ++i)
			relationSerialize(nptr->relations[i], tmpfp);
	}	
}

static void relationSerialize (Relation* rptr, FILE* tmpfp)
{
	//---------------------
	// Serialize a relation
	//---------------------
	
	// in file
	// |entity hash size|entity hash|id|
	
	if ( !rptr || !tmpfp ) return;

	// |entity hash size|entity hash|
	entitySerialize(rptr->type, tmpfp);

	fputc(rptr->dest->id, tmpfp);
}


static void entitySerialize(EntityType* entity, FILE* fp)
{	
	//-------------------
	// Serialize a entity
	//-------------------
	
	// in file
	// |hash size|hash|data size|data|

	uint64_t hash;     // Entity type hash
	char*    data;     // Data
		
	// Entity starts
	
	// Entity name for hashTable
	hash = entity->hashVal;	

	hashSerialize(hash, fp);

	// Entity Name starts
	data = entity->typeName;
	fputc(strlen(data), fp); // size of data
	
	fprintf(fp, data);
}


static inline void hashSerialize (uint64_t hash, FILE* fp)
{
	//---------------
	// Serialize hash
	//---------------

	// in file 
	// |hash size|hash|

	fputc(sizeof(hash), fp);  // size of hash
	for(size_t i = sizeof(uint64_t) / sizeof(uint8_t); i > 0; --i) {
		fputc((int8_t)(hash >> ((i - 1) * 8)), fp); // i - 1 cause 
	}										        // 8 * 8 = 64
											    	// if we shift 64 bits right
													// we lost data
	
}

