#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"
#include "stdbool.h"

#define MAX_WORD_SIZE      32

bool analyze_line(char *lptr, int size);

void freeTokensBuf(void);

#endif
