#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "node.h"
#include "hash.h"
#include "graph.h"
#include "serialization.h"
#include "deserialization.h"

int main(void)
{	
	Node *Tom, *Lucy;
	Graph* g;	
	//HashTable* table;

	initEntitiesTempTable();	

	Tom  = nodeConstructCli("Personallity", "Tom",  K_CHAR);		
	Lucy = nodeConstructCli("MustafaBlya", "Lucy",  K_CHAR);	
		
	g = graphInit(Tom);

	linkNodes(g, Tom,  Lucy, "Loved_In");
	linkNodes(g, Lucy, Tom,  "Loved_In");

	/*
	testnptr = (Node**) calloc(2, sizeof(Node*));
	testnptr[0] = Tom;	
	testnptr[1] = Lucy;	
	entityArraySerialize(testnptr, 2);
	*/

	//hashTableSerialize(table);
	//table = hashTableDeserialize();	

	/*
	add_relation(Tom,
			     relation_construct("Loves",
				 Lucy));	

	add_relation(Lucy,
			     relation_construct("Loves",
				 Tom));	

	*/

	
	return 0;
}


