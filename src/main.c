#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "node.h"


int main(void)
{	
	Node *Tom, *Lucy;	

	Tom  = node_construct("Person",
			              data_construct((void*)"Tom",
					      CHAR));	
	
	Lucy = node_construct("Person",
			              data_construct((void*)"Lucy",
						  CHAR));	

	add_relation(Tom,
			     relation_construct("Loves",
				 Lucy));	

	add_relation(Lucy,
			     relation_construct("Loves",
				 Tom));	

	
	node_destruct(Tom);
	node_destruct(Lucy);
	
	return 0;
}


