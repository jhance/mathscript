#ifndef MATHSCRIPT_H
#define MATHSCRIPT_H

enum statement_type {
    TYPE_ROOT,
    TYPE_FUNCTION_CALL,
    TYPE_SET_VARIABLE,
    TYPE_GET_VARIABLE,
    TYPE_GET_VALUE,
    TYPE_ADD,
    TYPE_SUBTRACT,
    TYPE_MULTIPLY,
    TYPE_PARENS,
    TYPE_IF_STATEMENT
};

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

struct parens {
    struct statement_node* expr;
};

struct if_statement {
    struct statement_node* expr;
    struct statement_node* statements;
};

union statement_info {
    struct function_call* function_call;
    struct set_variable* set_variable;
    struct get_variable* get_variable;
    struct get_value* get_value;
    struct add* add;
    struct subtract* subtract;
    struct multiply* multiply;
    struct parens* parens;
    struct if_statement* if_statement;
};

struct statement_node {
    struct statement_node* next;
    
    enum statement_type type;

    union statement_info data;
};

struct statement_list {
    struct statement_node* start;
    struct statement_node* end;
};

/* Called from parser after it finishes parsing to execute everything
 * Can also be used to execute inner statements/expressions
 */
void exec_prepare();
int exec_statement(struct statement_node* s);
void exec_statements(struct statement_node* list);

/* Called from parser to create new statement nodes in the list */
struct statement_node* statement_node_init();
struct statement_list* statement_list_init();
struct statement_node* new_function_call(struct function_call* function_call);
struct statement_node* new_set_variable(struct set_variable* set_variable);
struct statement_node* new_get_variable(struct get_variable* get_variable);
struct statement_node* new_get_value(struct get_value* get_value);
struct statement_node* new_add(struct add* add);
struct statement_node* new_subtract(struct subtract* subtract);
struct statement_node* new_multiply(struct multiply* multiply);
struct statement_node* new_parens(struct parens* parens);
struct statement_node* new_if_statement(struct if_statement* if_statement);

/* Called from the executer to actually execute a statement node */
int exec_function_call(struct function_call* function_call);
int exec_set_variable(struct set_variable* set_variable);
int exec_get_variable(struct get_variable* get_variable);
int exec_get_value(struct get_value* get_value); 
int exec_add(struct add* add);
int exec_subtract(struct subtract* subtract);
int exec_multiply(struct multiply* multiply);
int exec_parens(struct parens* parens);
int exec_if_statement(struct if_statement* if_statement);

#endif
