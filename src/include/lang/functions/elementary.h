
#ifndef __ZELISP_LANG_FUNCTIONS_ELEMENTARY_H__
#define __ZELISP_LANG_FUNCTIONS_ELEMENTARY_H__ 1


#include "lang/types.h"



#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


top_t* cons( top_t* car, top_t* cdr );
top_t* car( top_t* sexpr );
top_t* cdr( top_t* sexpr );
top_t* eq( top_t* l, top_t* r );
top_t* atom( top_t* sexpr );

top_t* caar( top_t* sexpr );
top_t* cadr( top_t* sexpr );
top_t* cdar( top_t* sexpr );

top_t* caddr( top_t* sexpr );
top_t* cadar( top_t* sexpr );


#ifdef __cplusplus
};
#endif

#endif
