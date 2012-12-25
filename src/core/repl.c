

//#include "repl.h"

#include <stdio.h>

//#include "repl/lexer.h"


#include "lang.h"
#include "repl/parser.h"

int main( void ) {

    //    top_t* foo = tokenize_string("");
    //
    //    top_t* x;
    //    while ( foo ) {
    //        x = car(foo);
    //
    //        if ( x ) {
    //        printf("LEXEME> ");
    //        switch (((lexeme_type_e)x->type)) {
    //        case LEXEME_T_NONE:
    //            printf( "NONE" );
    //            break;
    //        case LEXEME_T_LPAREN:
    //            printf( "(" );
    //            break;
    //        case LEXEME_T_RPAREN:
    //            printf( ")" );
    //            break;
    //        case LEXEME_T_STRING:
    //        case LEXEME_T_SYMBOL:
    //            printf( "%s", (char*)((token_t*)x)->data );
    //            break;
    //        case LEXEME_T_NUMBER:
    //            printf( "%ld", ((long)((token_t*)x)->data) );
    //            break;
    //        case LEXEME_T_END:
    //            printf( "<END>" );
    //            break;
    //        default:
    //            printf( "WELP" );
    //            break;
    //        }
    //        }
    //        printf( "\n" );
    //        foo = cdr(foo);
    //    }
    //
    //
    //
    //
    char* buffer;
    top_t* ast;

    printf( "Welcome to an amazing lazy LISP REPL\n" );

    while ( 1 ) {
        printf( "* " );
        buffer = read_sexpr();
        ast = eval(parse(buffer), NULL);
        print_sexpr( ast );
        printf("\n");
    }

    return 0;
}
