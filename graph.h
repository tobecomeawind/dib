#include "types.h"

#ifndef GRAPH_H
#define GPAPH_H

typedef struct Node Node;         // relationship between relation and node
typedef struct Relation Relation; // relationship between relation and node
typedef struct Data Data;         // relationship between relation and node

typedef struct Relation{
	char* name;         // name of relation
//	Node* parent;       // parent   structure
	Node* dest;	// children structure
		
	// film1<----- (relation) -----/ tom  \----- (relation) ----> England
	//(dest)    name:Acted_IN                  name:Live_IN       (dest)

	//void (*create  )(char* name, Node* parent, Node* child); 
	void (*destruct)(Relation* rel); 

} Relation;


typedef struct Data{
	vtypes  type;
	void*   info;

	void (*destruct)(Data* data);
} Data;

typedef struct EntityType{ // Entity = Node || Relation
	char     *typename;
	long int  hash;
} EntityType;

typedef struct NodeVtable {
		
	//Node* (*construct   )(Data* data, Relation* rel);
	void  (*destruct    )(Node* node);
	void  (*add_relation)(Node* node, Relation* rel);
	void  (*del_relation)(Node* node, Relation* rel);

} NodeVtable;

typedef struct Node{
	EntityType* type;	
	
	//char*       name;      // name of Node(Game, Person, City)
	//long int    nhash;     // hash(name)

	Data*       data;      // data ((Tom, CHAR), (23, INT), (3.14, FLOAT))
	Relation**  relations; // 
	size_t      rsize;     // relations size      
	NodeVtable* vtable;	   // virtual table with 
} Node;



Node* node_construct(char* name, Data* data);
void  node_destruct (Node* node);

Data* data_construct(void* data, uint8_t type);
void  data_destruct (Data* dptr);

Relation* relation_construct(char* name, Node* destination);
void      relation_destruct (Relation* rptr);

void add_relation(Node* node, Relation* rel);

#endif
