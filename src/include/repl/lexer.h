

#ifndef __ZELISP_REPL_LEXER_H__
#define __ZELISP_REPL_LEXER_H__ 1


#include "lang/types/cons.h"
#include "lang/functions/elementary.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


typedef enum {
    LEXEME_T_NONE = 0x00,
    LEXEME_T_LPAREN = 0x01,
    LEXEME_T_RPAREN = 0x02,
    LEXEME_T_SYMBOL = 0x03,
    LEXEME_T_NUMBER = 0x04,
    LEXEME_T_STRING = 0x05,
    LEXEME_T_END = 0xFF
} lexeme_type_e;

typedef struct token token_t;
struct token {
    type_e type;
    void* data;
};

token_t* token_create(void);
int token_destroy(token_t* token);

top_t* list_append(top_t* lp, top_t* cell);
top_t* list_append_token(top_t* lp, token_t* token);

top_t* tokenize_string(char* string);

int is_number( char c );
int is_alpha( char c );


#ifdef __cplusplus
};
#endif

#endif
