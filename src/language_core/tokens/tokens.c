#include "tokens.h"
#include "algs.h"

#include <string.h>
#include <stdio.h>



Token* isKeyword(char *word)
{
	//--------------------------
	//Check the word is keyword
	//else 
	//word == name of something
	//--------------------------

	int8_t index, size;
	Token   *tptr; // token pointer

	Token keywords[] = { // Keyword tokens
		{.type = K_CHAR,     .data = "CHAR"},
		{.type = K_ENTITIES, .data = "ENTITIES"},
		{.type = K_ENTITY,   .data = "ENTITY"},
		{.type = K_FLOAT,    .data = "FLOAT"},
		{.type = K_INT,      .data = "INT"},
		{.type = K_LINK,     .data = "LINK"},
	};
	
	size = sizeof(keywords) / sizeof(Token); 
	// return keyword token if word in keywords else 0
	index = binsearch((void**)keywords, size, (void*)word, bsTOKEN);	

	if(index < 0){
		return NULL;
	}

	tptr = &(keywords[index]);

	return tptr;
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




