#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

#define MAX_WORD_SIZE      32
#define MAX_TOKEN_BUF_SIZE 128


Token *analyze_line(char *lptr, int size);

extern Token  *tokensBuf;
extern Token  *tbptr    ;  // token buf pointer

void freeTokensBuf(void);

#endif
