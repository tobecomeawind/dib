#ifndef RELATION_H
#define RELATION_H

#include "entity_type.h"

typedef struct Node Node;

typedef struct Relation{
	
	EntityType* type;	
	
	Node* dest;	// children structure
		
	// film1<----- (relation) -----/ tom  \----- (relation) ----> England
	//(dest)    name:Acted_IN                  name:Live_IN       (dest)

} Relation;

Relation* relation_construct(char* name, Node* destination);
void      relation_destruct (Relation* rptr);

#endif
