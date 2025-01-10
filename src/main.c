#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include "node.h"
#include "hash.h"
#include "graph.h"
#include "serialization.h"
#include "deserialization.h"

char* createPath(const char* subDir);

#define SOURCE_PATH_MAX_SIZE 255
unsigned char SOURCE_PATH[SOURCE_PATH_MAX_SIZE];


int main(void)
{			
	if ( !getcwd(SOURCE_PATH, SOURCE_PATH_MAX_SIZE) ) {
		printf("\nInvalid source path\n");
		return -1;
	}
		
	Node *Tom, *Lucy;
	Graph* g;	
	//HashTable* table;

	
	initNodeEntitiesTempTable();	
	initRelEntitiesTempTable();

	Tom  = nodeConstructTmp("Personallity", "Tom",  K_CHAR);		
	Lucy = nodeConstructTmp("MustafaBlya", "Lucy",  K_CHAR);	

	Node* Node1 = nodeConstructTmp("test1", "Node", K_CHAR);

	Node* Node11 = nodeConstructTmp("test11", "Node", K_CHAR);
	Node* Node12 = nodeConstructTmp("test12", "Node", K_CHAR);

	Node* Node111 = nodeConstructTmp("test111", "Node", K_CHAR);
	Node* Node112 = nodeConstructTmp("test112", "Node", K_CHAR);
	
	Node* Node121 = nodeConstructTmp("test121", "Node", K_CHAR);
	Node* Node122 = nodeConstructTmp("test122", "Node", K_CHAR);


	g = graphInit(Node1);
	
	addNode(g, Tom);
	addNode(g, Tom);
	addNode(g, Lucy);

	addNode(g, Node1);
	addNode(g, Node11);
	addNode(g, Node12);
	addNode(g, Node111);
	addNode(g, Node112);
	addNode(g, Node121);
	addNode(g, Node122);

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



char* createPath(const char* subDir)
{	
	if ( !subDir ) return NULL;
	
	uint8_t len = strlen(SOURCE_PATH) + strlen(subDir) + 1;
	char*   res = malloc(len);
	
	if ( !res ) return NULL;

	strcpy(res, SOURCE_PATH);
	strcat(res, subDir);	

	return res;
}

