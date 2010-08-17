#ifndef MATHSCRIPT_H
#define MATHSCRIPT_H

#define TYPE_ROOT           0
#define TYPE_FUNCTION_CALL  1
#define TYPE_SET_VARIABLE   2
#define TYPE_GET_VARIABLE   3
#define TYPE_GET_VALUE      4
#define TYPE_ADD            5
#define TYPE_SUBTRACT       6
#define TYPE_MULTIPLY       7

struct function_call {
    char* identifier;
    struct statement_node* args;
};

struct set_variable {
    char identifier;
    struct statement_node* expr;
};

struct get_variable {
    char identifier;
};

struct get_value {
    int val;
};

struct add {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

struct subtract {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

struct multiply {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

union statement_info {
    struct function_call* function_call;
    struct set_variable* set_variable;
    struct get_variable* get_variable;
    struct get_value* get_value;
    struct add* add;
    struct subtract* subtract;
    struct multiply* multiply;
};

struct statement_node {
    struct statement_node* next;
    
    int type;

    union statement_info data;
};

/* Called from parser after it finishes parsing to execute everything
 * Can also be used to execute inner statements/expressions
 */
int exec_statement(struct statement_node* s);
void exec_statements(struct statement_node* list);

/* Called from parser to create new statement nodes in the list */
struct statement_node* statement_node_init();
void new_function_call(struct statement_node* list, 
                       struct function_call* function_call);
void new_set_variable(struct statement_node* list,
                      struct set_variable* set_variable);
void new_get_variable(struct statement_node* list,
                      struct get_variable* get_variable);
void new_get_value(struct statement_node* list,
                   struct get_value* get_value);
void new_add(struct statement_node* list,
             struct add* add);
void new_subtract(struct statement_node* list,
                  struct subtract* subtract);
void new_multiply(struct statement_node* list,
                  struct multiply* multiply);

/* Called from the executer to actually execute a statement node */
int exec_function_call(struct function_call* function_call);
int exec_set_variable(struct set_variable* set_variable);
int exec_get_variable(struct get_variable* get_variable);
int exec_get_value(struct get_value* get_value); 
int exec_add(struct add* add);
int exec_subtract(struct subtract* subtract);
int exec_multiply(struct multiply* multiply);

#endif
