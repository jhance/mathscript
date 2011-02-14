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

mathscript: $(OBJECTS)
	@echo "   CCLD  mathscript"
	@$(CC) $^ -lfl -o mathscript

statement.o: xmalloc.h
new.o: statement.h xmalloc.h
exec.o: statement.h xmalloc.h symtable.h
read.o: statement.h new.h xmalloc.h
write.o: statement.h
symtable.o: xmalloc.h

parser.tab.o: statement.h new.h exec.h read.h write.h mode.h


#### RULES ####
%.o : %.c %.h
	@echo "   CC    $@"
	@$(CC) -c $< -o $@

%.tab.c %.tab.h: %.y
	@echo "   BISON $*.tab.c $*.tab.h"
	@bison -vtd parser.y

parser.tab.o: parser.tab.c
	@echo "   CC    parser.tab.o"
	@gcc $(CFLAGS) -c parser.tab.c -o parser.tab.o

lex.yy.c: lexer.l
	@echo "   FLEX  lex.yy.c"
	@flex lexer.l

lex.yy.o: lex.yy.c parser.tab.h
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
