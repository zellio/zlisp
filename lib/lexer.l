%{
#include "lang.h"
#include "parser.h"

#define TOKEN(type) (yylval->token = (type))

#include <string.h>
%}

%option noyywrap
%option reentrant
%option bison-bridge

%%

;.*\n                                     { strndup(yytext, yyleng); return TOKEN_COMMENT; }
\(                                        { return TOKEN(TOKEN_L_PAREN); }
\)                                        { return TOKEN(TOKEN_R_PAREN); }
\.                                        { return TOKEN(TOKEN_DOT); }
\'                                        { return TOKEN(TOKEN_QUOTE); }
`                                         { return TOKEN(TOKEN_BACK_QUOTE); }
#\.                                       { yylval->str = strndup(yytext, yyleng); return TOKEN_CHARACTER; }
\"([^\"]|\\\")+\"                         { yylval->str = strndup(yytext, yyleng); return TOKEN_STRING; }
[+-]?[0-9]+                               { yylval->fixnum = atof(yytext); return TOKEN_FIXNUM; }
[+-]?[0-9]+\.[0-9]+                       { yylval->real = atof(yytext); return TOKEN_REAL; }
(\|([^|]|\\\|)*\||[^();\"\'`|\0 \n\r\t]+) { yylval->str = strndup(yytext, yyleng); return TOKEN_SYMBOL; }
[ \n\r\t]+                                { return TOKEN(TOKEN_WHITESPACE); }
.                                         { printf("Unknown token!"); yyterminate(); }
