#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tokens.h"
#include "algs.h"

#define MAX_TOKEN_BUF_SIZE 128


static Token* tokensBuf;
static Token* tokensTempBuf;

static Token* tbptr;
static Token* ttbptr; 

static void freeTokensBuf_iml(Token* buf, Token* bufptr);



#define INIT_BUF_IML(buf, bufptr)                              \
do {                                                           \
	buf = (Token*) malloc(sizeof(Token) * MAX_TOKEN_BUF_SIZE); \ 
	bufptr = buf;                                              \
} while(0);                                                    

void initTokensBuf     (void) { INIT_BUF_IML(tokensBuf,     tbptr);  }
void initTokensTempBuf (void) { INIT_BUF_IML(tokensTempBuf, ttbptr); }


void freeTokensBuf    (void) { freeTokensBuf_iml(tokensBuf,     tbptr); }
void freeTokensTempBuf(void) { freeTokensBuf_iml(tokensTempBuf, ttbptr);}


static void freeTokensBuf_iml(Token* buf, Token* bufptr)
{	
	//---------------
	// buf destructor
	//---------------
	
	for (uint8_t i = (bufptr - buf); i > 0; --i)
		free((--bufptr)->data);
		
	bufptr = NULL;
	free(buf);
}


static Token* tokenConstruct (Tokens major, Tokens minor, char* data)
{
	//------------------
	// Token constructor
	//------------------
	
	Token* tptr = malloc(sizeof(Token));	
	
	if ( !tptr ) return NULL;

	tptr->majorType = major;	
	tptr->minorType = minor;	
	tptr->data      = data;

	return tptr;	
}

static void tokenDestruct (Token* tptr)
{
	//---------------
	// Destruct token
	//---------------
	
	if ( !tptr )      return;
	if ( tptr->data ) free(tptr->data);	
	
	free(tptr);	
}


Token* getToken(void)
{
	//---------------------------------
	// Get token from tokensTempBuf
	//---------------------------------

	uint8_t mediateResult = ttbptr - tokensTempBuf;	
	
	// if tokensTempBuf not empty
	// return value from tokens temp bur pointer
	if ( mediateResult > 0 ) return --ttbptr;
	
	// if (tbprt != NULL) && (tbptr != last token in tokensBuf)
	// return current token and shift right by one pos in tokensBuf
	if ( tbptr && (tbptr - tokensBuf < MAX_TOKEN_BUF_SIZE)) return tbptr++;	
	
		
	// tbptr oferflowed or tbptr == stop point(NULL)
	return NULL;	
}

void ungetToken(Token *token)
{
	//---------------------------------
	// Push back token in tokensTempBuf
	//---------------------------------
	*ttbptr = *token;
	ttbptr++;
}


void appendToken(Tokens majType, // majorType
                 Tokens minType, // minorType
                 char*  data)    // word
{
	//-------------------------
	//Append token in tokensBuf
	//-------------------------

	if (tbptr - tokensBuf > MAX_TOKEN_BUF_SIZE){
		printf("\nError: TokensBuf are is full!\n");	
	}	
	
	
	tbptr->majorType = majType;
	tbptr->minorType = minType;
	
	// Copy data in new variable
	// cause input data will free later in analyze line 
	char* newData = malloc(strlen(data) + 1);
	strcpy(newData, data);

	(tbptr++)->data = newData;
}

void shiftTokensBufPointer (void) 
{
	tbptr = tokensBuf;	
}



char* convertTokenToString(Tokens token)
{	
	char* stringToken;

	switch(token){
		case(OPEN_PARENS):
			stringToken = "(";
			break;	
		case(CLOSE_PARENS):
			stringToken = ")";
			break;	
		case(NAME):
			stringToken = "Name";
			break;
		case(COLON):
			stringToken = ":";
			break;
		case(K_ENTITY):
			stringToken = "Entity";
			break;
		case(K_CHAR):
			stringToken = "CHAR";
			break;
		case(K_FLOAT):
			stringToken = "FLOAT";
			break;
		case(K_INT):
			stringToken = "INT";
			break;
		case(DATATYPE):
			stringToken = "Data Type";
			break;
		case(KEYWORDS):
			stringToken = "Keyword";
			break;
	}

	return stringToken;
}




// Token Checks 
bool isKeyword(char *word, Token* tptr)
{
	//--------------------------
	//Check the word is keyword
	//else 
	//word == name of something
	//--------------------------

	int8_t  index, size;
	Token  keyword; // token pointer

	Token keywords[] = { // Keyword tokens
		{.majorType = DATATYPE, .minorType = K_CHAR,     .data = "CHAR"    },
		{.majorType = KEYWORDS, .minorType = K_ENTITIES, .data = "ENTITIES"},
		{.majorType = KEYWORDS, .minorType = K_ENTITY,   .data = "ENTITY"  },
		{.majorType = DATATYPE, .minorType = K_FLOAT,    .data = "FLOAT"   },
		{.majorType = DATATYPE, .minorType = K_INT,      .data = "INT"     },
		{.majorType = KEYWORDS, .minorType = K_LINK,     .data = "LINK"    },
	};
	
	size = sizeof(keywords) / sizeof(Token); 
	
	// return keyword token if word in keywords else 0
	index = binsearch((void**)keywords, size, (void*)word, bsTOKEN);	
	
	if( index < 0 ) {
		tptr = NULL;
		return false;
	} else 
		index -= 1;

	keyword = keywords[index];
	memcpy(tptr, &keyword, sizeof(keyword));
	
	return true;
}


bool isParenses(char *c)
{
	return *c == '(' || *c == ')';
}

bool isColon(char *c)
{
	return *c == ':';
}

bool isComma(char *c)
{
	return *c == ',';
}

bool isWhiteSpace(char *c)
{
	return *c == ' ' || *c == '\t';
}

bool isAlNum(char *c)
{
	return isalnum(*c) || *c == '.';
}
