#include "lang/core.h"

object_t *zlc_eq(object_t *obj1, object_t *obj2)
{
    if (is_pair(obj1) || is_pair(obj2))
        return ZLC_NIL;

    return (obj1 == obj2) ? ZLC_TRUE : ZLC_FALSE;
}

object_t *zlc_assoc(object_t *key, object_t *alist)
{
    if (!is_pair(alist))
        error("Type error in `zlc_assoc'");

    for (object_t **node = &alist; is_pair(*node); node = &pair_cdr(*node))
        if (is_pair(*node) && object_compare(pair_caar(*node), key) == 0)
            return pair_car(*node);

    return ZLC_NIL;
}

object_t *zlc_acons(object_t *key, object_t *val, object_t *alist)
{
    return pair_create(pair_create(key, val), alist);
}
