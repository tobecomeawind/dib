#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdint.h>
#include <stdio.h>

// Start points if entity data
// Example of file:
//    COUNT_OF_ENTITIES|ENTITY_TYPE|DATA_OF_ENTITY_TYPE|DATA|DATA_OF_DATA|DATA_TYPE|DATA_OF_DATA_TYPE
//          1 byte         1 byte       n bytes         1b     n bytes     1 byte    1 byte
#define ENTITY_TYPE 0b00000001
#define DATA        0b00000010
#define DATA_TYPE   0b00000100

void nodeSerialize     (Node* node, FILE* fp);
void nodeArraySerialize(Node** nodeArray, size_t arraySize);

#endif
