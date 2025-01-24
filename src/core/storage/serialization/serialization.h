#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdint.h>
#include <stdio.h>

#include "hash.h"
#include "files.h"
#include "graph.h"

void hashTableSerialize  (HashTable* table, const char* filename);
void graphSerialize      (Graph*     gptr,  const char* filename);

#endif
