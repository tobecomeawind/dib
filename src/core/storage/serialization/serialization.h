#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdint.h>
#include <stdio.h>

#include "hash.h"
#include "files.h"

//void entitySerialize     (Node* node, FILE* fp);
void hashTableSerialize  (HashTable* table, const char* filename);
//void entityArraySerialize(Node** nodeArray, size_t arraySize);

#endif
