
#include "parser.h"

#include <string.h>

parser_t *parser_create(lexeme_t *tokens) {
    parser_t *obj = calloc(1, sizeof(parser_t));
    if (obj == NULL)
        error("Memory allocation error in `parser_create'");

    obj->tokens = tokens;
    obj->sym_list = nil_create();

    return obj;
}

int parser_destroy(parser_t *parser) {
    free(parser);
    return 0;
}

object_t *parser_intern(parser_t *self, char *label) {
    object_t *sym;

    for (object_t *ss = self->sym_list; !is_nil(ss); ss = pair_cdr(ss)) {
        sym = pair_car(ss);
        if (!strcmp(label, (sym->as.symbol.value)))
            return sym;
    }

    sym = symbol_create(label);
    self->sym_list = pair_create(sym, self->sym_list);
    return sym;
}

lexeme_t *parser_tokens_pop(parser_t *self) {
    lexeme_t *x = self->tokens;
    self->tokens = x->next;

    return x;
}

parser_t *parser_tokens_push(parser_t *self, lexeme_t *token) {
    token->next = self->tokens;
    self->tokens = token;

    return self;
}

lexeme_t *parser_accept(parser_t *self, lexeme_type type) {
    if (parser_tokens_peak(self)->type == type)
        return parser_tokens_pop(self);

    return NULL;
}

lexeme_t *parser_expect(parser_t *self, lexeme_type type) {
    if (parser_tokens_peak(self)->type == type)
        return parser_tokens_pop(self);

    lex_dump_tokens(self->tokens);

    error("Unexpected token type in `parser_expect'");
    return NULL;
}

object_t *parser_read_atom(parser_t *self) {
    lexeme_t *tok;

    if ((tok = parser_accept(self, TOKEN_SYMBOL))) {
        return parser_intern(self, tok->value);
    }
    else if ((tok = parser_accept(self, TOKEN_DOUBLE_QUOTE))) {
        return string_create(tok->value);
    }
    else if ((tok = parser_accept(self, TOKEN_CHARACTER))) {
        return character_create(*tok->value);
    }
    else if ((tok = parser_accept(self, TOKEN_FIXNUM))) {
        char *str = tok->value;
        int64_t value = 0;

        if (str[0] == '-') {
            value = -1;
            str++;
        }

        if (str[0] == '+') {
            str++;
        }

        while (*str) value = value * 10 + (*str++ - 0x30);
        return fixnum_create(value);
    }

    return NULL;
}

object_t *parser_read_list(parser_t *self) {
    parser_expect(self, TOKEN_L_PAREN);

    object_t *nil = nil_create();
    object_t *list = nil;
    object_t *cell = list;

    if (parser_accept(self, TOKEN_R_PAREN))
        return list;

    object_t *car = parser_read_expr(self);

    lexeme_t *tok;

    if ((tok = parser_accept(self, TOKEN_DOT))) {
        object_t *cdr = parser_read_expr(self);
        list = pair_create(car, cdr);
        parser_expect(self, TOKEN_R_PAREN);
    }
    else {
        list = pair_create(car, list);
        cell = list;
        while (!(parser_accept(self, TOKEN_R_PAREN))) {
            car = parser_read_expr(self);
            pair_set_cdr(cell, pair_create(car, nil));
            cell = pair_cdr(cell);
        }
    }

    return list;
}

object_t *parser_read_expr(parser_t *self) {
    if (parser_tokens_peak(self)->type == TOKEN_L_PAREN) {
        return parser_read_list(self);
    }
    else {
        return parser_read_atom(self);
    }
}

object_t *parse(lexeme_t *tokens) {
    parser_t *parser = parser_create(tokens);
    object_t *ast = parser_read_expr(parser);
    parser_expect(parser, TOKEN_END);
    parser->ast = ast;
    return ast;
}
