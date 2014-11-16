#ifndef __ZEME_LEXER_H__
#define __ZEME_LEXER_H__ 1

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

/// lexer
typedef enum {
    TOKEN_NONE,
    TOKEN_SEMICOLON,
    TOKEN_L_PAREN,
    TOKEN_R_PAREN,
    TOKEN_DOT,
    TOKEN_SYMBOL,
    TOKEN_QUOTE,
    TOKEN_BACK_QUOTE,
    TOKEN_DOUBLE_QUOTE,
    TOKEN_CHARACTER,
    TOKEN_FIXNUM,
    TOKEN_END
} lexeme_type;

typedef struct lexeme lexeme_t;
struct lexeme {
    lexeme_type type;
    char *value;
    lexeme_t *next;
};

lexeme_t *lexeme_create(void);
int lexeme_destroy(lexeme_t *self);

lexeme_t *lex_str(char *str);

void lex_print(lexeme_t *self);
void lex_dump_tokens(lexeme_t *self);

#ifdef __cplusplus
};
#endif

#endif
