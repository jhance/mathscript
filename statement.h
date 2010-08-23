#ifndef MATHSCRIPT_H
#define MATHSCRIPT_H

enum statement_type {
    TYPE_START,
    TYPE_END,
    TYPE_CALL_FUNCTION,
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

struct call_function {
    char* identifier;
    struct statement_node* args;
};

struct set_variable {
    char* identifier;
    struct statement_node* expr;
};

struct get_variable {
    char* identifier;
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
    struct call_function* call_function;
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

    union statement_info* data;
};

struct statement_list {
    struct statement_node* start;
    struct statement_node* end;
};



/* Called from parser to create new statement nodes in the list */
struct statement_node* statement_node_init(void);
struct statement_list* statement_list_init(void);
void statement_list_end(struct statement_list* list);

#endif
