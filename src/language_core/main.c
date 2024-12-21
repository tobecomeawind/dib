#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "lexer.h"
#include "tokens.h"
#include "parser.h"
#include "entity_type.h"

#define MAX_LINE_SIZE 128

static void hello_message(void);

void invokeCliIteration(void);
void invokeCliError(char*);

static char   lineBuf[MAX_LINE_SIZE]; // command line
static size_t lineBufIndex = 0;

int main(void)
{
	//---------------------//
	//The main CLI process //
	//Manager  CLI commands//
	//---------------------//
	
	
	initEntitiesTempTable();

	Token *ptr;

	hello_message();

	for(;;) {
		invokeCliIteration();
	}

	return 0;
}


void invokeCliIteration(void)
{
	char letter;

	printf("\ndib-cli >>> ");

	while( ( (letter = getchar()) != '\n') && (lineBufIndex < MAX_LINE_SIZE) ){
		lineBuf[lineBufIndex++] = letter;	
	}
		
	lineBuf[lineBufIndex] = '\0';	
	analyze_line(lineBuf, lineBufIndex);
	
	lineBufIndex = 0;	
	
	startParsing();
}	


void invokeCliError(char* errorWord)
{
	printf("\nError~~~ %s\n", errorWord);
	lineBufIndex = 0;
	//free(errorWord);
    invokeCliIteration();	
}


static void hello_message(void)
{
	//----------------------------
	//The first output of programm
	//General information
	//----------------------------

	printf("\n Hello in DIB, version is 0.0.0.0 \n");
	printf(" ---Copyright: tobecomeawind--- \n\n");	
}
