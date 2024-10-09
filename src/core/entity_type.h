#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

typedef struct EntityType{ // Entity = Node || Relation
	char     *typename;
	long int  hash;
} EntityType;

#endif
