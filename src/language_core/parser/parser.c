#include <stdio.h>


#include "lexer.h"
#include "tokens.h"
#include "parser.h"

static Token  *getToken(void);
static void  ungetToken(Token *token);

static void mainParsing (void);
static void parseKeyword(Token *tok);


Token *tokensBufPointer;
Token *tbptr;


void startParsing(Token *bptr)
{
	if(!bptr)
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


static void parseKeyword(Token *tok)
{
	if(tok->type == NAME){
		printf("\nError: Invalid keyword with name \"%s\"", tok->data);	
		printf("\nExpected keyword\n");
		return;	
	}

	/*
	switch tok->data:
		case "ENTITY":
	*/	

}






//if tokenTempBuf not null
//------------------------------------------
//Tokens get and unget
//Purpose - check the next token with get
//And unget him for putting in tokensTempBuf
//------------------------------------------
//else
//-----------------------------
//Get token from token buf
//
//buf != token temp buf
//buf = buf from startParsing()
//-----------------------------

Token  tokensTempBuf[TOKEN_TEMP_SIZE];
Token *ttbptr = tokensTempBuf; // token temp buf pointer


static Token *getToken(void)
{
	uint8_t mediateResult = ttbptr - tokensTempBuf;	

	if (mediateResult > 0){
		printf("\nReturn token value from temp\n");
		return --ttbptr;
	} else {	
		if (tbptr - tokensBufPointer < MAX_TOKEN_BUF_SIZE){
			printf("\nReturn token value from buf\n");
			return tbptr++;	
		}
		
		// tbptr oferflowed
		printf("\nReturn tokel value null\n");
		return NULL;
	}
	//return (mediateResult > 0) ? tokensTempBuf[--ttbptr]: getTokenFromBuf();
}


static void ungetToken(Token *token)
{
	ttbptr = token;
	ttbptr++;
}


