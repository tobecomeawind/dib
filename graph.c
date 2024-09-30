#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>


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
	uint8_t type;
	void*   info;

	void (*destruct)(Data* data);
} Data;

typedef struct Node{
	Data*      data;      //         
	Relation** relations; // 
	size_t     rsize;     // relations size      
	
	//Node* (*construct     )(Data* data, Relation* rel);
	void  (*destruct      )(Node* node);
	void  (*add_relation  )(Node* node, Relation* rel);
	void  (*del_relation  )(Node* node, Relation* rel);

} Node;



Node* node_construct(Data* data);
void  node_destruct (Node* node);

Data* data_construct(void* data, uint8_t type);
void  data_destruct (Data* dptr);

Relation* relation_construct(char* name, Node* parent, Node* child);
void      relation_destruct (Relation* rptr);

void add_relation(Node* node, Relation* rel);

int main(void)
{
	//Need to fix memory	
	
	Node* root;
	Node* root1;
	Node* root2;
	
	int     a = 8;
	uint8_t b = 1;	

	root  = node_construct(data_construct((void*)(&a), b));	
	root1 = node_construct(data_construct((void*)(&a), b));	
	root2 = node_construct(data_construct((void*)(&a), b));	
	
	root->add_relation(root,
			           relation_construct("Root to Root 1", 
								           root,   root1));	
	root1->add_relation(root1,
		                relation_construct("Root1 to Root 2", 
							                root1,    root2));	
	root2->add_relation(root2, 
			            relation_construct("Root2 to Root ", 
							                root2,   root));	
	
	root->destruct(root);
	root1->destruct(root1);
	root2->destruct(root2);

	return 0;
}


Node* node_construct(Data* data)
{
	Node* nptr;	// node pointer
	
	nptr = (Node*) malloc(sizeof(Node));

	//nptr->data         = data_construct(data);
	nptr->data         = data;
	nptr->rsize        = 0;
	nptr->relations    = (Relation**) malloc(sizeof(Relation*));
	nptr->destruct     = &node_destruct;
	nptr->add_relation = &add_relation;
	nptr->del_relation = NULL;

	return nptr;
}

void node_destruct(Node* node)
{
	(node->data)->destruct(node->data);
	
	for(size_t i = 0; i < node->rsize; i++)
		(node->relations[i])->destruct(node->relations[i]);	
	
	free(node->relations);
	free(node);
}


Data* data_construct(void* data, uint8_t type)
{
	Data* dptr; // data pointer	
	
	dptr = (Data*) malloc(sizeof(Data));

	dptr->type     = type;
	dptr->info     = data;	
	dptr->destruct = &data_destruct;

	return dptr;
}

void data_destruct(Data* dptr)
{
	free(dptr);	
}

Relation* relation_construct(char* name, Node* parent, Node* child)
{
	Relation* rptr; // relation pointer	
	
	rptr = (Relation*) malloc(sizeof(Relation));

	rptr->name     = name;
	rptr->parent   = parent;	
	rptr->child    = child;
	rptr->destruct = &relation_destruct;

	return rptr;
}

void relation_destruct(Relation* rptr)
{
	free(rptr);	
}

void add_relation(Node* node, Relation* rel)
{	
	node->relations[node->rsize++] = rel;

	node->relations = realloc(node->relations, node->rsize);
}

