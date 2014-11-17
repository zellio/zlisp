
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

lexeme_t *lexeme_create(void) {
    lexeme_t *obj = calloc(1, sizeof(lexeme_t));
    if (obj == NULL)
        error("Memory allocation error in `lexeme_create'");

    obj->type = TOKEN_NONE;

    return obj;
}

int lexeme_destroy(lexeme_t *lexeme) {
    if (lexeme == NULL)
        return -1;

    free(lexeme);

    return 0;
}

char *resizemem(char *block, size_t size, size_t new_size) {
    size_t copy_size = (size < new_size) ? size : new_size;
    char *new_block = calloc(new_size, 1);
    while (copy_size--) new_block[copy_size] = block[copy_size];
    return new_block;
}

int is_digit(char c) {
    return (0x30 <= c && c <= 0x39);
}

int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

int is_delim(char c) {
    return (is_whitespace(c)||c=='('||c==')'||c==';'||c=='"'||c=='\''||c=='`'||c=='|'||c=='\0');
}

lexeme_t *lex_str(char *str) {
    size_t b_size = 1024U;
    size_t b_used = 0U;
    char *b = calloc(b_size, 1);

    lexeme_t *lexemes = lexeme_create();
    lexeme_t *current_lexeme = lexemes;

    char c;
    while (1) {
        c = *str++;

        if (c == '\0') {
            current_lexeme->type = TOKEN_END;
        }

        else if (is_whitespace(c)) {
            continue;
        }

        // TOKEN_SEMICOLON,
        else if (c == ';') {
            while (*str != '\n') {
                b[b_used++] = *str++;
                if (b_used == b_size) {
                    size_t ns = b_size << 2;
                    char *nb = resizemem(b, b_size, ns);
                    free(b);
                    b = nb;
                    b_size = ns;
                }
            }
            current_lexeme->type = TOKEN_SEMICOLON;
        }

        // TOKEN_L_PAREN,
        else if (c == '(') {
            current_lexeme->type = TOKEN_L_PAREN;
        }

        // TOKEN_R_PAREN,
        else if (c == ')') {
            current_lexeme->type = TOKEN_R_PAREN;
        }

        // TOKEN_DOT,
        else if (c == '.') {
            current_lexeme->type = TOKEN_DOT;
        }

        // TOKEN_QUOTE,
        else if (c == '\'') {
            current_lexeme->type = TOKEN_QUOTE;
        }

        // TOKEN_BACK_QUOTE,
        else if (c == '`') {
            current_lexeme->type = TOKEN_BACK_QUOTE;
        }

        // TOKEN_DOUBLE_QUOTE,
        else if (c == '"') {
            while (*str != '"') {
                if (*str == '\\') {
                    str++;
                    switch (*str++) {
                    case 'a'  : b[b_used++] = '\a'; break;
                    case 'b'  : b[b_used++] = '\b'; break;
                    case 't'  : b[b_used++] = '\t'; break;
                    case 'n'  : b[b_used++] = '\n'; break;
                    case 'v'  : b[b_used++] = '\v'; break;
                    case 'f'  : b[b_used++] = '\f'; break;
                    case 'r'  : b[b_used++] = '\r'; break;
                    case '"'  : b[b_used++] = '"';  break;
                    case '\\' : b[b_used++] = '\\'; break;
                    default:
                        error("Invalid escape sequence in tokenizer");
                    }
                }
                else {
                    b[b_used++] = *str++;
                }
                if (b_used == b_size) {
                    size_t ns = b_size << 2;
                    char *nb = resizemem(b, b_size, ns);
                    free(b);
                    b = nb;
                    b_size = ns;
                }
            }
            str++;
            current_lexeme->type = TOKEN_DOUBLE_QUOTE;
        }

        // TOKEN_CHARACTER,
        else if (c == '#') {
            if (*str++ == '\\') {
                b[b_used++] = *str++;
            }
            else {
                error("Invalid character sequence");
            }
            current_lexeme->type = TOKEN_CHARACTER;
        }

        // TOKEN_FIXNUM,
        else if (is_digit(c) || ((c == '-' || c == '+') && is_digit(*str))) {
            while (is_digit(c)) {
                b[b_used++] = c;
                c = *str++;
                if (b_used == b_size) {
                    size_t ns = b_size << 2;
                    char *nb = resizemem(b, b_size, ns);
                    free(b);
                    b = nb;
                    b_size = ns;
                }
            }
            str--;
            current_lexeme->type = TOKEN_FIXNUM;
        }

        // TOKEN_SYMBOL
        else if (c == '|') {
            b[b_used++] = c;
            while (*str != '|') {
                if (*str == '\\') {
                    str++;
                }
                b[b_used++] = *str++;
            }
            b[b_used++] = *str++;
            current_lexeme->type = TOKEN_SYMBOL;
        }
        else if (!is_delim(c)) {
            while (!is_delim(c)) {
                b[b_used++] = c;
                c = *str++;

                if (b_used == b_size) {
                    size_t ns = b_size << 2;
                    char *nb = resizemem(b, b_size, ns);
                    free(b);
                    b = nb;
                    b_size = ns;
                }
            }
            str--;
            current_lexeme->type = TOKEN_SYMBOL;
        }

        if (current_lexeme->type == TOKEN_END)
            break;

        if (current_lexeme->type == TOKEN_NONE) {
            error("Error in lexer unknow token type");
        }
        if (b_used) {
            current_lexeme->value = calloc(1, b_used + 1);
            while (b_used--) {
                current_lexeme->value[b_used] = b[b_used];
                b[b_used] = '\0';
            }
            b_used = 0;
        }

        current_lexeme->next = lexeme_create();
        current_lexeme = current_lexeme->next;
    }

    return lexemes;
}

void lex_print(lexeme_t *self) {
    fprintf(stdout, "Lexeme: \n");
    switch (self->type) {
    case TOKEN_NONE         : fprintf(stdout, "  type: TOKEN_NONE\n");          break;
    case TOKEN_SEMICOLON    : fprintf(stdout, "  type: TOKEN_SEMICOLON\n");     break;
    case TOKEN_L_PAREN      : fprintf(stdout, "  type: TOKEN_L_PAREN\n");       break;
    case TOKEN_R_PAREN      : fprintf(stdout, "  type: TOKEN_R_PAREN\n");       break;
    case TOKEN_DOT          : fprintf(stdout, "  type: TOKEN_DOT\n");           break;
    case TOKEN_SYMBOL       : fprintf(stdout, "  type: TOKEN_SYMBOL\n");        break;
    case TOKEN_QUOTE        : fprintf(stdout, "  type: TOKEN_QUOTE\n");         break;
    case TOKEN_BACK_QUOTE   : fprintf(stdout, "  type: TOKEN_BACK_QUOTE\n");    break;
    case TOKEN_DOUBLE_QUOTE : fprintf(stdout, "  type: TOKEN_DOUBLE_QUOTE\n");  break;
    case TOKEN_CHARACTER    : fprintf(stdout, "  type: TOKEN_CHARACTER\n");     break;
    case TOKEN_FIXNUM       : fprintf(stdout, "  type: TOKEN_FIXNUM\n");        break;
    case TOKEN_END          : fprintf(stdout, "  type: TOKEN_END\n");           break;
    }

    fprintf(stdout, "  value: %s\n", self->value);
}

void lex_dump_tokens(lexeme_t *self) {
    while (self) {
        lex_print(self);
        self = self->next;
    }
}
