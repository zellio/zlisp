#ifndef __ZEME_TYPE_OBJECT_H__
#define __ZEME_TYPE_OBJECT_H__ 1

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

#define TYPE(x) (((object_t*)(x))->type)
#define IS_TYPE(x, type) (TYPE(x) == (type))

typedef enum {
    SCHEME_TYPE_NIL,
    SCHEME_TYPE_TRUE,
    SCHEME_TYPE_FALSE,
    SCHEME_TYPE_CHARACTER,
    SCHEME_TYPE_FIXNUM,
    SCHEME_TYPE_SYMBOL,
    SCHEME_TYPE_PAIR,
    SCHEME_TYPE_STRING,
    SCHEME_TYPE_VECTOR,
    SCHEME_TYPE_PORT,
    SCHEME_TYPE_BUILTIN,
    SCHEME_TYPE_CLOSURE
} object_type;

typedef struct object object_t;
struct object {
    object_type type;

    int (*comperator)(object_t *self, object_t *other);
    int (*destructor)(object_t *self);
    char *(*to_string)(object_t *self);

    union {
        /* SCHEME_TYPE_CHARACTER, */
        struct {
            char value;
        } character;

        /* SCHEME_TYPE_FIXNUM, */
        struct {
            int64_t value;
        } fixnum;

        /* SCHEME_TYPE_SYMBOL, */
        struct {
            uint64_t hash;
            char *value;
        } symbol;

        /* SCHEME_TYPE_PAIR, */
        struct {
            object_t *car;
            object_t *cdr;
        } pair;

        /* SCHEME_TYPE_STRING, */
        struct {
            size_t length;
            char *value;
        } string;

        /* SCHEME_TYPE_VECTOR, */
        struct {
            size_t length;
            object_t **value;
        } vector;

        /* SCHEME_TYPE_PORT, */
        struct {
            FILE *value;
        } port;

        /* SCHEME_TYPE_BUILTIN, */
        struct {
            object_t *(*fn)(object_t *arguments, object_t *env);
        } builtin;

        /* SCHEME_TYPE_CLOSURE */
        struct {
            object_t *parameters;
            object_t *body;
            object_t *env;
        } closure;
    } as;
};

void error(char *message);
char *typed_pointer_to_string(char *type, size_t type_length, void *ptr);

object_t *object_alloc(void);
int object_free(object_t *object);

object_t *object_create(object_type type);
int object_destroy(object_t *object);

int object_compare(object_t *object1, object_t *object2);
char *object_to_string(object_t *object);

#ifdef __cplusplus
};
#endif

#endif
