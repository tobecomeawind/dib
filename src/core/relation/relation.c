#include <stdlib.h>

#include "relation.h"
#include "hash.h"
#include "node.h"
#include "graph.h"
#include "files.h"

static Relation* relationConstruct_iml (EntityType* etptr, Node* destination);

Relation* relationConstructTmp(const char* name, Node* destination)
{	
	EntityType* etptr = relEntityTypeConstructTmp(name,
                                                  hash(name),
                                                  REL_TEMP_FILE);

	if ( !etptr ) return NULL;
	
	Relation* rptr = relationConstruct_iml(etptr, destination);

	if ( !rptr ) {
		entityTypeDestruct(etptr);
		return NULL;
	}

	return rptr;
}

Relation* relationConstruct(const char* name, Node* destination)
{	
	EntityType* etptr = entityTypeConstruct(name, hash(name));
	if ( !etptr ) return NULL;
	
	Relation* rptr = relationConstruct_iml(etptr, destination);

	if ( !rptr ) {
		entityTypeDestruct(etptr);
		return NULL;
	}

	return rptr;
}


static Relation* relationConstruct_iml (EntityType* etptr, Node* destination)
{
	if ( !etptr || !destination ) return NULL;

	Relation* rptr = (Relation*) malloc(sizeof(Relation));

	if ( !rptr ) return NULL;
	
	rptr->type = etptr;
	rptr->dest = destination;

	return rptr;
}


void relationDestruct(Relation* rptr)
{
	free(rptr);	
}
