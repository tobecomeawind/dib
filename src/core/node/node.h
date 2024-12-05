#ifndef NODE_H
#define NODE_H

#include "entity_type.h"
#include "data.h"
#include "relation.h"

#include <stddef.h>
#include <stdint.h>

typedef struct Node{
	EntityType* type;	
	
	Data*       data;      // data ((Tom, CHAR), (23, INT), (3.14, FLOAT))
	Relation**  relations; // 
	size_t      rsize;     // relations size      

} Node;


Node* nodeConstructFromCli(char* name, char *data, Tokens dataTypeToken);
Node* nodeConstruct(char*    name,
                     uint64_t hashValue,
                     void*    data,
                     Tokens   dataTypeToken);
void  nodeDestruct (Node* node);

void add_relation(Node* node, Relation* rel);

#endif
