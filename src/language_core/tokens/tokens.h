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
	NAME, 
	
	EXIT,

} Tokens;


typedef struct token_t {

	Tokens       majorType; 
	Tokens       minorType;
    char*        data;

} Token;

Token* tokenConstruct (Tokens major, Tokens minor, char* data);
void   tokenDestruct  (Token* tptr);

bool   isKeyword   (char *word, Token* tptr);
bool   isParenses  (char *c);
bool   isColon     (char *c);
bool   isWhiteSpace(char *c);
bool   isComma     (char *c);
bool   isAlNum     (char *c);

char*  convertTokenToString(Tokens token);

#endif
