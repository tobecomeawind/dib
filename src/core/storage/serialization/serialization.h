#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdint.h>
#include <stdio.h>

void entitySerialize     (Node* node, FILE* fp);
void entityArraySerialize(Node** nodeArray, size_t arraySize);

#endif
