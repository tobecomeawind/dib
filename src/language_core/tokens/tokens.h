#ifndef TOKENS_H
#define TOKENS_H

#include <stdint.h>

typedef enum
{
	//KEYWORDS
	CHAR,
	ENTITY,
	ENTITIES,
	FLOAT,
	INT,
	LINK,	


	NAME,
	WHITE_SPACE,

	OPEN_PARENS,   // (
	CLOSE_PARENS,  // )	
	
	COLON,          // :

} Tokens;

typedef struct {
	Tokens       type;
	const char  *data;	
} Token;


int isKeyword   (char *word);
int isParenses  (char *c);
int isColon     (char *c);
int isWhiteSpace(char *c);

#endif
