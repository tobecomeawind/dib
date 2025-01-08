#ifndef RELATION_H
#define RELATION_H

#include "entity_type.h"
typedef struct node_t Node;

typedef struct relation_t{
	
	EntityType* type;	
	
	Node* dest;	// children structure
		
	// film1<----- (relation) -----/ tom  \----- (relation) ----> England
	//(dest)    name:Acted_IN                  name:Live_IN       (dest)

} Relation;

Relation* relationConstruct(const char* name, Node* destination);
void      relationDestruct (Relation* rptr);

#endif
