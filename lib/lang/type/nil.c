#include "lang/type/nil.h"

object_t *nil_create(void)
{
	static object_t *nil = NULL;

	if (nil == NULL) {
		nil = object_create(TYPE_NIL);
		if (nil == NULL)
			error("Out of memeory error in `create_nil`");

		nil->to_string = &nil_to_string;
	}

	return nil;
}

char *nil_to_string(object_t *self)
{
	char *str = calloc(4, 1);
	strncpy(str, "nil", 3);
	return str;
}
