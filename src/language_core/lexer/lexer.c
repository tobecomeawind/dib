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


Token *analyze_line(char *lptr, int size)
{

	//------------------------------	
	// Analyzing to create tokens
	// Tokens in tokenBuf
	//------------------------------
		
	char   *tokenWord = (char*) malloc(sizeof(char) * MAX_WORD_SIZE);
	char   *twptr     = tokenWord;	// token word pointer
	


	Token  *tempVar;
	
	initTokensBuf();

	while(*lptr != '\0'){
		if (isAlNum(lptr)) {
		
			do{
				*twptr++ = *lptr;
			} while(isAlNum(++lptr));
			
			*twptr = '\0';
			

			if (tempVar = isKeyword(tokenWord)){
				appendToken(tempVar->majorType,
							tempVar->minorType,
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

	// tbptr = NULL; // stop point in tokens buf 
	
	tbptr = tokensBuf;

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


static void initTokensBuf(void)
{
	tokensBuf = (Token *) malloc(sizeof(Token) * MAX_TOKEN_BUF_SIZE);
	tbptr     = tokensBuf;  // token buf pointer
}

void freeTokensBuf(void)
{
	tbptr = NULL;
	free(tokensBuf);
}


