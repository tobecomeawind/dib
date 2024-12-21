#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

#include <stdint.h>


typedef struct { // Entity = Node || Relation

	char     *typename;
	uint64_t  hashVal;

} EntityType;

EntityType* entityTypeConstruct(char* name, uint64_t hash);
void        entityTypeDestruct (EntityType* fuckYou);

void initEntitiesTempTable (void);

#endif
