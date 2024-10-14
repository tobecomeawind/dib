#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "tokens.h"


static void appendToken(Token *buf, Token *bptr, Tokens type, char *data);

#define MAX_LINE_SIZE  100
#define MAX_WORD_SIZE  32

int main(void)
{
	void hello_message(void);
	void analyze_line(char* line, int size);

	char lineBuf[MAX_LINE_SIZE];
	char lineBufIndex = 0;	

	char    c;

	hello_message();

	while(c != EOF){
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


void analyze_line(char *lptr, int size)
{
	//------------------------------	
	// Analyzing to create tokens
	// Tokens in tokenBuf
	//------------------------------



	char    tokenWord[MAX_WORD_SIZE];
	char   *twptr = tokenWord;	// token word pointer
								
	Token   tokensBuf[1000];
	Token  *tbptr = tokensBuf;  // token buf pointer

	//uint8_t search_token(char *word);

	while(*lptr != '\0'){
		if (isalpha(*lptr)) {
			
			do{
				*twptr++ = *lptr;
			} while(isalpha(*++lptr));
			
			*twptr = '\0';

			if (isKeyword(tokenWord)){
				printf("\nKeyword: %s\n", tokenWord);
				appendToken(&tokensBuf[0],
						    tbptr,
							KEYWORD,
							tokenWord);	
			} else {
				printf("\nName   : %s\n", tokenWord);
				appendToken(&tokensBuf[0],
						    tbptr,
							NAME,
							tokenWord);		
			}		
			
			twptr = tokenWord;
		} else { // last symbol jump fix
			if (isParenses(lptr)) {

				printf("\nParens\n");
				
				switch (*lptr){
					case ')':
						appendToken(&tokensBuf[0], 
								    tbptr,
									CLOSE_PARENS,
									lptr);	
					case '(':
						appendToken(&tokensBuf[0], 
								    tbptr,
									OPEN_PARENS,
									lptr);	
							
				};
	
			} else if(isColon(lptr)){

				printf("\nColon\n");	
				appendToken(&tokensBuf[0],
						    tbptr,
							COLON, 
							lptr);		
				
			} else if(isWhiteSpace(lptr)){

				printf("\nWhiteSpace\n");
				appendToken(&tokensBuf[0],
						    tbptr,
							WHITE_SPACE, 
							lptr);		
					
			} else {	
				printf("\n--- \"%c\" nothing---\n", *lptr);	
			}

			lptr++; // last symbol jump fix
		}		
	}

	tbptr = tokensBuf;	
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


