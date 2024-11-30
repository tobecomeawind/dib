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


static void borderWrapper(bordersType btype, void (*func)(void));
static void parseEntity  (void);


static Token* isNextToken(Tokens majorType,
						  Tokens minorType, 
		                  bool   addTokenInTempBuf,
                          bool   minorCheck,						
						  bool   errorCheck);


// Extern buffer declaration
Token *tokensBuf;
Token *tbptr    ;   // token buf pointer

// Intern temp buffer declaration
Token *tokensTempBuf;
Token *ttbptr;      // token temp buf pointer



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

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Need fix all memory
//perepisat` kostili
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


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
		printf("\nExpected keyword\n");
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
			break;	
		case (K_LINK):
			printf("\nLink check\n");
			break;	
	}	
}




static void parseEntity(void)
{	
	//ENTITY	
	
	char*  EntityType, *Name;
	Tokens DataType;
	Node*  testNode;

	printf("\nStart Parsing Entity Entry\n");
	
	// Person
	EntityType = isNextToken(NAME, NAME, false, true , true)->data;
	
	//         (...., true,  ....)
	//         if we`ll check entity type	
	//checkEntityType())	
	
	// :	
	isNextToken(CLETTERS, COLON, false, true,  true);                  
	
	// Vasya	
	Name       = isNextToken(NAME, NAME, false, true , true)->data;

	// :	
	isNextToken(CLETTERS, COLON, false, true,  true);	
	
	// CHAR
	DataType   = isNextToken(DATATYPE, 0,  false, false, true)->minorType;  
	
	//check type and name
					  //
					  // ENTITY (Person:Vasya:CHAR)
					  //

	printf("\nStop Parsing Entity Entry\n");

	
	testNode  = node_construct(EntityType,
			                   Name,
					           DataType);	
		
	// multiply add entity
	//
	// Example
	// ENTITY (Person:Vasya:CHAR, Person:Sonya:CHAR)
	//
	if(isNextToken(CLETTERS, COMMA, true, true, false)){
		getToken();    // skip "," token
		parseEntity(); 	
	}
}


static void borderWrapper(bordersType btype, void (*func)(void))
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
	
	printf("\nChecking borders\n");
	isNextToken(BORDERS, openBorder,  false, true, true);        // (	
	func();
	isNextToken(BORDERS, closeBorder, false, true, true);        // )
	printf("\nExcellent\n");
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
	Tokens  tokenMajorType = tokenVar->majorType;
	Tokens  tokenMinorType = tokenVar->minorType;
	
	if (addTokenInTempBuf)
		ungetToken(tokenVar);

	if(tokenMajorType == majorType){

	    if(minorCheck && !(tokenMinorType == minorType)){
			
			tokenVar = NULL;	

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
		if(errorCheck)
			printf("\nInvalid expression type\n");	
		
		tokenVar = NULL;	
	}

	/*
	printf("\n--Token Info--\nData: \"%s\" \nMinor: %3d \nMajor: %3d\n",
			 tokenVar->data,
			          tokenMinorType,
			                     tokenMajorType);

	printf("\n--Check Info--\nMinor: %3d \nMajor: %3d\n", minorType, majorType);
	*/	


	return tokenVar;
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

