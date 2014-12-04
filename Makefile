APP=zlisp

CC=clang
CFLAGS=-ggdb -x c --std=c11 -D_POSIX_C_SOURCE=200809L -c -Wall -Wextra -pedantic -ferror-limit=1
LDFLAGS=-lm

LEX=flex
YACC=bison
YFLAGS=

RM=rm

SRCEXT=c
SRCDIR=lib

INCEXT=h
INCDIR=include

LEXEXT=l

YACCEXT=y

OBJDIR=obj
BINDIR=bin

LEX_SRCS := $(shell find $(SRCDIR) -name '*.$(LEXEXT)')
LEX_OBJS := $(patsubst %.$(LEXEXT),%.$(SRCEXT),$(LEX_SRCS))\
  $(patsubst $(SRCDIR)%.$(LEXEXT),$(INCDIR)%.$(INCEXT),$(LEX_SRCS))

YACC_SRCS := $(shell find $(SRCDIR) -name '*.$(YACCEXT)')
YACC_OBJS := $(patsubst %.$(YACCEXT),%.$(SRCEXT),$(YACC_SRCS))\
  $(patsubst $(SRCDIR)%.$(YACCEXT),$(INCDIR)%.$(INCEXT),$(YACC_SRCS))

SRCS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS := $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)

OBJS := $(patsubst $(SRCDIR)%.l,$(OBJDIR)%.o,$(LEX_SRCS))\
	$(patsubst $(SRCDIR)%.y,$(OBJDIR)%.o,$(YACC_SRCS))\
	$(patsubst $(SRCDIR)%.$(SRCEXT),$(OBJDIR)%.o,$(SRCS))

OBJDIRS := $(subst $(SRCDIR),$(OBJDIR),$(SRCDIRS))

.PHONY: all buildrepo clean distclean

all: $(BINDIR)/$(APP)

$(BINDIR)/$(APP): buildrepo $(LEX_OBJS) $(YACC_OBJS) $(OBJS)
	@mkdir -p `dirname $(@)`
	@echo "Linking $(@) ... "
	@$(CC) $(shell find $(OBJDIR) -iname '*.o') $(LDFLAGS) -o $(@)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling $(<) ... "
	@$(CC) $(CFLAGS) -I$(INCDIR) $(<) -o $(@)

$(SRCDIR)/%.h $(SRCDIR)/%.c: $(SRCDIR)/%.l
	@echo "Generating $(<) ... "
	@$(LEX) --header-file=$(INCDIR)/$(*).h -o $(@) $(<)

$(SRCDIR)/%.h $(SRCDIR)/%.c: $(SRCDIR)/%.y
	@echo "Generating $(<) ... "
	@$(YACC) $(YFLAGS) --defines=$(INCDIR)/$(*).h -o $(@) $(^)

buildrepo:
	@$(call make-repo)

define make-repo
	for dir in $(OBJDIRS); \
	do \
		mkdir -p $$dir; \
	done
endef

clean:
	$(RM) -rf $(OBJDIR) $(LEX_OBJS) $(YACC_OBJS)

distclean: clean
	$(RM) -rf $(BINDIR)
