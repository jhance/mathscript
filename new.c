#include "mathscript.h"
#include "xmalloc.h"
#include <stdlib.h>

struct statement_node* statement_node_init() {
    return xmalloc(sizeof(struct statement_node));
}

void new_function_call(struct statement_node* list,
                       struct function_call* function_call) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_FUNCTION_CALL;
    new->data.function_call = function_call;

    list->next = new;
}

void new_set_variable(struct statement_node* list,
                      struct set_variable* set_variable) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_SET_VARIABLE;
    new->data.set_variable = set_variable;

    list->next = new;
}

void new_get_variable(struct statement_node* list,
                      struct get_variable* get_variable) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_GET_VARIABLE;
    new->data.get_variable = get_variable;

    list->next = new;
}

void new_get_value(struct statement_node* list,
                   struct get_value* get_value) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_GET_VALUE;
    new->data.get_value = get_value;

    list->next = new;
}

void new_add(struct statement_node* list,
             struct add* add) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_ADD;
    new->data.add = add;

    list->next = new;
}

void new_subtract(struct statement_node* list,
                  struct subtract* subtract) {
    struct statement_node* new = statement_node_init();
    new->type = TYPE_SUBTRACT;
    new->data.subtract = subtract;

    list->next = new;
}
