CC=clang
RM=rm -Rf

CFLAGS=-ggdb -x c --std=c99 -c -Wall -Wextra -Werror -pedantic-errors -ferror-limit=1

SRCROOT=lib
INCROOT=include
TSTROOT=test

OBJROOT=build

VPATH=$(SRCROOT):$(INCROOT):$(TSTROOT):$(OBJROOT)

.PHONY: all clean types core

types: object.o boolean.o character.o fixnum.o symbol.o pair.o string.o\
  vector.o port.o builtin.o closure.o

core: types core.o

all: main

clean:
	$(RM) $(OBJROOT)/*.o

object.o: type/object.c type/object.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

boolean.o: type/boolean.c type/boolean.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

character.o: type/character.c type/character.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

fixnum.o: type/fixnum.c type/fixnum.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

symbol.o: type/symbol.c type/symbol.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

pair.o: type/pair.c type/pair.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

string.o: type/string.c type/string.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

vector.o: type/vector.c type/vector.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

port.o: type/port.c type/port.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

builtin.o: type/builtin.c type/builtin.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

closure.o: type/closure.c type/closure.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)


core.o: core.h core.c
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)
