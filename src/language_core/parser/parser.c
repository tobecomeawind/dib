#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "lexer.h"
#include "tokens.h"
#include "parser.h"
#include "node.h"


static void mainParsing (void);
static void parseKeyword(void);


static void borderWrapper(bordersType btype, bool (*func)(void));

static bool parseEntity  (void);

static Token* isNextToken(Tokens         majorType,
						  Tokens         minorType, 
                          isNextTokenArg args);

extern void invokeCliError(char*);
static void errorCall (Token* token, Tokens expectedType);

#define checkErrorCall(X, point) \
if(!(X)) {             \
	goto point;        \
}                      \




void startParsing(void)
{
	//--------------------------------
	//Extern function to start parsing
	//and init global variables
	//--------------------------------
	
	initTokensTempBuf();	

	mainParsing();
	
	freeTokensBuf();
	freeTokensTempBuf();
}


static void mainParsing(void)
{
	//------------------------
	//Main function of parsing
	//------------------------
	
	Token *tok;
	
	parseKeyword();
}


static void parseKeyword(void)
{
	//----------------------------------
	//Parse the first keyword in command  //command such a ENTITY (..., ...)
	//----------------------------------  //               LINK   (...<->...)
	


    //printf("\nMajor: %i Minor: %i Adress: %p\n", tokenMajorType, tokenMinorType, tok);

	// ENTITY (Person:Andrey:CHAR)
	
	Token* tok;
	Tokens tokenMajorType, tokenMinorType;

	if( !(tok = isNextToken(KEYWORDS, 0, NO_ARGS)) ){
		invokeCliError("Expected Keyword");	
		return;	
	}	
	
	tokenMajorType = tok->majorType;
	tokenMinorType = tok->minorType;	

	
	switch (tokenMinorType) {
		case (K_ENTITY):
			printf("\nEntity check\n");
			borderWrapper(PARENSES, &parseEntity);
			break;
		case (K_ENTITIES):
			printf("\nEntities check\n");
			printEntities();		
			break;	
		case (K_LINK):
			printf("\nLink check\n");
			break;	
	}	
}




static bool parseEntity(void)
{	
	//ENTITY	

	Token* tmpToken;	
	char*  Entity, *Data;
	Tokens DataType;
	
	// Person
	checkErrorCall(tmpToken = isNextToken(NAME, NAME, MINOR|ERROR), errorPoint);
	Entity = tmpToken->data;	
	//         (...., true,  ....)
	//         if we`ll check entity type	
	//checkEntityType())	
	
	// :	
	checkErrorCall(isNextToken(CLETTERS, COLON, MINOR|ERROR), errorPoint);
	
	// Vasya	
	checkErrorCall(tmpToken = isNextToken(NAME, NAME, MINOR|ERROR), errorPoint);
	Data = tmpToken->data;

	// :	
	checkErrorCall(isNextToken(CLETTERS, COLON, MINOR|ERROR), errorPoint);
	
	// CHAR
	checkErrorCall(tmpToken = isNextToken(DATATYPE, 0,  ERROR), errorPoint);
	DataType = tmpToken->minorType;	
	//check type and name
					  //
					  // ENTITY (Person:Vasya:CHAR)
					  //
	

	nodeConstructCli(Entity, Data, DataType);	
	
	// multiply add entity
	//
	// Example
	// ENTITY (Person:Vasya:CHAR, Person:Sonya:CHAR)
	//
	if( !isNextToken(CLETTERS, COMMA, TEMP|MINOR) ){
		return true;
	}

	getToken();    // skip "," token
	parseEntity(); 	

	errorPoint:		
		return false;
}


static void borderWrapper(bordersType btype, bool (*func)(void))
{	
	//-----------------------------------------------	
	// Wrap the function(statement) to check borders
	// Example:
	//
	// SomeKeyword (...:...:...)
	//          ||
	// SomeKeyword "("          | border decorator
	//              ...:...:... | func()
	//             ")"          | border decorator
	//------------------------------------------------
	
	Tokens openBorder, closeBorder;

	switch(btype){
		case(PARENSES):
			 openBorder =  OPEN_PARENS;
			closeBorder = CLOSE_PARENS;
			break;
	}
	
	isNextToken(BORDERS, openBorder,  MINOR|ERROR);        // (	
	if ( !func() ) return;	
	isNextToken(BORDERS, closeBorder, MINOR|ERROR);        // )
}




static Token* isNextToken(Tokens         majorType,
                          Tokens         minorType, 
                          isNextTokenArg args)
{
	//------------------------------------
	// If all conditions true
	//    Returns token
	// else
	//    Returns NULL
	//------------------------------------

	Token  *tokenVar = getToken();

	if ( !tokenVar ) return NULL;

	Tokens  tokenMajorType = tokenVar->majorType;
	Tokens  tokenMinorType = tokenVar->minorType;
	
	if ( args & TEMP )
		ungetToken(tokenVar);

	// if majors type not equal
	if ( tokenMajorType != majorType )
		goto errorCheckPoint;	
	
	// minors type not equal
	if( (args & MINOR) && !(tokenMinorType == minorType) ) 
		goto errorCheckPoint;	


	// if all good
	return tokenVar;


	errorCheckPoint:
		if ( args & ERROR )
			errorCall(tokenVar, (args & MINOR) ? (minorType) : (majorType));	
		// if error	
		return NULL;
}


static void errorCall (Token* token, Tokens expectedType)
{	
	char* expectedErrorWord, *errorString, *givenData;
	
   	givenData         = (token->data) ? (token->data) : "nothing";
	expectedErrorWord = convertTokenToString(expectedType);

	asprintf(&errorString,
            "|Expected: \"%s\"|---|Given: \"%s\"|",
             expectedErrorWord,   givenData);

	
	invokeCliError(errorString);

	free(errorString);
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


