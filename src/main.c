#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "node.h"


int main(void)
{	
	Node *Tom, *Lucy;	
	Node** testnptr; 

	Tom  = nodeConstructFromCli("Person", "Tom",  K_CHAR);		
	Lucy = nodeConstructFromCli("MustafaBlya", "Lucy", K_CHAR);	
		
	testnptr = (Node**) calloc(2, sizeof(Node*));
	testnptr[0] = Tom;	
	testnptr[1] = Lucy;	
	entityArraySerialize(testnptr, 2);
		
	/*
	add_relation(Tom,
			     relation_construct("Loves",
				 Lucy));	

	add_relation(Lucy,
			     relation_construct("Loves",
				 Tom));	

	
	node_destruct(Tom);
	node_destruct(Lucy);
	*/	
	return 0;
}


