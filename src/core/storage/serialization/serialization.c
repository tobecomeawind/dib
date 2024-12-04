#include <stdio.h>
#include <stdint.h>

#include "deserialization.h"
#include "serialization.h"
#include "node.h"
#include "files.h"
#include "types.h"


void entityArraySerialize(Node** nodeArray, size_t arraySize)
{
	//----------------------------------
	//Adding nodes to entities temp file
	//----------------------------------	
		
	FILE*  tmpfp;
	Node** entitiesArray;
	
	Node*  currentNode; 

	entitiesArray = getEntitiesArray();
	entitiesArray = NULL;

	tmpfp = fopen(TEMP_FILE, "w");

	if (!entitiesArray) {
	
		fputc(arraySize, tmpfp);

		for(size_t i = 0; i < arraySize; i++) {
		
			currentNode = nodeArray[i];
			
			entitySerialize(currentNode, tmpfp);		
		}		
	}

	fputc(EOF, tmpfp);
	fclose(tmpfp);
}


void entitySerialize(Node* node, FILE* fp)
{	
	uint64_t hash;     // Entity type hash
	void*    data;     // Data
	vtypes   dataType; // Data Type	
		
	// Entity starts

	hash = node->type->hash;	
	fputc(sizeof(hash),     fp);  // size of hash
	
	for(size_t i = sizeof(uint64_t) / sizeof(uint8_t); i > 0; i--) {
		fputc((int8_t)(hash >> ((i - 1) * 8)), fp); // i - 1 cause 
													// 8 * 8 = 64
													// if we shift 64 bits right
													// we lost data
	}	
	// Data starts
	data = node->data->info;
	fputc(sizeof(data),     fp); // size of data
	fprintf(fp, data);

	// Data Type starts
	dataType = node->data->type; // don't use size
								 // cause dataType always 1 byte	
	fputc(dataType, fp);		
}
