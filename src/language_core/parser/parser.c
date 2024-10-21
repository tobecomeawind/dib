#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "lexer.h"
#include "tokens.h"
#include "parser.h"


static Token  *getToken(void);
static void  ungetToken(Token *token);

static void mainParsing (void);
static void parseKeyword(Token *tok);


static void borderDecorator(bordersType btype, void (*func)(void));
static void parseEntity    (void);


static bool isDataType (Token  *tptr, bool errorCheck);
static bool isNextToken(Tokens majorType,
						Tokens minorType, 
		                bool   addTokenInTempBuf,
                        bool   minorCheck,						
						bool   errorCheck);

//Token *tokensBuf;
//Token *tbptr;


Token  *tokensBuf;
Token  *tbptr    ;  // token buf pointer




void startParsing(Token *bptr)
{
	//--------------------------------
	//Extern function to start parsing
	//and init global variables
	//--------------------------------
	
	if(!bptr)
		return;

	//tokensBuf = bptr;	
	//tbptr = bptr;	
	
	mainParsing();

	tbptr     = NULL;
	tokensBuf = NULL;
	//free(tokensBuf);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Need fix tokensBuf
//Need fix tokensBuf
//Need fix datatypes keyword
//Need fix all memory
//perepisat` kostili
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


static void mainParsing(void)
{
	//------------------------
	//Main function of parsing
	//------------------------
	
	Token *tok;
	
	parseKeyword(getToken());
}


static void parseKeyword(Token *tok)
{
	//----------------------------------
	//Parse the first keyword in command  //command such a ENTITY (..., ...)
	//----------------------------------  //               LINK   (...<->...)

	Tokens tokenMajorType = tok->majorType;
	Tokens tokenMinorType = tok->minorType;	

	printf("\nMajor: %i Minor: %i Adress: %p\n", tokenMajorType, tokenMinorType, tok);

	if(tokenMajorType == NAME){
		printf("\nError: Invalid keyword with name \"%s\"", tok->data);	
		printf("\nExpected keyword\n");
		return;	
	}

	// ENTITY (Person:Andrey:CHAR)
	if(isNextToken(KEYWORDS, 0, true, false, false)){
		switch (tokenMinorType) {
			case (K_ENTITY):
				printf("\nEntity check\n");
				borderDecorator(PARENSES, &parseEntity);
				break;	
		}		
	}	
}




static void parseEntity(void)
{
	//skipWhiteSpace();	
		
	//ENTITY	
	//isNextToken(OPEN_PARENS,  false, true);    // (	
	isNextToken(NAME,     NAME,     false, true, true);        // Person
	//         (...., true,  ....)
	//         if we`ll check entity type	
	//checkEntityType())	
	isNextToken(CLETTERS, COLON,    false, true, true);        // :	
	isNextToken(NAME,     NAME,     false, true, true);        // Vasya
	isNextToken(CLETTERS, COLON,    false, true, true);        // :	
	isNextToken(DATATYPE, 0,        false, false, true);        // CHAR		
	//check type and name
	//isNextToken(CLOSE_PARENS, false, true);       // )
					  //
					  // ENTITY (Person:Vasya:CHAR)
					  //
	printf("\nExcellent!!!\n");	
	//
	// multiply add entity
	//
	// Example
	// ENTITY (Person:Vasya:CHAR, Person:Sonya:CHAR)
	//
	if(isNextToken(CLETTERS, COMMA, true, true, false)){
		getToken();    // skip "," token
		parseEntity(); // 	
	}
}


static void borderDecorator(bordersType btype, void (*func)(void))
{	
	//-----------------------------------------------	
	// Wrap the function(statement) to check borders
	// Example:
	//
	// SomeKeyword (...:...:...)
	//          ||
	// SomeKeyword "("   -      border decorator
	//              ...:...:... func()
	//             ")"   -      border decorator
	//------------------------------------------------
	
	Tokens openBorder, closeBorder;

	switch(btype){
		case(PARENSES):
			 openBorder =  OPEN_PARENS;
			closeBorder = CLOSE_PARENS;
			break;
	}

	isNextToken(BORDERS, openBorder,  false, true, true);        // (	
	func();
	isNextToken(BORDERS, closeBorder, false, true, true);        // )
}




static bool isNextToken(Tokens majorType,
						Tokens minorType, 
		                bool   addTokenInTempBuf,
                        bool   minorCheck,						
						bool   errorCheck)
{
	Token  *tokenVar       = getToken();
	Tokens  tokenMajorType = tokenVar->majorType;
	Tokens  tokenMinorType = tokenVar->minorType;

	// fucking kostili((((((((
	bool result = false;	

	if(tokenMajorType == majorType){
		result = true;

	    if(minorCheck && !(tokenMinorType == minorType)){
		
			result = false;	
			
			if(errorCheck){
				// if we need invoke a error	
				printf("\n Error: expected ");
				switch(minorType){
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
		}

	} else {
		printf("\nInvalid expression type\n");	
	}

	//printf("\nToken type: %3i Data: \"%s\"\n", tokenVar->type, tokenVar->data);

	if (addTokenInTempBuf)
		ungetToken(tokenVar);

	return result;
}


/*
static bool isDataType(Token *tptr, bool errorCheck)
{
	//Kostil function	
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
*/


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
		if ((tbptr - tokensBuf < MAX_TOKEN_BUF_SIZE) && tbptr){			
			return tbptr++;	
		}
		
		// tbptr oferflowed or tbptr == stop point(NULL)
		return NULL;
	}
}


static void ungetToken(Token *token)
{
	*ttbptr = *token;
	ttbptr++;
}


