#ifndef TOKENS_H
#define TOKENS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	//KEYWORDS include KEYWORDS and DATATYPE

	KEYWORDS = 1,

	K_ENTITY,
	K_ENTITIES,
	K_LINK,	


	DATATYPE, 
	
	K_CHAR,
	K_FLOAT,
	K_INT,


	BORDERS,

	OPEN_PARENS,   // (
	CLOSE_PARENS,  // )	


	CLETTERS, //CHAR LETTERS

	COLON,         // :
	COMMA,         // ,
	WHITE_SPACE,   // 

	
	
	//OTHERS
	NAME


} Tokens;

typedef struct {
	Tokens       majorType; 
	Tokens       minorType;
    char        *data;	
} Token;


Token *isKeyword   (char *word);
bool   isParenses  (char *c);
bool   isColon     (char *c);
bool   isWhiteSpace(char *c);
bool   isComma     (char *c);
bool   isAlNum     (char *c);

#endif
