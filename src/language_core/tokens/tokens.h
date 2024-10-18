#ifndef TOKENS_H
#define TOKENS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	//KEYWORDS
	K_ENTITY,
	K_ENTITIES,
	K_LINK,	

	DATATYPE,
	K_CHAR,
	K_FLOAT,
	K_INT,

	NAME,
	WHITE_SPACE,   // 

	OPEN_PARENS,   // (
	CLOSE_PARENS,  // )	
	
	COLON,         // :
	COMMA,         // ,

} Tokens;


typedef struct {
	Tokens       type;
    char        *data;	
} Token;


Token  *isKeyword   (char *word);
bool    isParenses  (char *c);
bool    isColon     (char *c);
bool    isWhiteSpace(char *c);
bool    isComma     (char *c);

#endif
