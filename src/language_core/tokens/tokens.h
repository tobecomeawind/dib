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
	LINK,          // link
	DLINK,         // double link

		
	//OTHERS
	NAME, 
	
	EXIT,

} Tokens;


typedef struct token_t {

	Tokens       majorType; 
	Tokens       minorType;
    char*        data;

} Token;

void appendToken (Tokens majType, // majorType
                  Tokens minType, // minorType
                  char*  data);   // word

void initTokensBuf     (void);
void freeTokensBuf     (void);
void initTokensTempBuf (void);
void freeTokensTempBuf (void);

Token* getToken(void);
void ungetToken(Token *token);
void shiftTokensBufPointer (void); 



bool isKeyword   (char *word, Token* tptr);
bool isParenses  (const char c);
bool isColon     (const char c);
bool isWhiteSpace(const char c);
bool isComma     (const char c);
bool isAlNum     (const char c);
bool isLink      (const char c);
bool isDoubleLink(const char c1, const char c2);

char*  convertTokenToString(Tokens token);

#endif
