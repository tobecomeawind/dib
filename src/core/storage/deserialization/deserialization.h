#ifndef DESERIALIZATION_H
#define DESERIALIZATION_H

#include "node.h"

Node** getEntitiesArray(void);
static Node* entityDeserialize(FILE* fp);

#endif
