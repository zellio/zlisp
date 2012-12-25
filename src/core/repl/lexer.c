

#include <stdlib.h>

#include "repl/lexer.h"


token_t* token_create(void) {
    token_t* token = calloc(1, sizeof(token_t));
    if ( token == NULL )
        return NULL;
    return token;
}

int token_destroy(token_t* token) {
    if ( token == NULL )
        return -1;

    if ( token->data )
        free( token->data );

    free( token );

    return 0;
}

top_t* list_append(top_t* lp, top_t* cell) {
    if ( LANG_TYPE(lp) != LANG_T_CONS || LANG_TYPE(cell) != LANG_T_CONS )
        return NULL;
    ((cons_t*)lp)->cdr = cell;
    return cell;
}

top_t* list_append_token(top_t* lp, token_t* token) {
    return list_append(lp, cons((top_t*)token, NULL));
}

int is_number( char c ) {
    switch (c) {
    case '0':case '1':case '2':case '3':case '4':
    case '5':case '6':case '7':case '8':case '9':
        return 1;
    default:
        return 0;
    }
}

int is_alpha( char c ) {
    switch (c) {
    case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':
    case 'H':case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':
    case 'O':case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':
    case 'V':case 'W':case 'X':case 'Y':case 'Z':
        return 1;
    default:
        return 0;
    }
}

top_t* tokenize_string(char* string) {
    top_t* tokens = cons(NULL, NULL);

    char c;
    cons_t* current_cell = (cons_t*)tokens;
    token_t* token;

    char* p, * b, * s;
    unsigned int length;

 SKIP_CELL:
    while ((c = *string++)) {
        token = token_create();
        current_cell->car = (top_t*)token;
        switch (c) {
        case '(':
            token->type = LEXEME_T_LPAREN;
            token->data = NULL;
            break;
        case ')':
            token->type = LEXEME_T_RPAREN;
            token->data = NULL;
            break;
        case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':
        case 'H':case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':
        case 'O':case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':
        case 'V':case 'W':case 'X':case 'Y':case 'Z':
            token->type = LEXEME_T_SYMBOL;
            string--;
            p = string;
            length = 1;
            while ((is_number(*p++)||is_alpha(*p))) length++;
            b = s = calloc(length + 1, sizeof( char ));
            while ( length-- ) *s++ = *string++;
            token->data = b;
            break;
        case '0':case '1':case '2':case '3':case '4':
        case '5':case '6':case '7':case '8':case '9':
            token->type = LEXEME_T_NUMBER;
            token->data = 0;
            string--;
            while (is_number(*string))
                token->data = (void*)(((long)token->data) * 10L + ((*string++) - '0'));
            break;
        case '"':
            token->type = LEXEME_T_STRING;
            p = string; length = 0;
            while ( *p++ != '"' ) length++;
            b = s = calloc( length + 1, sizeof( char ));
            while ( length-- ) *s++ = *string++;
            string++;
            token->data = b;
            break;
        case ';':
            while (*string++!='\n');
        case ' ':case '\r':case '\n':case '\t':
            goto SKIP_CELL;
            break;
        default:
            return NULL;
            break;
        }
        current_cell->cdr = cons(NULL,NULL);
        current_cell = (cons_t*)current_cell->cdr;
    }

    token = token_create();
    token->type = LEXEME_T_END;
    token->data = "END";

    current_cell->car = (top_t*)token;

    return tokens;
}
