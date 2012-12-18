

#include "repl/parser.h"


top_t* parse(char* buffer) {
    parser_context_t* cntx = _parse(&(parser_context_t){buffer, NULL});
    return cntx->data;
}

parser_context_t* _parse(parser_context_t* cntx) {
    char* buffer = cntx->buffer;
    top_t* sexpr = cntx->data;

    if ( !buffer )
        return NULL;

    parser_context_t* next_cntx;

    switch (*buffer) {
    case '(':
        next_cntx = _parse_list(&(parser_context_t){buffer + 1, sexpr});
        break;
    case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
        next_cntx = _parse_number(&(parser_context_t){buffer, sexpr});
        break;
    case 'A':case 'B':case 'C':case 'D':case 'E':
    case 'F':case 'G':case 'H':case 'I':case 'J':
    case 'K':case 'L':case 'M':case 'N':case 'O':
    case 'P':case 'Q':case 'R':case 'S':case 'T':
    case 'U':case 'V':case 'W':case 'X':case 'Y':
    case 'Z':
        next_cntx = _parse_symbol(&(parser_context_t){buffer, sexpr});
        break;
    case ' ':case '\t':case '\r':case '\n':
        return _parse(&(parser_context_t){ buffer + 1, sexpr });
        break;
    default:
        return NULL;
    }

    return &(parser_context_t){ next_cntx->buffer, next_cntx->data };
}

parser_context_t* _parse_list(parser_context_t* cntx) {
    char* buffer = cntx->buffer;
    top_t* head = NULL;
    top_t* tail = NULL;
    cons_t* next_cons;

    while ( *buffer != ')') {
        parser_context_t* next_cntx = _parse(&(parser_context_t){buffer, NULL});

        buffer = next_cntx->buffer;
        next_cons = (cons_t*)cons( next_cntx->data, NULL );

        if ( head == NULL ) {
            head = (top_t*)next_cons;
            tail = head;
        }
        else {
            ((cons_t*)tail)->cdr = (top_t*)next_cons;
            tail = ((cons_t*)tail)->cdr;
        }
    }
    return &(parser_context_t){buffer + 1, head};
}

parser_context_t* _parse_symbol(parser_context_t* cntx) {
    char* buffer = cntx->buffer;

    int loop = 1;
    char* end = buffer;

    while ( loop ) {
        switch (*end) {
        case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':
        case 'G':case 'H':case 'I':case 'J':case 'K':case 'L':
        case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':
        case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':
        case 'Y':case 'Z':case '0':case '1':case '2':case '3':
        case '4':case '5':case '6':case '7':case '8':case '9':
            break;
        default:
            loop = 0;
            end--;
            break;
        }
        end++;
    }

    char save_end = *end;
    *end = '\0';
    top_t* sym = atom_create_symbol( buffer );
    *end = save_end;

    cntx->buffer = end;
    cntx->data = sym;

    return cntx;
}

parser_context_t* _parse_number(parser_context_t* cntx) {
    char* buffer = cntx->buffer;

    long number = 0;
    int loop = 1;

    while ( loop ) {
        switch (*buffer) {
        case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
            number = number * 10 + (*buffer) - '0';
            break;
        default:
            loop = 0;
            buffer--;
        }
        buffer++;
    }

    cntx->buffer = buffer;
    cntx->data = atom_create_number( number );

    return cntx;
}
