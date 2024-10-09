#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "tokens.h"

#define MAX_LINE_SIZE  100
#define MAX_WORD_SIZE  32

int main(void)
{
	void hello_message(void);
	void analyze_line(char* line, int size);

	char lineBuf[MAX_LINE_SIZE];
	char lineBufIndex = 0;	

	uint8_t currentToken;
	char    c;

	hello_message();

	while(currentToken != EXIT){
		printf("dib-cli >>> ");

		while((c = getchar()) != '\n'){
			lineBuf[lineBufIndex++] = c;				
		}
		
		printf("---Start Analyzing Line---");	
	
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
	uint8_t tokensBuf[100];

	uint8_t search_token(char *word);

	while(*lptr != '\0'){
		if(isalpha(*lptr)){
			while(isalpha(*lptr)){
				*twptr   = *lptr;	
				twptr++;    lptr++;	
			}
			*twptr = '\0';
			search_token(tokenWord);
			twptr = tokenWord;
		}else{
			printf("\n--- \"%c\" is not alpha---\n", *lptr);	
			lptr++;
		}	
	}	
}


uint8_t search_token(char *word)
{
	//--------------------------
	// Search token numb by word
	// word = CREATE
	// enum dbTokens = CREATE
	//--------------------------
	printf("\nWord: %s \n", word);	
}


