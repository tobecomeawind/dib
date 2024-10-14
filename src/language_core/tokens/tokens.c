#include "tokens.h"
#include "algs.h"

#include <string.h>
#include <stdio.h>



int isKeyword(char *word)
{
	//--------------------------
	//Check the word is keyword
	//else 
	//word == name of something
	//--------------------------

	char* keywords[] = { // All tokens
		"CHAR",
		"ENTITY",
		"ENTITIES",
		"FLOAT",
		"INT",
		"LINK",
	};

	// return 1 if word in keywords else 0
	return binsearch((void**)keywords, 6, (void*)word, CHAR);	
}


int isParenses(char *c)
{
	return *c == '(' || *c == ')';
};

int isColon(char *c)
{
	return *c == ':';
};

int isWhiteSpace(char *c)
{
	return *c == ' ' || *c == '\t';
};




