

#ifndef __ZELISP_LANG_TYPE_BOOLEAN_H__
#define __ZELISP_LANG_TYPE_BOOLEAN_H__ 1


#include "lang/types/top.h"
#include "lang/types/atom.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


#define TRUE (boolean_true())
#define FALSE NULL
#define AS_BOOLEAN(x) ((x)) ? TRUE : FALSE

top_t* boolean_true(void);


#ifdef __cplusplus
};
#endif

#endif
