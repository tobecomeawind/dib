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
	long int hash;     // Entity type hash
	void*    data;     // Data
	vtypes   dataType; // Data Type	
		
	// Entity starts

	hash = node->type->hash;	
	fputc(sizeof(hash),     fp);
	
	for(size_t i = sizeof(long int) / sizeof(uint8_t); i > 0; i--)
		fputc((char)(hash >> i * 8), fp);
	
	// Data starts
	data   = node->data->info;
	fputc(sizeof(data),     fp);		
	fprintf(fp, data);

	// Data Type starts
	dataType = node->data->type;	
	fputc(dataType, fp);		
}
