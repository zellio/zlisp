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
    object_t *obj;
}

%token  <token>   TOKEN_L_PAREN TOKEN_R_PAREN TOKEN_DOT TOKEN_QUOTE
%token  <token>   TOKEN_BACK_QUOTE TOKEN_WHITESPACE
%token  <str>     TOKEN_COMMENT TOKEN_CHARACTER TOKEN_SYMBOL TOKEN_STRING
%token  <fixnum>  TOKEN_FIXNUM
%token  <real>    TOKEN_REAL

%type   <obj>     exprs expr list atom

%start program

%%

program:        /* empty */
        |       exprs       { root = $1; }
        ;

exprs:          expr
        |       exprs expr  { $$ = pair_create($1, $2); }
        ;

expr:           atom
        |       TOKEN_L_PAREN expr TOKEN_DOT expr TOKEN_R_PAREN { $$ = pair_create($2, $4); }
        |       list
        ;

list:           TOKEN_L_PAREN exprs TOKEN_R_PAREN { $$ = $2; }
        ;

atom:           TOKEN_SYMBOL     { $$ = symbol_create($1); free($1); }
        |       TOKEN_STRING     { $$ = string_create($1); free($1); }
        |       TOKEN_FIXNUM     { $$ = fixnum_create($1); }
        |       TOKEN_REAL       { $$ = real_create($1); }
        |       TOKEN_CHARACTER  { $$ = character_create($1[2]); free($1); }
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
