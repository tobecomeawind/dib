#include "tokens.h"
#include "algs.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Token* isKeyword(char *word)
{
	//--------------------------
	//Check the word is keyword
	//else 
	//word == name of something
	//--------------------------

	int8_t  index, size;
	Token   *tptr, keyword; // token pointer

	Token keywords[] = { // Keyword tokens
		{.minorType = K_CHAR,     .data = "CHAR"},
		{.minorType = K_ENTITIES, .data = "ENTITIES"},
		{.minorType = K_ENTITY,   .data = "ENTITY"},
		{.minorType = K_FLOAT,    .data = "FLOAT"},
		{.minorType = K_INT,      .data = "INT"},
		{.minorType = K_LINK,     .data = "LINK"},
	};
	
	size = sizeof(keywords) / sizeof(Token); 
	// return keyword token if word in keywords else 0
	index = binsearch((void**)keywords, size, (void*)word, bsTOKEN);	

	keyword = keywords[index];

	if(index < 0){
		return NULL;
	}

	tptr = malloc(sizeof(Token));
	memcpy(tptr, &keyword, sizeof(keyword));

	tptr->majorType = KEYWORDS;

	/*	
	tptr       = malloc(sizeof(Token));
	tptr->data = malloc(sizeof(char*));

	tptr->type = keyword.type; 
	while(*tptr->data++ = *keyword.data++);	
	*/	
	
	//memcpy((char*)tptr->data, (char*)keyword.data, sizeof(strlen(keyword.data)));


	return tptr;
}


bool isParenses(char *c)
{
	return *c == '(' || *c == ')';
};

bool isColon(char *c)
{
	return *c == ':';
};

bool isComma(char *c)
{
	return *c == ',';
};

bool isWhiteSpace(char *c)
{
	return *c == ' ' || *c == '\t';
};

