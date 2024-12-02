#include <stdio.h>
#include <stdint.h>

#include "deserialization.h"
#include "files.h"

Node** getEntitiesArray(void)
{
	FILE*    tmpfp;
	uint8_t  countEntities;

	tmpfp = fopen(TEMP_FILE, "r");	

	if (!tmpfp) {
		printf("\nEntities Temp file didn't created yet\n");	
		return 0;
	}

	if ((countEntities = fgetc(tmpfp)) == EOF) 
		return NULL;

		
	fclose(tmpfp);
}

