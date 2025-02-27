#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "deserialization.h"
#include "entity_type.h"
#include "hash.h"


static HashNode*   hashNodeDeserialize (FILE* tmpfp);
static EntityType* entityDeserialize   (FILE* fp);


HashTable* hashTableDeserialize (const char* filename)
{
	if ( !filename ) return NULL;
	
	FILE*      tmpfp;
	int8_t     hashTableSize;
	HashTable* table;
	HashNode*  tableNode;

	tmpfp = fopen(filename, "r");

	if ( !tmpfp ) { // if file not exist we create him
		tmpfp = fopen(filename, "w");
		fclose(tmpfp);
		return NULL;
	}
	
	hashTableSize = fgetc(tmpfp);

	if ( hashTableSize == EOF ) {  // if file without data
		fclose(tmpfp);	
		return NULL;
	}

	table = hashTableInit(hashTableSize);

	for (uint8_t i = 0; i < hashTableSize; i++) {
 
		tableNode = hashNodeDeserialize(tmpfp);

		table->array[i] = tableNode;	
	}	
	
	fclose(tmpfp);

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
	else
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
	
	name = (char*) malloc(chunkSize + 1);
	name[chunkSize]	= '\0';
	
	fread(name, 1, chunkSize, fp);

	entity = entityTypeConstruct(name, hash);	

	free(name);
	return entity;
}

