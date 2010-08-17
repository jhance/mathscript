#include "mathscript.h"
#include "xmalloc.h"
#include <stdlib.h>

struct statement_node* statement_node_init() {
    return xmalloc(sizeof(struct statement_node));
}

struct statement_list* statement_list_init() {
    struct statement_list* l = xmalloc(sizeof(struct statement_list));
    struct statement_node* s = xmalloc(sizeof(struct statement_node));
    s->type = TYPE_ROOT;
    l->start = s;
    l->end = s;

    return l;
}

struct statement_node* new_function_call(struct function_call* function_call) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_FUNCTION_CALL;
    new->data.function_call = function_call;

    return new;
}

struct statement_node* new_set_variable(struct set_variable* set_variable) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_SET_VARIABLE;
    new->data.set_variable = set_variable;

    return new;
}

struct statement_node* new_get_variable(struct get_variable* get_variable) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_GET_VARIABLE;
    new->data.get_variable = get_variable;

    return new;
}

struct statement_node* new_get_value(struct get_value* get_value) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_GET_VALUE;
    new->data.get_value = get_value;

    return new;
}

struct statement_node* new_add(struct add* add) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_ADD;
    new->data.add = add;

    return new;
}

struct statement_node* new_subtract(struct subtract* subtract) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_SUBTRACT;
    new->data.subtract = subtract;

    return new;
}

struct statement_node* new_multiply(struct multiply* multiply) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_MULTIPLY;
    new->data.multiply = multiply;

    return new;
}

struct statement_node* new_parens(struct parens* parens) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_PARENS;
    new->data.parens = parens;

    return new;
}

struct statement_node* new_compare_g(struct compare_g* compare_g) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_COMPARE_G;
    new->data.compare_g = compare_g;
    
    return new;
}

struct statement_node* new_compare_ge(struct compare_ge* compare_ge) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_COMPARE_GE;
    new->data.compare_ge = compare_ge;
    
    return new;
}

struct statement_node* new_compare_l(struct compare_l* compare_l) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_COMPARE_L;
    new->data.compare_l = compare_l;
    
    return new;
}

struct statement_node* new_compare_le(struct compare_le* compare_le) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_COMPARE_LE;
    new->data.compare_le = compare_le;
    
    return new;
}

struct statement_node* new_compare_e(struct compare_e* compare_e) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_COMPARE_E;
    new->data.compare_e = compare_e;
    
    return new;
}

struct statement_node* new_compare_ne(struct compare_ne* compare_ne) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_COMPARE_NE;
    new->data.compare_ne = compare_ne;
    
    return new;
}

struct statement_node* new_if_statement(struct if_statement* if_statement) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_IF_STATEMENT;
    new->data.if_statement = if_statement;

    return new;
}

struct statement_node* new_while_loop(struct while_loop* while_loop) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_WHILE_LOOP;
    new->data.while_loop = while_loop;

    return new;
}
