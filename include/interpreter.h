#ifndef __ZL_INTERPRETER_H__
#define __ZL_INTERPRETER_H__ 1

#include "lang.h"
#include "parser.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

object_t *SYM_LIST;

object_t *intern(char *label);

object_t *eval(object_t *expr, object_t *env);
object_t *evlist(object_t *exprs, object_t *env);
object_t *apply(object_t *proc, object_t *vals, object_t *env);

#ifdef __cplusplus
};
#endif

#endif
