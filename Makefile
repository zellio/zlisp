CC=clang
RM=rm -Rf

CFLAGS=-ggdb -x c -std=c99 -c -Wall -Wextra -Werror -pedantic-errors -ferror-limit=1

SRCROOT=src
INCROOT=include
TSTROOT=test

OBJROOT=build

VPATH=$(SRCROOT):$(INCROOT):$(TSTROOT):$(OBJROOT)

.PHONY: all clean types

types: object.o 

all: main

clean:
	$(RM) $(OBJROOT)/*.o

object.o: object.c object.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)
