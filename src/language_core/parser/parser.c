#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "lexer.h"
#include "tokens.h"
#include "parser.h"
#include "node.h"

static Token  *getToken(void);
static void  ungetToken(Token *token);
static void initTokensTempBuf(void);
static void freeTokensTempBuf(void);

static void mainParsing (void);
static void parseKeyword(void);


static void borderWrapper(bordersType btype, bool (*func)(void));

static bool parseEntity  (void);


static Token* isNextToken(Tokens majorType,
						  Tokens minorType, 
		                  bool   addTokenInTempBuf,
                          bool   minorCheck,						
						  bool   errorCheck);

extern void invokeCliError(char*);
static void errorCall (Token* token, Tokens expectedType);

// Extern buffer declaration
Token *tokensBuf;
Token *tbptr    ;   // token buf pointer

// Intern temp buffer declaration
Token *tokensTempBuf;
Token *ttbptr;      // token temp buf pointer




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
	
	if(!tbptr)
		return;

	//tokensBuf = bptr;	
	//tbptr = bptr;	
	
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
	if(!isNextToken(KEYWORDS, 0, true, false, false)){
		invokeCliError("Expected Keyword");	
		return;	
	}	
	
	Token* tok            = getToken(); 
	Tokens tokenMajorType = tok->majorType;
	Tokens tokenMinorType = tok->minorType;	

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
	Node*  testNode;
	
	// Person
	checkErrorCall(tmpToken = isNextToken(NAME, NAME, false, true , true),
			                                                        errorPoint);
	Entity = tmpToken->data;	
	//         (...., true,  ....)
	//         if we`ll check entity type	
	//checkEntityType())	
	
	// :	
	checkErrorCall(isNextToken(CLETTERS, COLON, false, true, true), errorPoint);
	
	// Vasya	
	checkErrorCall(tmpToken = isNextToken(NAME, NAME, false, true , true),
                                                                    errorPoint);
	Data = tmpToken->data;

	// :	
	checkErrorCall(isNextToken(CLETTERS, COLON, false, true, true), errorPoint);
	
	// CHAR
	checkErrorCall(tmpToken = isNextToken(DATATYPE, 0,  false, false, true),
                                                                    errorPoint);
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
	if( !isNextToken(CLETTERS, COMMA, true, true, false) ){
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
	
	isNextToken(BORDERS, openBorder,  false, true, true);        // (	
	if ( !func() ) return;
	
	isNextToken(BORDERS, closeBorder, false, true, true);        // )
}




static Token* isNextToken(Tokens majorType,
						Tokens minorType, 
		                bool   addTokenInTempBuf,
                        bool   minorCheck,						
						bool   errorCheck)
{
	//------------------------------------
	// If all conditions true
	//    Returns token
	// else
	//    Returns NULL
	//------------------------------------

	Token  *tokenVar       = getToken();

	if (!tokenVar) return NULL;

	Tokens  tokenMajorType = tokenVar->majorType;
	Tokens  tokenMinorType = tokenVar->minorType;
	
	if (addTokenInTempBuf)
		ungetToken(tokenVar);

	if(tokenMajorType == majorType){

	    if(minorCheck && !(tokenMinorType == minorType)){
			
			if(errorCheck)
				errorCall(tokenVar, minorType);
				
			tokenVar = NULL;	
		}

	} else {
		if(errorCheck)
			errorCall(tokenVar, (minorCheck) ? (minorType) : (majorType));	
		
		tokenVar = NULL;	
	}

	return tokenVar;
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


static Token* getToken(void)
{
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


static void ungetToken(Token *token)
{
	*ttbptr = *token;
	ttbptr++;
}

static void initTokensTempBuf(void)
{
    tokensTempBuf = (Token*) malloc(sizeof(Token) * TOKEN_TEMP_SIZE);
	ttbptr        = tokensTempBuf; // token temp buf pointer											  
}

static void freeTokensTempBuf(void)
{
	free(tokensTempBuf);
	ttbptr = NULL;	
}

