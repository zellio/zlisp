#include "repl.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    fprintf(stdout, "Zeme 0.1.0\n");
    fprintf(stdout, "Copyright (C) 2014 Zachary Elliott\n\n");
    fprintf(stdout, "Zeme is a toy implementation of scheme.\n");

    size_t buffer_size = 1024L;
    char *buffer = calloc(buffer_size, 1);

    object_t *env = init_env();

    while (1) {
        fprintf(stdout, "* ");

        fgets(buffer, buffer_size - 1, stdin);

        lexeme_t *toks = lex_str(buffer);
        object_t *ast = parse(toks);
        object_t *result = eval(ast, env);

        fprintf(stdout, "%s\n\n", object_to_string(result));

        memset(buffer, '\0', buffer_size);
    }

    free(buffer);

    return 0;
}
