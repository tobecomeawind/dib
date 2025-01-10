#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

#include <stdint.h>

typedef struct entity_type_t{ // Entity = Node || Relation

	char     *typeName;
	uint64_t  hashVal;

} EntityType;

EntityType* entityTypeConstruct(const char* typeName, uint64_t hash);
EntityType* nodeEntityTypeConstructTmp (const char* typeName,
                                        uint64_t    hashValue,
                                        const char* subdir);
void        entityTypeDestruct (EntityType* fuckYou);

void printEntities (void);

void initNodeEntitiesTempTable     (void);
void destructNodeEntitiesTempTable (void);

EntityType* searchByHashNodeEntitiesTempTable (uint64_t hashValue);

#endif
