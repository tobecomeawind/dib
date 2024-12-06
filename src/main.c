#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "node.h"


int main(void)
{	
	Node *Tom, *Lucy;	
	Node** testnptr; 

	//Tom  = node_construct("Person", "Tom",  K_CHAR);	
	
	Lucy = nodeConstructFromCli("MustafaBlya", "Lucy", K_CHAR);	
		
	testnptr = &Lucy;	
	entityArraySerialize(testnptr, 1);
		
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


