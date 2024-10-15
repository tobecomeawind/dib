#include "lexer.h"
#include "tokens.h"


#define TOKEN_TEMP_SIZE 10


static Token  *getToken(void);
static void  ungetToken(Token *token);
static void  mainParsing(void);



Token *tokensBufPointer;
Token *tbptr;




void startParsing(Token *bptr)
{
	if(!*bptr)
		return;

	tokensBufPointer = bptr;	
	tbptr = tokensBufPointer;	
	
	mainParsing();
}


static void mainParsing(void)
{
	//
	//Main function of parsing
	//
	Token *tok;
	
	parseKeyword(getToken());

}


void parseKeyword(Token *tok)
{
	if(tok->type != KEYWORD){
		printf("Error: Invalid keyword with name \"%s\"", tok->data);	
	}
	
	switch tok->data:
		case "ENTITY":
		

}








static Token *getTokenFromBuf(void)
{
	//-----------------------------
	//Get token from token buf
	//
	//buf != token temp buf
	//buf = buf from startParsing()
	//-----------------------------
	
	if(tbptr - tokensBufPointer < MAX){
		return tbptr++;	
	}

	return NULL;
}


//------------------------------------------
//Tokens get and unget
//Purpose - check the next token with get
//And unget him for putting in tokensTempBuf
//------------------------------------------

Token  tokensTempBuf[TOKEN_TEMP_SIZE];
Token *ttbptr = tokensTempBuf; // token temp buf pointer


static Token *getToken(void)
{
	uint8_t mediateResult = ttbptr - tokensTenpBuf;	

	return (mediateResult > 0) ? tokensTempBuf[--ttbptr]: getTokenFromBuf();
}


static void ungetToken(Token *token)
{
	*ttbtr++ = token;
}


