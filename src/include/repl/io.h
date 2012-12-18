

#ifndef __ZELISP_REPL_IO_H__
#define __ZELISP_REPL_IO_H__ 1


#include "lang.h"



#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

#define READ_BUFFER 1024


int print_sexpr( top_t* sexpr );
char* read_sexpr( void );


#ifdef __cplusplus
};
#endif

#endif
