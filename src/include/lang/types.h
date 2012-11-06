

#ifndef __ZELISP_LANG_TYPES_H__
#define __ZELISP_LANG_TYPES_H__ 1


#include "lang/types/top.h"
#include "lang/types/atom.h"
#include "lang/types/cons.h"
#include "lang/types/boolean.h"


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


#define TYPE(x) (((top_t*)(x))->type)
#define LANG_TYPE(x) (TYPE(x) & 0x0F)

//


#ifdef __cplusplus
};
#endif

#endif
