%{
#include <stdio.h>
#include "mathscript.h"
#include "xmalloc.h"

struct statement_node* statement_list_start;
struct statement_node* statement_list_cur;
%}

%union {
    int int_val;
    char char_val;
    struct statement_node* statement_val;
}

%token <char_val> T_VARIABLE_IDENTIFIER
%token <char_val> T_FUNCTION_IDENTIFIER
%token <int_val> T_INTEGER
%token T_PRINT

%left '+' '-'
%left '*'

%type <statement_val> expression

%start commands

%%

commands: /* empty */
    | commands command ';'
    ;

command:
    print
    |
    set_variable
    ;

expression:
    T_INTEGER {
        struct get_value* g = xmalloc(sizeof(struct get_value));
        g->val = $1;
        
        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_GET_VALUE;
        expr->data.get_value = g;

        $<statement_val>$ = expr;
    }
    |
    T_VARIABLE_IDENTIFIER {
        struct get_variable* g = xmalloc(sizeof(struct get_variable));
        g->identifier = $1;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_GET_VARIABLE;
        expr->data.get_variable = g;

        $<statement_val>$ = expr;
    }
    |
    expression '+' expression {
        struct add* a  = xmalloc(sizeof(struct add));
        a->expr_left = $1;
        a->expr_right = $3;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_ADD;
        expr->data.add = a;

        $<statement_val>$ = expr;
    }
    |
    expression '-' expression {
        struct subtract* s = xmalloc(sizeof(struct subtract));
        s->expr_left = $1;
        s->expr_right = $3;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_SUBTRACT;
        expr->data.subtract = s;

        $<statement_val>$ = expr;
    }
    |
    expression '*' expression {
        struct multiply* m = xmalloc(sizeof(struct multiply));
        m->expr_left = $1;
        m->expr_right = $3;

        struct statement_node* expr = statement_node_init();
        expr->type = TYPE_MULTIPLY;
        expr->data.multiply = m;

        $<statement_val>$ = expr;
    }
    ;

set_variable:
    T_VARIABLE_IDENTIFIER '=' expression
    {
        struct set_variable* s = xmalloc(sizeof(struct set_variable));
        s->identifier = $1;
        s->expr = $3;

        new_set_variable(statement_list_cur, s);
        
        statement_list_cur = statement_list_cur->next;
    }
    ;

print:
    T_PRINT '[' expression ']'
    {
        struct function_call* call = xmalloc(sizeof(struct function_call));
        call->identifier = "print";
        call->args = xmalloc(sizeof(struct statement_node));
        call->args[0] = *$3;
        new_function_call(statement_list_cur, call);

        statement_list_cur = statement_list_cur->next;
    }
    ;
%%

yyerror(const char* str) {
    fprintf(stderr, "Error: %s\n", str);
}

int main() {
    statement_list_start = statement_node_init();
    statement_list_start->type = TYPE_ROOT;
    statement_list_cur = statement_list_start;
    yyparse();
    exec_statements(statement_list_start);
    return 0;
}
