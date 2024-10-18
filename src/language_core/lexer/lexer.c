#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "tokens.h"


static void appendToken(Token *buf, Token *bptr, Tokens type, char *data);


Token *analyze_line(char *lptr, int size)
{

	//------------------------------	
	// Analyzing to create tokens
	// Tokens in tokenBuf
	//------------------------------

	char   *tokenWord = (char*) malloc(sizeof(char) * MAX_WORD_SIZE);
	char   *twptr     = tokenWord;	// token word pointer
							
	Token  *tokensBuf = (Token *) malloc(sizeof(Token) * MAX_TOKEN_BUF_SIZE);
	Token  *tbptr     = tokensBuf;  // token buf pointer
	Token  *tempVar;


	while(*lptr != '\0'){
		if (isalpha(*lptr)) {
			
			do{
				*twptr++ = *lptr;
			} while(isalpha(*++lptr));
			
			*twptr = '\0';
			

			if (tempVar = isKeyword(tokenWord)){
	
				appendToken(tokensBuf,
						    tbptr++,
							tempVar->type,
							tempVar->data);		
			} else {
				appendToken(tokensBuf,
						    tbptr++,
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
						appendToken(tokensBuf, 
								    tbptr++,
									CLOSE_PARENS,
									tokenWord);	
						break;
					case '(':
						appendToken(tokensBuf, 
								    tbptr++,
									OPEN_PARENS,
									tokenWord);	
						break;
							
				};
	
			} else if(isColon(lptr)){

				appendToken(tokensBuf,
						    tbptr++,
							COLON, 
							tokenWord);		
				
		/*	} else if(isWhiteSpace(lptr)){

				appendToken(tokensBuf,
						    tbptr,
							WHITE_SPACE, 
							tokenWord);		
		*/			
			} else if(isComma(lptr)){

				appendToken(tokensBuf,
						    tbptr++,
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


static void appendToken(Token *buf, Token *bptr, Tokens type, char *data)
{
	if (bptr - buf > MAX_TOKEN_BUF_SIZE){
		printf("\nError: TokensBuf are is full!\n");	
		exit(-1);
	}	

	Token *tokenVar = (Token*) malloc(sizeof(Token));	
	int    dataSize = (int)    strlen(data);
	char  *dataVar  = (char*)  malloc(sizeof(char) * dataSize);

	memcpy(dataVar, data, dataSize);

	tokenVar->type = type;
	tokenVar->data = dataVar;

	/*
	Token tokenVar = {.type = type,
	                  .data = data};
	*/

	*bptr = *tokenVar;


//	printf("\n Address: %p  \n", bptr);
}



