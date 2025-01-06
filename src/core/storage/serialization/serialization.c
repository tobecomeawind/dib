#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "deserialization.h"
#include "serialization.h"
#include "entity_type.h"
#include "node.h"
#include "files.h"
#include "types.h"

static void hashNodeSerialize (HashNode*   tableNode, FILE* tmpfp);
static void entitySerialize   (EntityType* entity,    FILE* fp);


void hashTableSerialize (HashTable* table)
{
	//-----------------------
	// Serialize a hash table
	// Table of Entities
	//-----------------------
	
	FILE* tmpfp;
	
	tmpfp = fopen(TEMP_FILE, "w");

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


static void entitySerialize(EntityType* entity, FILE* fp)
{	
	//-------------------
	// Serialize a entity
	//-------------------
	
	uint64_t hash;     // Entity type hash
	char*    data;     // Data
		
	// Entity starts
	
	// Entity name for hashTable
	hash = entity->hashVal;	

	fputc(sizeof(hash), fp);  // size of hash

	for(size_t i = sizeof(uint64_t) / sizeof(uint8_t); i > 0; --i) {
		fputc((int8_t)(hash >> ((i - 1) * 8)), fp); // i - 1 cause 
	}												// 8 * 8 = 64
													// if we shift 64 bits right
													// we lost data
	
	// Entity Name starts
	data = entity->typeName;
	fputc(strlen(data), fp); // size of data
	
	fprintf(fp, data);
}
