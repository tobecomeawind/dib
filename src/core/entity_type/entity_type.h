#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

#include <stdint.h>

typedef struct EntityType{ // Entity = Node || Relation
	char     *typename;
	uint64_t  hash;
} EntityType;

#endif
