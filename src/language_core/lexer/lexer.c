#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "tokens.h"


static void appendToken(Token *buf, Token *bptr, Tokens type, char *data);


static Token  *tokensBuf = (Token *) malloc(sizeof(Token) * MAX_TOKEN_BUF_SIZE);
static Token  *tbptr     = tokensBuf;  // token buf pointer


Token *analyze_line(char *lptr, int size)
{

	//------------------------------	
	// Analyzing to create tokens
	// Tokens in tokenBuf
	//------------------------------

	char   *tokenWord = (char*) malloc(sizeof(char) * MAX_WORD_SIZE);
	char   *twptr     = tokenWord;	// token word pointer
							
	Token  *tempVar;

	while(*lptr != '\0'){
		if (isalpha(*lptr)) {
			
			do{
				*twptr++ = *lptr;
			} while(isalpha(*++lptr));
			
			*twptr = '\0';
			

			if (tempVar = isKeyword(tokenWord)){
	
				appendToken(KEYWORD,
							tempVar->type,
							tempVar->data);		
			} else {
				appendToken(NAME,
							NAME,
							tokenWord);		
			}		
			free(tempVar);	
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
					printf("\n--- \"%c\" invalid---\n", *lptr);	
			}
		
			twptr = tokenWord;

			lptr++; // last symbol jump fix
		}	
	}

	
	free(tokenWord);

	tbptr = NULL; // stop point in tokens buf 

	return tokensBuf;	
}


static void appendToken(Tokens majType, // majorType
						Tokens minType, // minorType
						char *data)     // word
{
	//-------------------------
	//Append token in tokensBuf
	//-------------------------

	if (tbptr - tokensBuf > MAX_TOKEN_BUF_SIZE){
		printf("\nError: TokensBuf are is full!\n");	
		exit(-1);
	}	

	Token *tokenVar = (Token*) malloc(sizeof(Token));	
	int    dataSize = (int)    strlen(data);
	char  *dataVar  = (char*)  malloc(sizeof(char) * dataSize);

	memcpy(dataVar, data, dataSize);

	tokenVar->majorType = majType;
	tokenVar->minorType = minType;
	tokenVar->data = dataVar;

	*tbptr++ = *tokenVar;
}



