APP=zlisp

CC=clang
LEX=flex
YACC=bison
RM=rm

CFLAGS=-ggdb -x c --std=c11 -D_POSIX_C_SOURCE=200809L -c -Wall -Wextra -pedantic -ferror-limit=1
LDFLAGS=-lm
YFLAGS=

SRC_EXT=c
INC_EXT=h
LEX_EXT=l
YACC_EXT=y

SRCDIR=lib
INCDIR=include
OBJDIR=obj
BINDIR=bin

LEX_SRCS := $(shell find $(SRCDIR) -name '*.$(LEX_EXT)')
LEX_OBJS := $(patsubst %.$(LEX_EXT),%.$(SRC_EXT),$(LEX_SRCS))\
	$(patsubst $(SRCDIR)%.$(LEX_EXT),$(INCDIR)%.$(INC_EXT),$(LEX_SRCS))

YACC_SRCS := $(shell find $(SRCDIR) -name '*.$(YACC_EXT)')
YACC_OBJS := $(patsubst %.$(YACC_EXT),%.$(SRC_EXT),$(YACC_SRCS))\
	$(patsubst $(SRCDIR)%.$(YACC_EXT),$(INCDIR)%.$(INC_EXT),$(YACC_SRCS))

SRCS := $(shell find $(SRCDIR) -name '*.$(SRC_EXT)')
SRCDIRS := $(shell find . -name '*.$(SRC_EXT)' -exec dirname {} \; | uniq)

OBJS := $(patsubst $(SRCDIR)%.l,$(OBJDIR)%.o,$(LEX_SRCS))\
	$(patsubst $(SRCDIR)%.y,$(OBJDIR)%.o,$(YACC_SRCS))\
	$(patsubst $(SRCDIR)%.$(SRC_EXT),$(OBJDIR)%.o,$(SRCS))

OBJDIRS := $(subst $(SRCDIR),$(OBJDIR),$(SRCDIRS))

.PHONY: all buildrepo clean distclean

all: $(BINDIR)/$(APP)

$(BINDIR)/$(APP): buildrepo $(LEX_OBJS) $(YACC_OBJS) $(OBJS)
	@mkdir -p `dirname $(@)`
	@echo "Linking $(@) ... "
	@$(CC) $(sort $(OBJS)) $(LDFLAGS) -o $(@)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRC_EXT)
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
