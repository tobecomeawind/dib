#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include "node.h"
#include "hash.h"
#include "graph.h"
#include "serialization.h"
#include "deserialization.h"
#include "language_core.h"

static inline void initBuffers (void); 
static inline void destructBuffers (void);


int main(void)
{					
	if ( saveSourceDirPath() != 0) {
		printf("\nInvalid source path\n");
		return -1;	
	}


	int8_t cliStatusCode;
	
	initBuffers();	
	
	cliStatusCode = languageCoreStart();	
	
	switch ( cliStatusCode ) {
		case ( -1 ):
			destructBuffers();
			printf("\nGoodbye!\n\n");
			break;
	}
	
	return 0;
}


static inline void initBuffers (void) 
{
	initNodeEntitiesTempTable();	
	initRelEntitiesTempTable();
	initMainGraph();
}

static inline void destructBuffers (void)
{
	destructNodeEntitiesTempTable();	
	destructRelEntitiesTempTable();
	destructMainGraph();	
}

