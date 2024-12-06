#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "deserialization.h"
#include "files.h"

Node** getEntitiesArray(void)
{
	FILE*    tmpfp;
	int8_t   countEntities;
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
	//----------------------------------------
	// Create entity from bytes data to struct
	//----------------------------------------

	Node*    entity;	
	void*    data;
	uint64_t hash = 0;	
	vtypes   dataType;
	
	uint8_t  byte;	
	uint32_t chunkSize; // size of chunk 
						// such in file
						//   ...|Size_Of_Data_Of_Entity|data_of_Entity|...
						//              ||                    || 
						//            chunkSize              hash 
						//        1byte with size       chunkSize bytes
						//               sizeof(hash) = chunkSize


	// Entity Hash size in bytes
	chunkSize = fgetc(fp);
	
	// skip last iteration 
	// cause we don't need move last byte
	for (;chunkSize-- > 1;) {
		byte = fgetc(fp);
		hash = (hash |= byte) << 8;	
	}	
	hash = (hash |= (byte = fgetc(fp))); 

	// Data size in bytes
	chunkSize = fgetc(fp);

	data = malloc(chunkSize);
	fread(data, 1, chunkSize, fp);	

	// Data Type size in bytes 
	dataType = fgetc(fp);	

	printf("\nEntity hash: %lli Data: %s\n", hash, (char*)data);		

	entity = nodeConstruct(NULL, hash, data, dataType);		

	//return NULL;
}
