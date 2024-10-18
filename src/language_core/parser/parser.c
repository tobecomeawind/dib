#include <stdio.h>
#include <stdbool.h>

#include "lexer.h"
#include "tokens.h"
#include "parser.h"

static Token  *getToken(void);
static void  ungetToken(Token *token);

static void mainParsing (void);
static void parseKeyword(Token *tok);



static void borderDecorator(bordersType btype, void (*func)(void));
static void parseEntity(void);


static bool isDataType(Token  *tptr, bool errorCheck);
static bool isNextToken(Tokens tokenType,
		                bool   addTokenInTempBuf,
						bool   errorCheck);
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
//Need fix all memory
//perepisat` kostili
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
	//----------------------------------
	//Parse the first keyword in command  //command such a ENTITY (..., ...)
	//----------------------------------  //               LINK   (...<->...)

	Tokens tokenType = tok->type;
	

	if(tokenType == NAME){
		printf("\nError: Invalid keyword with name \"%s\"", tok->data);	
		printf("\nExpected keyword\n");
		return;	
	}

	//ENTITY (Person:Andrey:CHAR)

	switch (tokenType) {
		case(K_ENTITY):
			printf("\nEntity check\n");
			borderDecorator(PARENSES, &parseEntity);	
			//parseEntity();
	}	
}




static void parseEntity(void)
{
	//skipWhiteSpace();	
		
	//ENTITY	
	//isNextToken(OPEN_PARENS,  false, true);        // (	
	isNextToken(NAME,       false, true);        // Person
	//         (...., true,  ....)
	//         if we`ll check entity type	
	//checkEntityType())	
	isNextToken(COLON,      false, true);        // :	
	isNextToken(NAME,       false, true);        // Vasya
	isNextToken(COLON,      false, true);        // :	
	isNextToken(DATATYPE,   false, true);        // CHAR		
	//check type and name
	//isNextToken(CLOSE_PARENS, false, true);       // )
					  //
					  // ENTITY (Person:Vasya:CHAR)
					  //
	printf("\nExcellent!!!\n");	


	// multiply add entity
	//
	// Example
	// ENTITY (Person:Vasya:CHAR, Person:Sonya:CHAR)
	if(isNextToken(COMMA, true, false)){
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

	isNextToken(openBorder,  false, true);        // (	
	func();
	isNextToken(closeBorder, false, true);        // )
}




static bool isNextToken(Tokens tokenType,
		                bool   addTokenInTempBuf,
						bool   errorCheck)
{
	Token  *tokenVar     = getToken();
	Tokens  tokenVarType = tokenVar->type;

	// fucking kostili((((((((
	bool result;
	

	if (!(result = (tokenVarType == tokenType))){
	

		// datatype check
		// kostil epta
		if (tokenType == DATATYPE){
			if (isDataType(tokenVar, errorCheck))		
				result = true;
		    
			// absract break
			// we shouldnt go down if condition is true
			errorCheck = false;
		}
		
		if (errorCheck){
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

	}

	printf("\nToken type: %3i Data: \"%s\"\n", tokenVar->type, tokenVar->data);

	if (addTokenInTempBuf)
		ungetToken(tokenVar);

	return result;
}

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
		if ((tbptr - tokensBufPointer < MAX_TOKEN_BUF_SIZE) && tbptr){			
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


