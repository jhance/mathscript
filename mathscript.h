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
    TYPE_COMPARE_G,
    TYPE_COMPARE_GE,
    TYPE_COMPARE_L,
    TYPE_COMPARE_LE,
    TYPE_COMPARE_E,
    TYPE_COMPARE_NE,
    TYPE_IF_STATEMENT,
    TYPE_WHILE_LOOP,
    TYPE_FOR_LOOP
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

struct compare_g {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

struct compare_ge {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

struct compare_l {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

struct compare_le {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

struct compare_e {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

struct compare_ne {
    struct statement_node* expr_left;
    struct statement_node* expr_right;
};

struct if_statement {
    struct statement_node* expr;
    struct statement_list* statements;
};

struct while_loop {
    struct statement_node* expr;
    struct statement_list* statements;
};

struct for_loop {
    struct statement_node* initial_statement;
    struct statement_node* expr;
    struct statement_node* iterator_statement;
    struct statement_list* statements;
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
    struct compare_g* compare_g;
    struct compare_ge* compare_ge;
    struct compare_l* compare_l;
    struct compare_le* compare_le;
    struct compare_e* compare_e;
    struct compare_ne* compare_ne;
    struct if_statement* if_statement;
    struct while_loop* while_loop;
    struct for_loop* for_loop;
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
void exec_statements(struct statement_list* list);


/* Called from parser to create new statement nodes in the list */
struct statement_node* statement_node_init();
struct statement_list* statement_list_init();


/* Declares helpers for creating nodes based on the structs
 * See also: DEFINE_NEW_FUNC in new.c
 *
 * Example: 
 * struct statement_node* new_get_value(struct get_value* get_value);
 */
#define DECLARE_NEW_FUNC(s) struct statement_node* new_##s(struct s* s);

/* please use semicolons on the macros */
DECLARE_NEW_FUNC(function_call);
DECLARE_NEW_FUNC(set_variable);
DECLARE_NEW_FUNC(get_variable);
DECLARE_NEW_FUNC(get_value);
DECLARE_NEW_FUNC(add);
DECLARE_NEW_FUNC(subtract);
DECLARE_NEW_FUNC(multiply);
DECLARE_NEW_FUNC(parens);
DECLARE_NEW_FUNC(compare_g);
DECLARE_NEW_FUNC(compare_ge);
DECLARE_NEW_FUNC(compare_l);
DECLARE_NEW_FUNC(compare_le);
DECLARE_NEW_FUNC(compare_e);
DECLARE_NEW_FUNC(compare_ne);
DECLARE_NEW_FUNC(if_statement);
DECLARE_NEW_FUNC(while_loop);
DECLARE_NEW_FUNC(for_loop);

/* Called from the executer to actually execute a statement node
 *
 * Example:
 * int exec_get_value(struct get_value* get_value);
 */
#define DECLARE_EXEC_FUNC(s) int exec_##s(struct s* s);

/* please use semicolons after the macros */
DECLARE_EXEC_FUNC(function_call);
DECLARE_EXEC_FUNC(set_variable);
DECLARE_EXEC_FUNC(get_variable);
DECLARE_EXEC_FUNC(get_value);
DECLARE_EXEC_FUNC(add);
DECLARE_EXEC_FUNC(subtract);
DECLARE_EXEC_FUNC(multiply);
DECLARE_EXEC_FUNC(parens);
DECLARE_EXEC_FUNC(compare_g);
DECLARE_EXEC_FUNC(compare_ge);
DECLARE_EXEC_FUNC(compare_l);
DECLARE_EXEC_FUNC(compare_le);
DECLARE_EXEC_FUNC(compare_e);
DECLARE_EXEC_FUNC(compare_ne);
DECLARE_EXEC_FUNC(if_statement);
DECLARE_EXEC_FUNC(while_loop);
DECLARE_EXEC_FUNC(for_loop);

#endif
