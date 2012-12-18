
CC = gcc
RM = rm -Rf

CFLAGS = -ggdb -x c -std=c99 -c -Wall -Wextra -Werror -pedantic-errors -Wdouble-promotion -Wformat=2 -Winit-self -Wmissing-include-dirs -Wparentheses -Wswitch-default -Wswitch-enum -Wsync-nand -Wuninitialized -Wunknown-pragmas -Wstrict-overflow=2 -Wfloat-equal -Wundef -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wconversion -Wlogical-op -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-format-attribute -Wpacked -Wpacked-bitfield-compat -Wdouble-promotion -Wformat=2 -Winit-self -Wmissing-include-dirs -Wparentheses -Wswitch-default -Wswitch-enum -Wsync-nand -Wuninitialized -Wunknown-pragmas -Wstrict-overflow=2 -Wfloat-equal -Wundef -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wconversion -Wlogical-op -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmissing-format-attribute -Wpacked -Wpacked-bitfield-compat -Wredundant-decls -Wnested-externs -Winline -Woverlength-strings -Wcomments -Wundef -Wunused-macros -Wendif-labels
LDFLAGS =

SRCROOT = src/core
INCROOT = src/include
TSTROOT = src/test

OBJROOT = build

VPATH=$(SRCROOT):$(INCROOT):$(TSTROOT):$(OBJROOT)

.PHONY: all

all: types functions


top.o: lang/types/top.c lang/types/top.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

atom.o: lang/types/atom.c lang/types/atom.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

cons.o: lang/types/cons.c lang/types/cons.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

boolean.o: lang/types/boolean.c lang/types/boolean.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

types: top.o atom.o cons.o boolean.o


elementary.o: lang/functions/elementary.c lang/functions/elementary.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

auxiliary.o: lang/functions/auxiliary.c lang/functions/auxiliary.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

evalquote.o: lang/functions/evalquote.c lang/functions/evalquote.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

functions: elementary.o auxiliary.o evalquote.o


parser.o: repl/parser.c repl/parser.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

io.o: repl/io.c repl/io.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)

repl.o: repl.c repl.h
	$(CC) $(CFLAGS) -I$(INCROOT) -o $(OBJROOT)/$(@) $(<)


repl: top.o atom.o cons.o boolean.o elementary.o auxiliary.o evalquote.o parser.o io.o repl.o
	$(CC) -o $(@) $(OBJROOT)/top.o $(OBJROOT)/atom.o $(OBJROOT)/cons.o $(OBJROOT)/boolean.o $(OBJROOT)/elementary.o $(OBJROOT)/auxiliary.o $(OBJROOT)/evalquote.o $(OBJROOT)/parser.o $(OBJROOT)/io.o $(OBJROOT)/repl.o

.PHONY: clean

clean:
	$(RM) $(OBJROOT)/*.o

.PHONY: rebuild

rebuild: clean all
