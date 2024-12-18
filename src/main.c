#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "node.h"
#include "hash.h"
#include "serialization.h"

int main(void)
{	
	Node *Tom, *Lucy;	
	Node** testnptr; 

	HashTable* table = hashTableInit(2);

	Tom  = nodeConstructFromCli("Person", "Tom",  K_CHAR);		
	Lucy = nodeConstructFromCli("MustafaBlya", "Lucy", K_CHAR);	
	
	hashTableInsert(table, Tom);
	hashTableInsert(table, Lucy);
	hashTableInsert(nodeConstructFromCli("Person"));	

	/*
	testnptr = (Node**) calloc(2, sizeof(Node*));
	testnptr[0] = Tom;	
	testnptr[1] = Lucy;	
	entityArraySerialize(testnptr, 2);
	*/

	hashTableSerialize(table);

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


