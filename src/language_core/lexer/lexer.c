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

	char   *tokenWord = malloc(sizeof(char) * MAX_WORD_SIZE);
	char   *twptr     = tokenWord;	// token word pointer
							
	Token  *tokensBuf = malloc(sizeof(Token) * MAX_TOKEN_BUF_SIZE);
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
						    tbptr,
							tempVar->type,
							(char*)tempVar->data);		
			} else {
				appendToken(tokensBuf,
						    tbptr,
							NAME,
							tokenWord);		
			}		
			
			twptr = tokenWord;
		} else { // last symbol jump fix
			
			twptr    = lptr;
			*++twptr = '\0'; 	

			if (isParenses(lptr)) {
	
				switch (*lptr){
					case ')':
						appendToken(tokensBuf, 
								    tbptr,
									CLOSE_PARENS,
									twptr);	
					case '(':
						appendToken(tokensBuf, 
								    tbptr,
									OPEN_PARENS,
									twptr);	
							
				};
	
			} else if(isColon(lptr)){

				appendToken(tokensBuf,
						    tbptr,
							COLON, 
							twptr);		
				
			} else if(isWhiteSpace(lptr)){

				appendToken(tokensBuf,
						    tbptr,
							WHITE_SPACE, 
							twptr);		
					
			} else {	
				printf("\n--- \"%c\" invalid---\n", *lptr);	
			}
		
			twptr = tokenWord;

			lptr++; // last symbol jump fix
		}		
	}
	
	return tokensBuf;	
}


static void appendToken(Token *buf, Token *bptr, Tokens type, char *data)
{
	if(bptr - buf > 0){
		printf("\nError: TokensBuf are is full!\n");	
		exit(-1);
	}	
	
	Token tokenVar = {.type = type,
		              .data = (const char*)data};
	*bptr++ = tokenVar;
}


