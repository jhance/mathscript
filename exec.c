#include "exec.h"
#include "statement.h"
#include "symtable.h"
#include "xmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct symtable* table;

void exec_prepare() {
    table = symtable_init();
}

void exec_statements(struct statement_list* list) {
    struct statement_node* cur = list->start;
    while(cur != NULL) {
        exec_statement(cur);
        cur = cur->next;
    }
}

int exec_statement(struct statement_node* s) {
    switch(s->type) {
        case TYPE_START:
        case TYPE_END:
            return 0;
        case TYPE_CALL_FUNCTION:
            return exec_call_function(s->data.call_function);
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
        case TYPE_COMPARE_G:
            return exec_compare_g(s->data.compare_g);
        case TYPE_COMPARE_GE:
            return exec_compare_ge(s->data.compare_ge);
        case TYPE_COMPARE_L:
            return exec_compare_l(s->data.compare_l);
        case TYPE_COMPARE_LE:
            return exec_compare_le(s->data.compare_le);
        case TYPE_COMPARE_E:
            return exec_compare_e(s->data.compare_e);
        case TYPE_COMPARE_NE:
            return exec_compare_ne(s->data.compare_ne);
        case TYPE_IF_STATEMENT:
            return exec_if_statement(s->data.if_statement);
        case TYPE_WHILE_LOOP:
            return exec_while_loop(s->data.while_loop);
        case TYPE_FOR_LOOP:
            return exec_for_loop(s->data.for_loop);
    }

    fprintf(stderr, "Error: Invalid statement\n");

    return 0;
}

int exec_call_function(struct call_function* call_function) {
    if(strcmp(call_function->identifier, "print") == 0) {
        /* By "args" its really something like &(args[0]) */
        printf("%d\n", exec_statement(call_function->args));
    }
    else {
        fprintf(stderr, 
                "Error: No such function: %s\n", call_function->identifier);
    }
    return 0;
}

int exec_set_variable(struct set_variable* set_variable) {
    int* val = xmalloc(sizeof(int));
    *val = exec_statement(set_variable->expr);
    symtable_set(table, set_variable->identifier, val);
    return 0;
}

int exec_get_variable(struct get_variable* get_variable) {
    return *(int*) symtable_get(table, get_variable->identifier);
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

int exec_compare_g(struct compare_g* compare_g) {
    int val_left = exec_statement(compare_g->expr_left);
    int val_right = exec_statement(compare_g->expr_right);

    return val_left > val_right;
}

int exec_compare_ge(struct compare_ge* compare_ge) {
    int val_left = exec_statement(compare_ge->expr_left);
    int val_right = exec_statement(compare_ge->expr_right);

    return val_left >= val_right;
}

int exec_compare_l(struct compare_l* compare_l) {
    int val_left = exec_statement(compare_l->expr_left);
    int val_right = exec_statement(compare_l->expr_right);

    return val_left < val_right;
}

int exec_compare_le(struct compare_le* compare_le) {
    int val_left = exec_statement(compare_le->expr_left);
    int val_right = exec_statement(compare_le->expr_right);

    return val_left <= val_right;
}

int exec_compare_e(struct compare_e* compare_e) {
    int val_left = exec_statement(compare_e->expr_left);
    int val_right = exec_statement(compare_e->expr_right);

    return val_left == val_right;
}

int exec_compare_ne(struct compare_ne* compare_ne) {
    int val_left = exec_statement(compare_ne->expr_left);
    int val_right = exec_statement(compare_ne->expr_right);

    return val_left != val_right;
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

int exec_while_loop(struct while_loop* while_loop) {
    while(exec_statement(while_loop->expr)) {
        exec_statements(while_loop->statements);
    }
    return 0;
}

int exec_for_loop(struct for_loop* for_loop) {
    exec_statement(for_loop->initial_statement);
    while(exec_statement(for_loop->expr)) {
        exec_statements(for_loop->statements);
        exec_statement(for_loop->iterator_statement);
    }
    return 0;
}
