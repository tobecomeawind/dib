
#ifndef TYPES_H
#define TYPES_H

typedef enum vtypes{
	CHAR  = 0b00000001,  // idea for char type 
						 // the last bit says the type == char
						 // the another bits says about size, 
						 // including the first bit
						 // 
						 // if bit another bytes are zero
						 // 	size == 1 byte
						 // else 
						 // 	size == CHAR(for example 0b01110001)
						 //                  char with size 2^4 + 2^5 + 2^6
						 
	INT   = 0b00000010,
	FLOAT = 0b00000100	
} vtypes; // variable types

#endif
