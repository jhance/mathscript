%{
#include <stdio.h>
#include <stdlib.h>
#include "mathscript.h"
#include "xmalloc.h"

struct statement_list* statement_list;
%}

%union {
    int int_val;
    char char_val;
    struct statement_node* statement_node_val;
    struct statement_list* statement_list_val;
}

%token <char_val> T_VARIABLE_IDENTIFIER
%token <char_val> T_FUNCTION_IDENTIFIER
%token <int_val> T_INTEGER
%token T_PRINT
%token T_IF
%token T_WHILE
%token T_FOR

%left T_COMPARE_G T_COMPARE_GE T_COMPARE_L T_COMPARE_LE T_COMPARE_E
      T_COMPARE_NE
%left '+' '-'
%left '*'

%type <statement_node_val> expression
%type <statement_node_val> comparison
%type <statement_node_val> statement
%type <statement_node_val> block
%type <statement_list_val> statements

%%

main:
    statements {
        statement_list = $1
    }

statements: 
    /* empty */ {
        $$ = statement_list_init();
    }
    | statements statement ';' {
        $1->end->next = $2;
        $1->end = $2;
        $$ = $1;
    }
    | statements block {
        $1->end->next = $2;
        $1->end = $2;
        $$ = $1;
    }
    ;

statement:
    T_PRINT '[' expression ']' {
        struct function_call* call = xmalloc(sizeof(struct function_call));
        call->identifier = "print";
        call->args = xmalloc(sizeof(struct statement_node));
        call->args[0] = *$3;

        $$ = new_function_call(call);
    }
    |
    T_VARIABLE_IDENTIFIER '=' expression {
        struct set_variable* s = xmalloc(sizeof(struct set_variable));
        s->identifier = $1;
        s->expr = $3;

        $$ = new_set_variable(s);
    }
    ;

block:
    T_IF '[' expression ']' '{' statements '}' {
        struct if_statement* i = xmalloc(sizeof(struct if_statement));
        i->expr = $3;
        i->statements = $6;

        $$ = new_if_statement(i);
    }
    |
    T_WHILE '[' expression ']' '{' statements '}' {
        struct while_loop* w = xmalloc(sizeof(struct while_loop));
        w->expr = $3;
        w->statements = $6;

        $$ = new_while_loop(w);
    }
    |
    T_FOR '[' statement ';' expression ';' statement ']' '{' statements '}' {
        struct for_loop* f = xmalloc(sizeof(struct for_loop));
        f->initial_statement = $3;
        f->expr = $5;
        f->iterator_statement = $7;
        f->statements = $10;

        $$ = new_for_loop(f);
    }
    ;

expression:
    T_INTEGER {
        struct get_value* g = xmalloc(sizeof(struct get_value));
        g->val = $1;
        
        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_GET_VALUE;
        expr->data.get_value = g;

        $$ = expr;
    }
    |
    T_VARIABLE_IDENTIFIER {
        struct get_variable* g = xmalloc(sizeof(struct get_variable));
        g->identifier = $1;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_GET_VARIABLE;
        expr->data.get_variable = g;

        $$ = expr;
    }
    |
    expression '+' expression {
        struct add* a  = xmalloc(sizeof(struct add));
        a->expr_left = $1;
        a->expr_right = $3;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_ADD;
        expr->data.add = a;

        $$ = expr;
    }
    |
    expression '-' expression {
        struct subtract* s = xmalloc(sizeof(struct subtract));
        s->expr_left = $1;
        s->expr_right = $3;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_SUBTRACT;
        expr->data.subtract = s;

        $$ = expr;
    }
    |
    expression '*' expression {
        struct multiply* m = xmalloc(sizeof(struct multiply));
        m->expr_left = $1;
        m->expr_right = $3;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_MULTIPLY;
        expr->data.multiply = m;

        $$ = expr;
    }
    |
    comparison
    |
    '(' expression ')' {
        struct parens* p = xmalloc(sizeof(struct parens));
        p->expr = $2;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_PARENS;
        expr->data.parens = p;

        $$ = expr;
    }
    ;

comparison:
    expression T_COMPARE_G expression {
        struct compare_g* c = xmalloc(sizeof(struct compare_g));
        c->expr_left = $1;
        c->expr_right = $3;

        $$ = new_compare_g(c);
    }
    |
    expression T_COMPARE_GE expression {
        struct compare_ge* c = xmalloc(sizeof(struct compare_ge));
        c->expr_left = $1;
        c->expr_right = $3;

        $$ = new_compare_ge(c);
    }
    |
    expression T_COMPARE_L expression {
        struct compare_l* c = xmalloc(sizeof(struct compare_l));
        c->expr_left = $1;
        c->expr_right = $3;

        $$ = new_compare_l(c);
    }
    |
    expression T_COMPARE_LE expression {
        struct compare_le* c = xmalloc(sizeof(struct compare_le));
        c->expr_left = $1;
        c->expr_right = $3;

        $$ = new_compare_le(c);
    }
    |
    expression T_COMPARE_E expression {
        struct compare_e* c = xmalloc(sizeof(struct compare_e));
        c->expr_left = $1;
        c->expr_right = $3;

        $$ = new_compare_e(c);
    }
    |
    expression T_COMPARE_NE expression {
        struct compare_ne* c = xmalloc(sizeof(struct compare_ne));
        c->expr_left = $1;
        c->expr_right = $3;

        $$ = new_compare_ne(c);
    }
    ;

%%

yyerror(const char* str) {
    fprintf(stderr, "Error: %s\n", str);
    exit(1);
}

int main() {
    yyparse();
    exec_prepare();
    exec_statements(statement_list);
    return 0;
}
