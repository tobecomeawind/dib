#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "node.h"


int main(void)
{	
	Node *Tom, *Lucy;	

	//Tom  = node_construct("Person", "Tom",  K_CHAR);	
	
	Lucy = node_construct("Person", "Lucy", K_CHAR);	
	
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


