#ifndef NODE_H
#define NODE_H

#include <stddef.h>
#include <stdint.h>

#include "entity_type.h"
#include "data.h"
#include "relation.h"

typedef struct node_t {

	EntityType* type;	

	uint8_t     id;        // for graph serialization and deserialization

	Data*       data;      // data ((Tom, CHAR), (23, INT), (3.14, FLOAT))
	Relation**  relations; // 
	size_t      rsize;     // relations size      

} Node;


Node* nodeConstructTmp(char* name, char* data, Tokens dataTypeToken);
Node* nodeConstruct(char*    name,
                    uint64_t hashValue,
                    void*    data,
                    Tokens   dataTypeToken);

void  nodeDestruct (Node* node);

void addRelation(Node* node, Relation* rel);

#endif
