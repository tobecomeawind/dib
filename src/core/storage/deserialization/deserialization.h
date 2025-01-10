#ifndef DESERIALIZATION_H
#define DESERIALIZATION_H

#include "node.h"
#include "hash.h"
#include "files.h"

HashTable* hashTableDeserialize (const char* filename);

#endif
