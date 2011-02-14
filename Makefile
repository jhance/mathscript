-include make.conf

CORE=.MAKEFILE-VERSION

# Don't optimize if we are debugging.
ifdef DEBUG
CFLAGS=-g
else
CFLAGS=-O2
endif

CFLAGS=-g
CC=gcc -Wall -Werror $(CFLAGS)

COBJECTS += statement.o
COBJECTS += new.o
COBJECTS += exec.o
COBJECTS += read.o
COBJECTS += write.o
COBJECTS += xmalloc.o
COBJECTS += symtable.o

OBJECTS += lex.yy.o
OBJECTS += parser.tab.o
OBJECTS += $(COBJECTS)

SOURCES += $(COBJECTS:.o=.c)
SOURCES += $(COBJECTS:.o=.h)
SOURCES += lexer.l
SOURCES += parser.y
SOURCES += mode.h

DISTFILES += $(SOURCES)
DISTFILES += Makefile
DISTFILES += README

PREFIX=/usr/local

DEPS=$(OBJECTS:%.o=.d/%.d)

mathscript: $(OBJECTS) $(CORE)
	@echo "   CCLD  mathscript"
	@$(CC) $(subst $(CORE),,$^) -lfl -o mathscript

# everything depends on CORE. If it changed, rebuild!
.MAKEFILE-VERSION: Makefile make.conf
	@echo "Makefile update."
	@touch .MAKEFILE-VERSION

-include $(DEPS)

#### RULES ####
.d/%.d: %.c $(CORE)
	@ESCAPED_NAME=`echo "$@" | sed "s/\//\\\//g"`
	@$(CC) -M $< | sed "s/$*.o/$(ESCAPED_NAME)/g" > $@

%.o : %.c $(CORE)
	@echo "   CC    $@"
	@$(CC) -c $< -o $@

%.tab.c %.tab.h: %.y $(CORE)
	@echo "   BISON $*.tab.c $*.tab.h"
	@bison -vtd parser.y

parser.tab.o: parser.tab.c $(CORE)
	@echo "   CC    parser.tab.o"
	@gcc $(CFLAGS) -c parser.tab.c -o parser.tab.o

lex.yy.c: lexer.l $(CORE)
	@echo "   FLEX  lex.yy.c"
	@flex lexer.l

lex.yy.o: lex.yy.c parser.tab.h $(CORE)
	@echo "   CC    lex.yy.o"
	@gcc $(CFLAGS) -c lex.yy.c -o lex.yy.o


# Fake rules
.PHONY: clean
clean:
	@echo "   CLEAN"
	@rm -f *.yy.*
	@rm -f *.tab.*
	@rm -f *.o
	@rm -f mathscript
	@rm -f parser.output
	@rm -f .d/*.d

.PHONY: install
install:
	@echo "   INSTALL"
	@if [ ! -d $(PREFIX)/bin ] ; then mkdir $(PREFIX)/bin ; fi
	@cp mathscript $(PREFIX)/bin

.PHONY: dist
dist: dist-gz

.PHONY: dist-gz
dist-gz:
	@echo "   DIST"
	@rm -rf mathscript-0.1
	@mkdir mathscript-0.1
	@cp $(DISTFILES) mathscript-0.1
	@tar czf mathscript-0.1.tar.gz mathscript-0.1
	@rm -rf mathscript-0.1

.PHONY: dist-bz2
dist-bz2:
	@echo "   DIST"
	@rm -rf mathscript-0.1
	@mkdir mathscript-0.1
	@cp $(DISTFILES) mathscript-0.1
	@tar cjf mathscript-0.1.tar.bz2 mathscript-0.1
	@rm -rf mathscript-0.1

.PHONY: unpack-dist
unpack-dist:
	@echo "   UNPACK DIST"
	@tar xf mathscript-0.1.tar.gz
