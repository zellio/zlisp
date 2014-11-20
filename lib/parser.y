%{
#include "lang.h"
#include "parser.h"
#include "lexer.h"

#include <stdint.h>

extern int yylex();

void yyerror(void *scanner, const char *s) { printf("ERROR: %s\n", s); }

object_t *root;
%}

%debug
%pure-parser
%lex-param {void *scanner}
%parse-param {void *scanner}

%code provides {
    int zlisp_parse(char *str, object_t **node);
}

%union {
    char *str;
    uint64_t fixnum;
    double real;
    uint64_t token;
}

%token  <str>     TOKEN_COMMENT
%token  <token>   TOKEN_L_PAREN
%token  <token>   TOKEN_R_PAREN
%token  <token>   TOKEN_DOT
%token  <token>   TOKEN_QUOTE
%token  <token>   TOKEN_BACK_QUOTE
%token  <str>     TOKEN_SYMBOL
%token  <str>     TOKEN_STRING
%token  <fixnum>  TOKEN_FIXNUM
%token  <real>    TOKEN_REAL
%token  <str>     TOKEN_CHARACTER
%token  <token>   TOKEN_WHITESPACE

%start program

%%

program:        /* empty */
        |       exprs
        ;

exprs:          expr
        |       exprs expr
        ;

expr:           atom
        |       TOKEN_L_PAREN expr TOKEN_DOT expr TOKEN_R_PAREN
        |       list
        ;

list:           TOKEN_L_PAREN exprs TOKEN_R_PAREN
        ;

atom:           TOKEN_SYMBOL
        |       TOKEN_STRING
        |       TOKEN_FIXNUM
        |       TOKEN_REAL
        |       TOKEN_CHARACTER
        ;

%%

int zlisp_parse(char *text, object_t **node)
{
    // yydebug = 1;

    yyscan_t scanner;
    yylex_init(&scanner);
    YY_BUFFER_STATE buffer = yy_scan_string(text, scanner);
    int rc = yyparse(scanner);
    yy_delete_buffer(buffer, scanner);
    yylex_destroy(scanner);

    // If parse was successful, return root node.
    if(rc == 0) {
        *node = root;
        return 0;
    }
    // Otherwise return error.
    else {
        return -1;
    }
}
