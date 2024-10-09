#include "tokens.h"
#include <string.h>
#include <stdio.h>

#include "algs.h"

int isKeyword(char *word)
{
	//--------------------------
	//Check the word is keyword
	//else 
	//word == name of something
	//--------------------------

	char* keywords[] = { // All tokens
		"ENTITY",
		"RELATION",
		"SPAWN",
	};

	// return 1 if word in keywords else 0
	return binsearch((void**)keywords, 3, (void*)word, CHAR);	
}
