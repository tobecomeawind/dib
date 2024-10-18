#include <stdio.h>
#include <stdbool.h>

#include "lexer.h"
#include "tokens.h"
#include "parser.h"

static Token  *getToken(void);
static void  ungetToken(Token *token);

static void mainParsing (void);
static void parseKeyword(Token *tok);

static void parseEntity(void);

static bool isNextToken(Tokens tokenType, bool addTokenInTempBuf, bool error);
static void skipWhiteSpace();



Token *tokensBufPointer;
Token *tbptr;




void startParsing(Token *bptr)
{
	//--------------------------------
	//Extern function to start parsing
	//and init global variables
	//--------------------------------
	
	if(!bptr)
		return;

	tokensBufPointer = bptr;	
	tbptr = tokensBufPointer;	
	
	mainParsing();
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Need fix tokensBuf
//Need fix tokensBuf
//Need fix datatypes keyword
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


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

	//ENTITY (Person:Andrey:CHAR)

	switch (tok->type) {
		case(K_ENTITY):
			printf("\nEntity check\n");
			parseEntity();
	}	
}




static void parseEntity(void)
{
	//skipWhiteSpace();	
		
	//ENTITY	
	isNextToken(OPEN_PARENS,  false, true);        // (	
	isNextToken(NAME,         false, true);        // Person
	//         (...., true,  ....)
	//         if we`ll check entity type	
	//checkEntityType())	
	isNextToken(COLON,        false, true);        // :	
	isNextToken(NAME,         false, true);        // Vasya
	isNextToken(COLON,        false, true);        // :	
	isNextToken(DATATYPE,     false, true);        // CHAR	
	//check type and name
	isNextToken(CLOSE_PARENS, false, true);       // )
					  //
					  // ENTITY (Person:Vasya:CHAR)
					  //
	printf("\nExcellent!!!\n");	
}


static bool isDataType(Token *tptr, bool errorCheck)
{
	Tokens tokenType = tptr->type;
	bool   result    = false;

	switch (tokenType){
		case(K_CHAR):
		case(K_INT):
		case(K_FLOAT):
			result = true;	
			break;
		default:
			if(errorCheck){
				printf("\nError: invalid datatype \"%s\" \n", tptr->data);
				//exit
			}
			break;
	}
	
	return result;	
}



static bool isNextToken(Tokens tokenType,
		                bool   addTokenInTempBuf,
						bool   errorCheck)
{
	Token *tokenVar     = getToken();
	Tokens  tokenVarType = tokenVar->type;


	bool result = true;
	

	if (!(tokenVarType == tokenType)){	
		if (errorCheck && !(isDataType(tokenVar, errorCheck))){
			// if we need invoke a error	
			printf("\n Error: expected ");
			switch(tokenType){
				case(OPEN_PARENS):
					printf("\"(\"");
					break;	
				case(CLOSE_PARENS):
					printf("\")\"");
					break;	
				case(NAME):
					printf("\"Name\"");
					break;
				case(COLON):
					printf("\":\"");	
					break;
			}
			printf(" \n");

		}

		result = false;
	}

	printf("\nToken type: %i Data: %s\n", tokenVar->type, tokenVar->data);

	if (addTokenInTempBuf)
		ungetToken(tokenVar);

	return result;
}



static void skipWhiteSpace()
{
	//invalid work

	while(getToken()->type == WHITE_SPACE);
	//ungetToken();
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
		return --ttbptr;
	} else {	
		if (tbptr - tokensBufPointer < MAX_TOKEN_BUF_SIZE){
			return tbptr++;	
		}
		
		// tbptr oferflowed
		return NULL;
	}
	//return (mediateResult > 0) ? tokensTempBuf[--ttbptr]: getTokenFromBuf();
}


static void ungetToken(Token *token)
{
	ttbptr = token;
	ttbptr++;
}


