#ifndef TOKENS_H
#define TOKENS_H

#include <stdint.h>

typedef enum
{
	//KEYWORDS
	KEYWORDS	
	K_ENTITY,
	K_ENTITIES,
	K_LINK,	

	DATATYPE,
	K_CHAR,
	K_FLOAT,
	K_INT,

	NAME,
	WHITE_SPACE,

	OPEN_PARENS,   // (
	CLOSE_PARENS,  // )	
	
	COLON,          // :

} Tokens;

typedef struct {
	Tokens       type;
    char        *data;	
} Token;


Token *isKeyword   (char *word);
int    isParenses  (char *c);
int    isColon     (char *c);
int    isWhiteSpace(char *c);

#endif
