#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "deserialization.h"
#include "files.h"

Node** getEntitiesArray(void)
{
	FILE*    tmpfp;
	uint8_t  countEntities;
	Node**   entitiesArray;

	tmpfp = fopen(TEMP_FILE, "r");	

	if (!tmpfp) {
		printf("\nEntities Temp file didn't created yet\n");	
		return 0;
	}

	if ((countEntities = fgetc(tmpfp)) == EOF){
		printf("\nNo data in file!\n");
		fclose(tmpfp);
		return NULL;
	}

	entitiesArray = (Node**) malloc(sizeof(Node*) * countEntities);	

	for (size_t i = 0; i < countEntities; i++) {
		entityDeserialize(tmpfp);	
	}

	fclose(tmpfp);
}


static Node* entityDeserialize(FILE* fp)
{
	Node*    entity;	
	void*    data;
	long int hash;	
	vtypes   dataType;
	uint8_t  byte;	
	uint32_t size;


	// Entity Hash size in bytes
	size = fgetc(fp);

	for (uint32_t i = 0; i < size; i++) {
		byte = fgetc(fp);	
		hash = (hash |= byte) << 8;		
	}	

	printf("\nHash: %li \n", hash);

	// Data size in bytes
	size = fgetc(fp);

	fread(data, size, 1, fp);	

	// Data Type size in bytes 
	dataType = fgetc(fp);	
}
