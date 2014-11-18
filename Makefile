APP=zlisp

CC=clang
RM=rm

LEX=flex
YACC=bison
YFLAGS=

CFLAGS=-ggdb -x c --std=c99 -D_POSIX_C_SOURCE=200809L -c -Wall -Wextra -pedantic -ferror-limit=1
LDFLAGS=-lm

SRCEXT=c
SRCDIR=lib
INCDIR=include
OBJDIR=obj
BINDIR=bin

LEX_SRCS := $(shell find $(SRCDIR) -name '*.l')
LEX_OBJS := $(patsubst %.l,%.c,${LEX_SRCS}) $(patsubst %.l,%.h,${LEX_SRCS})

YACC_SRCS := $(shell find $(SRCDIR) -name '*.y')
YACC_OBJS := $(patsubst %.y,%.c,${YACC_SRCS}) $(patsubst %.y,%.h,${YACC_SRCS})

SRCS    := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS := $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)

OBJS    := $(patsubst $(SRCDIR)%.l,$(OBJDIR)%.o,$(LEX_SRCS))\
	$(patsubst $(SRCDIR)%.l,$(OBJDIR)%.o,$(LEX_SRCS))\
	$(patsubst $(SRCDIR)%.y,$(OBJDIR)%.o,$(YACC_SRCS))

OBJDIRS := $(subst $(SRCDIR),$(OBJDIR),$(SRCDIRS))

.PHONY: all buildrepo clean distclean

all: $(BINDIR)/$(APP)

$(BINDIR)/$(APP): buildrepo $(LEX_OBJS) $(YACC_OBJS) $(OBJS)
	@mkdir -p `dirname $(@)`
	@echo "Linking $(@) ... "
	@$(CC) $(OBJS) $(LDFLAGS) -o $(@)

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
	$(RM) -fr $(OBJDIR) $(LEX_OBJS) $(YACC_OBJS)

distclean: clean
	$(RM) -fr $(BINDIR)
