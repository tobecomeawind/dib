#ifndef PARSER_H
#define PARSER_H

#define TOKEN_TEMP_SIZE 10

void startParsing(void);

typedef enum {
	PARENSES,

} bordersType;

typedef enum is_next_token_check_t {
	
	NO_ARGS = 0x00,
    TEMP    = 0x01, // add    token in temp buf
    MINOR   = 0x02, // check  minor value	
    ERROR   = 0x04, // invoke error

} isNextTokenArg;

typedef enum parse_entity_check_t {
	
	E_ENTITY   = 0x01,
	E_DATA     = 0x02,
	E_DATATYPE = 0x04,

} parseEntityArg;


#endif
