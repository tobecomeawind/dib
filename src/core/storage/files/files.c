#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "files.h"

unsigned char SOURCE_PATH[SOURCE_PATH_MAX_SIZE];


int saveSourceDirPath (void)
{
	if ( !getcwd(SOURCE_PATH, SOURCE_PATH_MAX_SIZE) ) {
		return -1;
	}

	return 0;
}

void clearFile(const char* subdir)
{
	char* path = createPath(subdir);
	FILE* tmp  = fopen(path, "w");
	
	fclose(tmp);
	free(path);
}

char* createPath(const char* subdir)
{	
	if ( !subdir ) return NULL;
	
	uint8_t len = strlen(SOURCE_PATH) + strlen(subdir) + 1;
	char*   res = malloc(len);
	
	if ( !res ) return NULL;

	strcpy(res, SOURCE_PATH);
	strcat(res, subdir);	

	return res;
}

