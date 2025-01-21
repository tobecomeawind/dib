#ifndef FILES_H
#define FILES_H

#define REL_TEMP_FILE  "/data/tmp/rel_entities.tmp"
#define NODE_TEMP_FILE "/data/tmp/node_entities.tmp"
#define DATA_TEMP_FILE "/data/data.dib"

#define SOURCE_PATH_MAX_SIZE 255

void  clearFile (const char* subdir);
char* createPath(const char* subDir);
int   saveSourceDirPath (void);


#endif
