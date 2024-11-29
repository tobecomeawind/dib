#ifndef NODE_H
#define NODE_H

#include "entity_type.h"
#include "data.h"
#include "relation.h"

#include <stddef.h>

typedef struct Node{
	EntityType* type;	
	
	Data*       data;      // data ((Tom, CHAR), (23, INT), (3.14, FLOAT))
	Relation**  relations; // 
	size_t      rsize;     // relations size      

} Node;


Node* node_construct(char* name, char* data, Tokens dataTypeToken);
void  node_destruct (Node* node);

void add_relation(Node* node, Relation* rel);

#endif
