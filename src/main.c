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

	Node* Node1 = nodeConstructCli("test", "Node", K_CHAR);

	Node* Node11 = nodeConstructCli("test", "Node", K_CHAR);
	Node* Node12 = nodeConstructCli("test", "Node", K_CHAR);

	Node* Node111 = nodeConstructCli("test", "Node", K_CHAR);
	Node* Node112 = nodeConstructCli("test", "Node", K_CHAR);
	
	Node* Node121 = nodeConstructCli("test", "Node", K_CHAR);
	Node* Node122 = nodeConstructCli("test", "Node", K_CHAR);


	g = graphInit(Node1);

	
	linkNodes(g, Node1, Node11, "empty");
	linkNodes(g, Node11, Node111, "empty");
	linkNodes(g, Node111, Node122, "empty");
	linkNodes(g, Node122, Node1, "empty");


	linkNodes(g, Node122, Tom, "empty");

	// Tree
	/*
	linkNodes(g, Node1, Node11, "Parent_Of");
	linkNodes(g, Node1, Node12, "Parent_Of");
		
	linkNodes(g, Node11, Node111, "Parent_Of");
	linkNodes(g, Node11, Node112, "Parent_Of");

	linkNodes(g, Node12, Node121, "Parent_Of");
	linkNodes(g, Node12, Node122, "Parent_Of");

	linkNodes(g, Node122, Node1, "Parent_Of");
	
	linkNodes(g, Node122, Tom, "Parent_Of");
	
	linkNodes(g, Tom, Lucy, "Parent_Of");
	*/
	
	return 0;
}


