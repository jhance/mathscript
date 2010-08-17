#include "mathscript.h"
#include "symtable.h"
#include "xmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static symtable table;

void exec_prepare() {
    table = symtable_init();
}

void exec_statements(struct statement_node* list) {
    struct statement_node* cur = list;
    while(cur != NULL) {
        exec_statement(cur);
        cur = cur->next;
    }
}

int exec_statement(struct statement_node* s) {
    switch(s->type) {
        case TYPE_ROOT:
            return 0;
        case TYPE_FUNCTION_CALL:
            return exec_function_call(s->data.function_call);
        case TYPE_SET_VARIABLE:
            return exec_set_variable(s->data.set_variable);
        case TYPE_GET_VARIABLE:
            return exec_get_variable(s->data.get_variable);
        case TYPE_GET_VALUE:
            return exec_get_value(s->data.get_value);
        case TYPE_ADD:
            return exec_add(s->data.add);
        case TYPE_SUBTRACT:
            return exec_subtract(s->data.subtract);
        case TYPE_MULTIPLY:
            return exec_multiply(s->data.multiply);
        case TYPE_PARENS:
            return exec_parens(s->data.parens);
        case TYPE_IF_STATEMENT:
            return exec_if_statement(s->data.if_statement);
    }

    fprintf(stderr, "Error: Invalid statement\n");

    return 0;
}

int exec_function_call(struct function_call* function_call) {
    if(strcmp(function_call->identifier, "print") == 0) {
        /* By "args" its really something like &(args[0]) */
        printf("%d\n", exec_statement(function_call->args));
    }
    else {
        fprintf(stderr, 
                "Error: No such function: %s\n", function_call->identifier);
    }
    return 0;
}

int exec_set_variable(struct set_variable* set_variable) {
    int* val = xmalloc(sizeof(int));
    *val = exec_statement(set_variable->expr);
    table[symtable_calc_index(set_variable->identifier)] = val;
    return 0;
}

int exec_get_variable(struct get_variable* get_variable) {
    return *(int*) table[symtable_calc_index(get_variable->identifier)];
}

int exec_get_value(struct get_value* get_value) {
    return get_value->val;
}

int exec_add(struct add* add) {
    int val_left = exec_statement(add->expr_left);
    int val_right = exec_statement(add->expr_right);

    return val_left + val_right;
}

int exec_subtract(struct subtract* subtract) {
    int val_left = exec_statement(subtract->expr_left);
    int val_right = exec_statement(subtract->expr_right);

    return val_left - val_right;
}

int exec_multiply(struct multiply* multiply) {
    int val_left = exec_statement(multiply->expr_left);
    int val_right = exec_statement(multiply->expr_right);

    return val_left * val_right;
}

int exec_parens(struct parens* parens) {
    return exec_statement(parens->expr);
}

int exec_if_statement(struct if_statement* if_statement) {
    if(exec_statement(if_statement->expr)) {
        exec_statements(if_statement->statements);
        return 1;
    }
    else {
        return 0;
    }
}
