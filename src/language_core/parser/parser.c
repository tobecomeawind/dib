#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "lexer.h"
#include "tokens.h"
#include "parser.h"
#include "node.h"
#include "graph.h"

static void mainParsing (void);
static void parseKeyword(void);


static void borderWrapper(bordersType btype, bool (*func)(void));

static Node* parseEntity_iml(parseEntityArg args);
static bool parseEntity (void);
static bool parseLink   (void);

static Token* isNextToken(Tokens         majorType,
						  Tokens         minorType, 
                          isNextTokenArg args);

extern void invokeCliError(char*);
static void errorCall (Token* token, Tokens expectedType);

#define ASSERT_JUMP(X, point) \
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
			borderWrapper(PARENSES, &parseLink);
			break;	
	}	
}




static bool parseEntity(void)
{	
	
	if ( !parseEntity_iml( E_ENTITY | E_DATA | E_DATATYPE ) )
		return false;	
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
}

static bool parseLink (void)
{
	// LINK	(Man:Vasya <> Women:Masha, LOVED_IN)
	Node *source, *target;
	char* relName;	
	bool doubleLink = false;

	Token* tmpToken;
	
	// Man:Vasya
	ASSERT_JUMP(source = parseEntity_iml( E_ENTITY | E_DATA ),  errorPoint);  
	// >
	if ( !(tmpToken = isNextToken(CLETTERS, LINK, MINOR|ERROR)) ) {
		// if next token != LINK
	    // we check dlink 
		ungetToken(tmpToken);		
		// <>	
		ASSERT_JUMP(isNextToken(CLETTERS, DLINK, MINOR|ERROR),  errorPoint);
		doubleLink = true;
	}
	// Women:Masha	
	ASSERT_JUMP(target = parseEntity_iml( E_ENTITY | E_DATA ),  errorPoint); 
   	// ,	
	ASSERT_JUMP(isNextToken(CLETTERS, COMMA, TEMP|MINOR),       errorPoint);	
	// LOVED_IN	
	ASSERT_JUMP(tmpToken = isNextToken(NAME, NAME, MINOR|ERROR),errorPoint);
	relName = tmpToken->data;


	if ( !linkNodes(source, target, relName) )
		goto errorPoint;
	
	if ( !(doubleLink && linkNodes(target, source, relName)) ) 
		goto errorPoint;


	return true;	

	errorPoint:
		return false;
}


static Node* parseEntity_iml(parseEntityArg args)
{
	//ENTITY (Person:Vasya:CHAR)	

	Token* tmpToken = NULL;	
	char*  Entity   = NULL;
	char*  Data     = NULL;
	Tokens DataType = 0;

	Node*  tmpNode; 

	if ( args & E_ENTITY ) {
		// Person
		ASSERT_JUMP(tmpToken = isNextToken(NAME, NAME, MINOR|ERROR),errorPoint);
		Entity = tmpToken->data;
	} else 
		goto errorPoint;	
	
	if ( args & E_DATA ) {
		// :	
		ASSERT_JUMP(isNextToken(CLETTERS, COLON, MINOR|ERROR), errorPoint);			
		// Vasya	
		ASSERT_JUMP(tmpToken = isNextToken(NAME, NAME, MINOR|ERROR),errorPoint);
		Data = tmpToken->data;
	}
	
	if (args & E_DATATYPE) {
		// :	
		ASSERT_JUMP(isNextToken(CLETTERS, COLON, MINOR|ERROR), errorPoint);
		
		// CHAR
		ASSERT_JUMP(tmpToken = isNextToken(DATATYPE, 0,  ERROR), errorPoint);
		DataType = tmpToken->minorType;		
	}	

	if ( !DataType && Data )
		DataType = getTypeOfData(Data);

	tmpNode = nodeConstructTmp(Entity, Data, DataType);
	return tmpNode;


	errorPoint:
		return NULL;
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
