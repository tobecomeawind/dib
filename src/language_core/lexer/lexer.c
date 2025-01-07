#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "tokens.h"


static void appendToken(Tokens majType, // majorType
						Tokens minType, // minorType
						char *data);    // word
										
static void initTokensBuf(void);

extern void invokeCliError(char*);


Token* analyze_line(char *lptr, int size)
{

	//------------------------------	
	// Analyzing to create tokens
	// Tokens in tokenBuf
	//------------------------------
		
	char* tokenWord = (char*) malloc(MAX_WORD_SIZE);
	char* twptr     = tokenWord;	// token word pointer
	
	Token* tmpToken = malloc(sizeof(Token));
	
	initTokensBuf();

	while( *lptr != '\0' ) {
		if ( isAlNum(lptr) ) {
		
			do{
				*twptr++ = *lptr;
			} while( isAlNum(++lptr) );
			
			*twptr = '\0';
			

			if ( isKeyword(tokenWord, tmpToken) ) {
				appendToken(tmpToken->majorType,
							tmpToken->minorType,
							tmpToken->data);		
			} else {

				// exit 
				if ( strcmp(tokenWord, "q") == 0 ) {
					freeTokensBuf();	
					goto end;
				}
				   

				appendToken(NAME,
							NAME,
							tokenWord);		
			}		

			//free(tmpToken);	
			twptr = tokenWord;
		} else { // last symbol jump fix
			
			*twptr    = *lptr;
			*++twptr  = '\0'; 	

			if (isParenses(lptr)) {
	
				switch (*lptr){
					case ')':
						appendToken(BORDERS,
									CLOSE_PARENS,
									tokenWord);	
						break;
					case '(':
						appendToken(BORDERS,    
									OPEN_PARENS,
									tokenWord);	
						break;
							
				};
	
			} else if(isColon(lptr)){

				appendToken(CLETTERS,
							COLON, 
							tokenWord);		
					
			} else if(isComma(lptr)){

				appendToken(CLETTERS,
							COMMA,
						    tokenWord);	
			
			} else {
				if(!isWhiteSpace(lptr))	
					printf("\n\"Undefined char - %c\"\n", *lptr);		
			}
		
			twptr = tokenWord;

			lptr++; // last symbol jump fix
		}	
	}
	
	tbptr = tokensBuf;

	end:
		free(tokenWord);
		free(tmpToken);	

		return tbptr;	
}


static void appendToken(Tokens majType, // majorType
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


static void initTokensBuf(void)
{
	tokensBuf = (Token*) malloc(sizeof(Token) * MAX_TOKEN_BUF_SIZE);
	tbptr     = tokensBuf;  // token buf pointer
}

void freeTokensBuf(void)
{	
	for (uint8_t i = (tbptr - tokensBuf); i > 0; --i)
		free((tbptr)->data);
			
	tbptr = NULL;
	free(tokensBuf);
}


