#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "node.h"
#include "hash.h"
#include "serialization.h"
#include "deserialization.h"

int main(void)
{	
	Node *Tom, *Lucy;	
	HashTable* table;	
	/*	
	HashTable* table = hashTableInit(2);

	Tom  = nodeConstructFromCli("Personallity", "Tom",  K_CHAR);		
	Lucy = nodeConstructFromCli("MustafaBlya", "Lucy", K_CHAR);	
	
	hashTableInsert(table, Tom->type);
	hashTableInsert(table, Lucy->type);
	*/

	/*
	testnptr = (Node**) calloc(2, sizeof(Node*));
	testnptr[0] = Tom;	
	testnptr[1] = Lucy;	
	entityArraySerialize(testnptr, 2);
	*/

	//hashTableSerialize(table);
	table = hashTableDeserialize();	

	/*
	add_relation(Tom,
			     relation_construct("Loves",
				 Lucy));	

	add_relation(Lucy,
			     relation_construct("Loves",
				 Tom));	

	*/

	//nodeDestruct(Tom);
	//nodeDestruct(Lucy);
	hashTableDestruct(table);	
	
	return 0;
}


