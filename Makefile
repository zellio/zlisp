APP=zeme

CC=clang
RM=rm

CFLAGS=-ggdb -x c --std=c99 -c -Wall -Wextra -pedantic -ferror-limit=1
LDFLAGS=-lm

SRCEXT=c
SRCDIR=lib
INCDIR=include
OBJDIR=obj
BINDIR=bin

SRCS    := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS := $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)

OBJS    := $(patsubst $(SRCDIR)%.$(SRCEXT),$(OBJDIR)%.o,$(SRCS))
OBJDIRS := $(subst $(SRCDIR),$(OBJDIR),$(SRCDIRS))

.PHONY: all buildrepo clean distclean

all: $(BINDIR)/$(APP)

$(BINDIR)/$(APP): buildrepo $(OBJS)
	@mkdir -p `dirname $(@)`
	@echo "Linking $(@) ... "
	@$(CC) $(OBJS) $(LDFLAGS) -o $(@)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling $(<) ... "
	@$(CC) $(CFLAGS) -I$(INCDIR) $(<) -o $(@)

buildrepo:
	@$(call make-repo)

define make-repo
	for dir in $(OBJDIRS); \
	do \
		mkdir -p $$dir; \
	done
endef

clean:
	$(RM) -fr $(OBJDIR)

distclean: clean
	$(RM) -fr $(BINDIR)
