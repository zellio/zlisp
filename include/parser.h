#ifndef __ZEME_PARSER_H__
#define __ZEME_PARSER_H__ 1

#include "lexer.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

typedef struct parser parser_t;
struct parser {
    lexeme_t *tokens;
    object_t *sym_list;
    object_t *ast;
};

parser_t *parser_create(lexeme_t *tokens);
int parser_destroy(parser_t *parser);

object_t *parser_intern(parser_t *self, char *label);

lexeme_t *parser_tokens_pop(parser_t *self);
parser_t *parser_tokens_push(parser_t *self, lexeme_t *token);
#define parser_tokens_peak(x) ((x)->tokens)

lexeme_t *parser_accept(parser_t *self, lexeme_type type);
lexeme_t *parser_expect(parser_t *self, lexeme_type type);

object_t *parser_read_atom(parser_t *self);
object_t *parser_read_list(parser_t *self);
object_t *parser_read_expr(parser_t *self);

object_t *parse(lexeme_t *tokens);


#ifdef __cplusplus
};
#endif

#endif
