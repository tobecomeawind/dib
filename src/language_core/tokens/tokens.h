#ifndef TOKENS_H
#define TOKENS_H

typedef enum
{
	SPAWN,

	OPEN_PARENTS,  // (
	CLOSE_PARENTS,  // )	
	
	OPEN_BRACES,  // {
	CLOSE_BRACES, // }

	ENTITY,
	REL,
	NAME

} dbTokens;

typedef enum
{
	EXIT = 1,
	NEXT_ROW,	

} cliTokens;

#endif
