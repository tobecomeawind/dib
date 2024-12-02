#include <stdio.h>
#include <stdint.h>

#include "deserialization.h"
#include "serialization.h"
#include "node.h"
#include "files.h"
#include "types.h"


void nodeArraySerialize(Node** nodeArray, size_t arraySize)
{
	//----------------------------------
	//Adding nodes to entities temp file
	//----------------------------------	
		
	FILE*  tmpfp;
	Node** entitiesArray;
	
	Node*  currentNode; 

	entitiesArray = getEntitiesArray();

	tmpfp = fopen(TEMP_FILE, "w");

	if (!entitiesArray) {
	
		fputc(arraySize, tmpfp);

		for(size_t i = 0; i < arraySize; i++) {
		
			currentNode = nodeArray[i];
			
			nodeSerialize(currentNode, tmpfp);		
		}		
	}

	fputc(EOF, tmpfp);
	fclose(tmpfp);
}


void nodeSerialize(Node* node, FILE* fp)
{	
	long int hash;     // Entity type hash
	void*    data;     // Data
	vtypes   dataType; // Data Type	
		
	// Entity starts
	fputc(ENTITY_TYPE,    fp);

	hash = node->type->hash;	
	
	for(size_t i = sizeof(long int) / sizeof(uint8_t); i > 0; i--)
		fputc((char)(hash >> i * 8), fp);
	
	// Data starts
	fputc(DATA,           fp);		
	data   = node->data->info;	
	fwrite(data, sizeof(data), sizeof(data) / sizeof(uint8_t), fp); 

	// Data Type starts
	fputc(DATA_TYPE,      fp);		
	dataType = node->data->type;	
	fputc(dataType, fp);		
}
