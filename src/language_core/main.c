#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "tokens.h"
#include "lexer.h"


#define MAX_LINE_SIZE      128

int main(void)
{
	//---------------------//
	//The main CLI process //
	//Manager  CLI commands//
	//---------------------//
	
	void hello_message(void);

	char   lineBuf[MAX_LINE_SIZE];
	size_t lineBufIndex = 0;	

	Token *ptr;

	char c;


	hello_message();

	while(true){
		printf("dib-cli >>> ");

		while(((c = getchar()) != '\n') && (lineBufIndex < MAX_LINE_SIZE)){
			lineBuf[lineBufIndex++] = c;				
		}
			
		lineBuf[lineBufIndex] = '\0';	
		ptr = analyze_line(lineBuf, lineBufIndex);
		
		//parse(ptr)....

		free(ptr);
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

	printf("\n Hello in DIB, version is 0.0.0.0 \n");
	printf(" ---Copyright: tobecomeawind--- \n\n");	
}
