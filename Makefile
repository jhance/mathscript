CC=gcc -Wall -Werror -g

OBJECTS =
OBJECTS += lex.yy.o
OBJECTS += parser.tab.o
OBJECTS += new.o
OBJECTS += exec.o
OBJECTS += xmalloc.o
OBJECTS += symtable.o

mathscript: $(OBJECTS)
	@echo "   CCLD  mathscript"
	@$(CC) $(OBJECTS) -lfl -o mathscript

new.o: mathscript.h xmalloc.h
exec.o: mathscript.h xmalloc.h symtable.h
symtable.o: xmalloc.h

parser.tab.o: mathscript.h


#### RULES ####
%.o : %.c
	@echo "   CC    $@"
	@$(CC) -c $< -o $@

%.tab.c %.tab.h: %.y
	@echo "   BISON $*.tab.c $*.tab.h"
	@bison -vd parser.y

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
