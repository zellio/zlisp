

#ifndef __ZELISP_REPL_PARSER_H__
#define __ZELISP_REPL_PARSER_H__ 1


#include "lang.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif



typedef struct parser_context parser_context_t;
struct parser_context {
    char* buffer;
    top_t* data;
};


top_t* parse(char* buffer);

parser_context_t* _parse(parser_context_t* cntx);
parser_context_t* _parse_list(parser_context_t* cntx);
parser_context_t* _parse_symbol(parser_context_t* cntx);
parser_context_t* _parse_number(parser_context_t* cntx);


#ifdef __cplusplus
};
#endif

#endif
