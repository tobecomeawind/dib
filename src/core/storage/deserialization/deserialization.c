#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "deserialization.h"
#include "files.h"
#include "entity_type.h"
#include "hash.h"


static HashNode*   hashNodeDeserialize (FILE* tmpfp);
static EntityType* entityDeserialize   (FILE* fp);


HashTable* hashTableDeserialize (void)
{
	FILE*      tmpfp;
	uint8_t    hashTableSize;
	HashTable* table;
	HashNode*  tableNode;

	tmpfp = fopen(TEMP_FILE, "r");

	if (!tmpfp) return NULL;

	hashTableSize = fgetc(tmpfp);

	if (hashTableSize == EOF) return NULL;

	table = hashTableInit(hashTableSize);

	for (uint8_t i = 0; i < hashTableSize; i++) {
 
		tableNode = hashNodeDeserialize(tmpfp);

		table->array[i] = tableNode;	
	}	
	
	return table;
}


static HashNode* hashNodeDeserialize (FILE* tmpfp)
{
	uint8_t     flag;	
	HashNode*   hnptr;
	EntityType* etptr;
	
	etptr = entityDeserialize(tmpfp);

	hnptr = hashNodeConstruct(etptr);

	if ( (flag = getc(tmpfp)) == '>' )
		hnptr->next = hashNodeDeserialize(tmpfp);	
	
	ungetc(flag, tmpfp);
	
	return hnptr;
}


static EntityType* entityDeserialize(FILE* fp)
{
	//----------------------------------------
	// Create entity from bytes data to struct
	//----------------------------------------

	EntityType* entity;	
	char*       name;
	uint64_t    hash = 0;	
	
	uint8_t  byte;	
	uint32_t chunkSize; // size of chunk 
						// such in file
						//   ...|Size_Of_Data_Of_Entity|data_of_Entity|...
						//              ||                    || 
						//            chunkSize              hash 
						//        1byte with size       chunkSize bytes
						//               sizeof(hash) = chunkSize


	// Entity Hash size in bytes
	chunkSize = getc(fp);
	
	if ( !chunkSize ) return NULL; 

	// skip last iteration 
	// cause we don't need move last byte
	for (;chunkSize-- > 1;) {
		byte = fgetc(fp);
		hash = (hash |= byte) << 8;	
	}	
	hash = (hash |= (byte = fgetc(fp))); 

	// Data size in bytes
	chunkSize = fgetc(fp);

	name = (char*) malloc(chunkSize);

	fread(name, 1, chunkSize, fp);		

	//printf("\nEntity hash: %lli Data: %s\n", hash, (char*)data);		

	entity = entityTypeConstruct(name, hash);	

	return entity;
}




/*
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
		entitiesArray[i] = entityDeserialize(tmpfp);	
	}

	fclose(tmpfp);

	return entitiesArray;
}
*/
