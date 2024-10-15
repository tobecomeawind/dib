#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "tokens.h"


static void appendToken(Token *buf, Token *bptr, Tokens type, char *data);


int main(void)
{
	void hello_message(void);
	Token *analyze_line(char* line, int size);

	char lineBuf[MAX_LINE_SIZE];
	char lineBufIndex = 0;	

	char    c;

	hello_message();

	while(1){
		printf("dib-cli >>> ");

		while((c = getchar()) != '\n'){
			lineBuf[lineBufIndex++] = c;				
		}
			
		lineBuf[lineBufIndex] = '\0';	
		analyze_line(lineBuf, lineBufIndex);
		
		lineBufIndex = 0;
	}	


	return 0;
}


void hello_message(void)
{
	//----------------------------
	//The first output of programm
	//General information
	//----------------------------

	printf("\n Hello in DIB, version is 0.0.0.1 \n");
	printf(" ---Copyright: tobecomeawind--- \n\n");
	
}


Token *analyze_line(char *lptr, int size)
{

	//------------------------------	
	// Analyzing to create tokens
	// Tokens in tokenBuf
	//------------------------------

	char    tokenWord[MAX_WORD_SIZE];
	char   *twptr = tokenWord;	// token word pointer
								
	//Token   tokensBuf[MAX_TOKEN_BUF_SIZE]; = malloc(sizeof(Token) * MAX_TOKEN_BUF_SIZE)
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
			if (isParenses(lptr)) {
	
				switch (*lptr){
					case ')':
						appendToken(tokensBuf, 
								    tbptr,
									CLOSE_PARENS,
									lptr);	
					case '(':
						appendToken(tokensBuf, 
								    tbptr,
									OPEN_PARENS,
									lptr);	
							
				};
	
			} else if(isColon(lptr)){

				appendToken(tokensBuf,
						    tbptr,
							COLON, 
							lptr);		
				
			} else if(isWhiteSpace(lptr)){

				appendToken(tokensBuf,
						    tbptr,
							WHITE_SPACE, 
							lptr);		
					
			} else {	
				printf("\n--- \"%c\" invalid---\n", *lptr);	
			}

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


