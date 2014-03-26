#ifndef __ZEME_CORE_H__
#define __ZEME_CORE_H__ 1

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif


// "type/object"

// "type/boolean"
object_t *zeme_fn_not(object_t *args);

// "type/character"
object_t *zeme_fn_char_equal_predicate(object_t *args);
object_t *zeme_fn_char_lt_predicate(object_t *args);
object_t *zeme_fn_char_gt_predicate(object_t *args);
object_t *zeme_fn_char_lte_predicate(object_t *args);
object_t *zeme_fn_char_gte_predicate(object_t *args);
object_t *zeme_fn_char_to_fixnum(object_t *args);

// "type/fixnum"
object_t *zeme_fn_fixnum_to_char(object_t *args);
object_t *zeme_fn_fixnum_add(object_t *args);
object_t *zeme_fn_fixnum_subtract(object_t *args);
object_t *zeme_fn_fixnum_multiply(object_t *args);
object_t *zeme_fn_fixnum_quotient(object_t *args);
// object_t *zeme_fn_fixnum_remainder(object_t *args);
object_t *zeme_fn_fixnum_modulo(object_t *args);
// object_t *zeme_fn_fixnum_max(object_t *args);
// object_t *zeme_fn_fixnum_min(object_t *args);
// object_t *zeme_fn_fixnum_abs(object_t *args);
// object_t *zeme_fn_fixnum_numerator(object_t *args);
// object_t *zeme_fn_fixnum_denominator(object_t *args);
// object_t *zeme_fn_fixnum_gcd(object_t *args);
// object_t *zeme_fn_fixnum_lcm(object_t *args);
// object_t *zeme_fn_fixnum_floor(object_t *args);
// object_t *zeme_fn_fixnum_ceiling(object_t *args);
// object_t *zeme_fn_fixnum_truncate(object_t *args);
// object_t *zeme_fn_fixnum_round(object_t *args);
// object_t *zeme_fn_fixnum_rationalize(object_t *args);
// object_t *zeme_fn_fixnum_expt(object_t *args);

// "type/symbol"
object_t *zeme_fn_symbol_to_string(object_t* args);

// "type/pair"
object_t *zeme_fn_cons(object_t* args);
object_t *zeme_fn_car(object_t* args);
object_t *zeme_fn_cdr(object_t* args);
object_t *zeme_fn_set_car_bang(object_t* args);
object_t *zeme_fn_set_cdr_bang(object_t* args);

// "type/string"
object_t *zeme_fn_string_to_symbol(object_t* args);
object_t *zeme_fn_make_string(object_t* args);
object_t *zeme_fn_string_length(object_t* args);
object_t *zeme_fn_string_ref(object_t* args);
object_t *zeme_fn_string_set_bang(object_t* args);

// "type/vector"
object_t *zeme_fn_make_vector(object_t* args);
object_t *zeme_fn_vector_length(object_t* args);
object_t *zeme_fn_vector_ref(object_t* args);
object_t *zeme_fn_vector_set_bang(object_t* args);

// "type/port"

// "type/builtin"

// "type/closure"


#ifdef __cplusplus
};
#endif

#endif
