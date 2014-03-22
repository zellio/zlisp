#include <math.h>
// #include <stdio.h>
#include "type/port.h"

object_t *port_create(FILE* stream) {
    object_t *port = object_create(SCHEME_TYPE_PORT);
    if (port == NULL)
        error("Out of memory error in `pair_create`");

    port->as.port.value = stream;

    port->comperator = &port_comperator;
    port->destructor = &port_destructor;
    port->to_string = &port_to_string;

    return port;
}

int port_destructor(object_t *self) {
    return object_free(self);
}
int port_comperator(object_t *self, object_t *other) {
    return self - other;
}

char *port_to_string(object_t *self) {
    FILE *file = self->as.port.value;
    int32_t fd = fileno(file);
    int32_t fd_length = floor(log10(fd)) + 1;
    size_t str_len = fd_length + 8 + 1;
    char *str = calloc(str_len, sizeof(char));

    snprintf(str, str_len, "#<Port:%d>", fd);

    return str;
}
