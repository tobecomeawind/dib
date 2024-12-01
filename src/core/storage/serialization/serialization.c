#include "node.h"

#include <stdio.h>
#include <stdint.h>

#define TEMP_FILE    "entities.tmp"

#define ENTITY_TYPE 0b00000001
#define DATA        0b00000010
#define DATA_TYPE   0b00000010


static Node** getEntitiesArray(void);

void nodeSerialize(Node* nodeArray[], size_t arraySize)
{
	//----------------------------------
	//Adding nodes to entities temp file
	//----------------------------------	
		
	FILE*  tmpfp;
	Node** entitiesArray;
	
	Node*    currentNode; 
	long int hash;
	void*    data;
	vtypes   dataType;		

	entitiesArray = getEntitiesArray();

	tmpfp = fopen();

	if (!entitiesArray) {
	
		fputc(size, tmpfp);

		for(size_t i = 0; i < arraySize; i++) {
		
			currentNode = nodeArray[i];
			
			// Entity starts
			fputc(ENTITY_TYPE, tmpfp);
		
			hash = currentNode->type.hash;				
			fputc((wchar_t)hash, tmpfp);		
			
			// Data starts
			fputc(DATA,        tmpfp);		
			data   = currentNode->data->info;	
			fwrite(data, sizeof(data), sizeof(data) / sizeof(uint8_t), tmpfp); 

			// Data Type starts
			fputc(DATA_TYPE,   tmpfp);		
			dataType = currentNode->data->type;	
			fputc(dataType, tmpfp);	
		}		
	}

	fclose(tmpfp);
}

static Node** getEntitiesArray(void)
{
	FILE*    tmpfp;	
	uint8_t  countEntities;

	tmpfp = fopen(TEMP_FILE, "r");	

	if (!tmpfp) {
		printf("\nEntities Temp file didn't created yet\n");	
		return 0;
	}

	if ((countEntities = fgetc(fp)) == EOF) 
		return NULL;

		
	fclose(tmpfp);
}
