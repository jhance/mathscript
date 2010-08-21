CC=gcc -Wall -Werror -g

OBJECTS =
OBJECTS += lex.yy.o
OBJECTS += parser.tab.o
OBJECTS += statement.o
OBJECTS += new.o
OBJECTS += exec.o
OBJECTS += read.o
OBJECTS += write.o
OBJECTS += xmalloc.o
OBJECTS += symtable.o

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
	@gcc -g -c parser.tab.c -o parser.tab.o

lex.yy.c: lexer.l
	@echo "   FLEX  lex.yy.c"
	@flex lexer.l

lex.yy.o: lex.yy.c parser.tab.h
	@echo "   CC    lex.yy.o"
	@gcc -g -c lex.yy.c -o lex.yy.o


# Fake rules
clean:
	@echo "   CLEAN"
	@rm -f *.yy.*
	@rm -f *.tab.*
	@rm -f *.o
	@rm -f mathscript
	@rm -f parser.output
