#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "tokens.h"

bool analyze_line(char* lptr, int size)
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
		if ( isAlNum(*lptr) ) {
		
			do{
				*twptr++ = *lptr;
			} while( isAlNum(*++lptr) );
			
			*twptr = '\0';
			

			if ( isKeyword(tokenWord, tmpToken) ) {
				appendToken(tmpToken->majorType,
							tmpToken->minorType,
							tmpToken->data);		
			} else {

				// exit 
				if ( strcmp(tokenWord, "q") == 0 ) {
					freeTokensBuf();	
					free(tokenWord);
					free(tmpToken);	
					return false;
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

			if ( isParenses(*lptr) ) {
	
				switch ( *lptr ) {
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
	
			} else if ( isColon(*lptr) ) {

				appendToken(CLETTERS,
							COLON, 
							tokenWord);		
					
			} else if ( isComma(*lptr) ) {

				appendToken(CLETTERS,
							COMMA,
						    tokenWord);	

			} else if ( isLink(*lptr) ) {
			
				appendToken(CLETTERS,
							LINK,
						    tokenWord);	

			} else if ( isDoubleLink(*lptr, *(lptr + 1)) ) {
					
				appendToken(CLETTERS,
							DLINK,
						    "<>");
				lptr++;	

			} else {
				if( !isWhiteSpace(*lptr) )	
					printf("\n\"Undefined char - %c\"\n", *lptr);		
			}
		
			twptr = tokenWord;

			lptr++; // last symbol jump fix
		}	
	}


	shiftTokensBufPointer();	

	free(tokenWord);
	free(tmpToken);	

	return true;	
}
