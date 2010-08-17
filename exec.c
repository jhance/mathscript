#include "mathscript.h"
#include "symtable.h"
#include "xmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static symtable table;

void exec_statements(struct statement_node* list) {
    table = symtable_init();

    struct statement_node* cur = list;
    while(cur != NULL) {
        exec_statement(cur);
        cur = cur->next;
    }
}

int exec_statement(struct statement_node* s) {
    switch(s->type) {
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
    }

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
