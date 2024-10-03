#include "types.h"

#ifndef GRAPH_H
#define GPAPH_H

typedef struct Node Node;         // relationship between relation and node
typedef struct Relation Relation; // relationship between relation and node
typedef struct Data Data;         // relationship between relation and node

typedef struct Relation{
	char* name;     // name of relation
	Node* parent;   // parent   structure
	Node* child;	// children structure
		
	// film1<----- (relation) -----/ tom  \----- (relation) ----> England
	//(child)    name:Acted_IN    |(parent)|    name:Live_IN       (child)

	//void (*create  )(char* name, Node* parent, Node* child); 
	void (*destruct)(Relation* rel); 

} Relation;


typedef struct Data{
	vtypes  type;
	void*   info;

	void (*destruct)(Data* data);
} Data;

typedef struct NodeVtable {
		
	//Node* (*construct   )(Data* data, Relation* rel);
	void  (*destruct    )(Node* node);
	void  (*add_relation)(Node* node, Relation* rel);
	void  (*del_relation)(Node* node, Relation* rel);

} NodeVtable;

typedef struct Node{
	Data*       data;      //         
	Relation**  relations; // 
	size_t      rsize;     // relations size      
	NodeVtable* vtable;	   // virtual table with 
} Node;



Node* node_construct(Data* data);
void  node_destruct (Node* node);

Data* data_construct(void* data, uint8_t type);
void  data_destruct (Data* dptr);

Relation* relation_construct(char* name, Node* parent, Node* child);
void      relation_destruct (Relation* rptr);

void add_relation(Node* node, Relation* rel);

#endif
