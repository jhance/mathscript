#include "read.h"
#include "statement.h"
#include "new.h"
#include "xmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

static FILE *fin;

void read_prepare(char *filename) {
    if(filename == NULL) {
        fin = stdin;
        return;
    }

    fin = fopen(filename, "r");
    if(fin == NULL) {
        fprintf(stderr, "Error: Couldn't open file\n");
        exit(1);
    }
}

void read_end(void) {
    if(fin != stdin) {
        fclose(fin);
    }
}

struct statement_list *read_statements() {
    struct statement_list *list = xmalloc(sizeof(struct statement_list));
    struct statement_node *node;

    node = read_statement();
    if(node->type != TYPE_START) {
        fprintf(stderr, "Error: File format wrong (statement list doesn't"
                        "begin with type TYPE_START");
        exit(1);
    }

    list->start = node;
    list->end = node;

    while((node = read_statement())->type != TYPE_END) {
        list->end->next = node;
        list->end = node;
    }

    return list;
}

struct statement_node *read_statement() {
    int type;
    fread(&type, sizeof(int), 1, fin);

    struct statement_node *node;

    switch(type) {
        case TYPE_START:
            node = statement_node_init();
            node->type = TYPE_START;
            return node;
        case TYPE_END:
            node = statement_node_init();
            node->type = TYPE_END;
            return node;
        case TYPE_CALL_FUNCTION:
            return new_call_function(read_call_function());
        case TYPE_SET_VARIABLE:
            return new_set_variable(read_set_variable());
        case TYPE_GET_VARIABLE:
            return new_get_variable(read_get_variable());
        case TYPE_GET_VALUE:
            return new_get_value(read_get_value());
        case TYPE_ADD:
            return new_add(read_add());
        case TYPE_SUBTRACT:
            return new_subtract(read_subtract());
        case TYPE_MULTIPLY:
            return new_multiply(read_multiply());
        case TYPE_PARENS:
            return new_parens(read_parens());
        case TYPE_COMPARE_G:
            return new_compare_g(read_compare_g());
        case TYPE_COMPARE_GE:
            return new_compare_ge(read_compare_ge());
        case TYPE_COMPARE_L:
            return new_compare_l(read_compare_l());
        case TYPE_COMPARE_LE:
            return new_compare_le(read_compare_le());
        case TYPE_COMPARE_E:
            return new_compare_e(read_compare_e());
        case TYPE_COMPARE_NE:
            return new_compare_ne(read_compare_ne());
        case TYPE_IF_STATEMENT:
            return new_if_statement(read_if_statement());
        case TYPE_WHILE_LOOP:
            return new_while_loop(read_while_loop());
        case TYPE_FOR_LOOP:
            return new_for_loop(read_for_loop());
    }

    fprintf(stderr, "Error: Invalid statement\n");
    exit(1);
}

struct call_function *read_call_function() {
    size_t size;
    fread(&size, sizeof(size_t), 1, fin);

    struct call_function *call_function = 
        xmalloc(sizeof(struct call_function));
    
    /* make sure to include room for the \0 at end of string */
    call_function->identifier = xmalloc(sizeof(char)  *(size + 1));
    fread(call_function->identifier, sizeof(char), size, fin);
    call_function->identifier[size] = '\0';

    call_function->args = read_statement();

    return call_function;
}

struct set_variable *read_set_variable() {
    size_t size;
    fread(&size, sizeof(size_t), 1, fin);

    struct set_variable *set_variable = xmalloc(sizeof(struct set_variable));

    /* make sure to include room for the \0 at end of string */
    set_variable->identifier = xmalloc(sizeof(char)  *(size + 1));
    fread(set_variable->identifier, sizeof(char), size, fin);
    set_variable->identifier[size] = '\0';

    set_variable->expr = read_statement();

    return set_variable;
}

struct get_variable *read_get_variable() {
    size_t size;
    fread(&size, sizeof(size_t), 1, fin);

    struct get_variable *get_variable = xmalloc(sizeof(struct get_variable));

    /* make sure to include room for the \0 at end of string */
    get_variable->identifier = xmalloc(sizeof(char)  *(size + 1));
    fread(get_variable->identifier, sizeof(char), size, fin);
    get_variable->identifier[size] = '\0';

    return get_variable;
}

struct get_value *read_get_value() {
    struct get_value *get_value = xmalloc(sizeof(struct get_value));

    fread(&(get_value->val), sizeof(int), 1, fin);

    return get_value;
}

struct add *read_add() {
    struct add *add = xmalloc(sizeof(struct add));

    add->expr_left = read_statement();
    add->expr_right = read_statement();

    return add;
}

struct subtract *read_subtract() {
    struct subtract *subtract = xmalloc(sizeof(struct subtract));

    subtract->expr_left = read_statement();
    subtract->expr_right = read_statement();

    return subtract;
}

struct multiply *read_multiply() {
    struct multiply *multiply = xmalloc(sizeof(struct multiply));

    multiply->expr_left = read_statement();
    multiply->expr_right = read_statement();

    return multiply;
}

struct parens *read_parens() {
    struct parens *parens = xmalloc(sizeof(struct parens));

    parens->expr = read_statement();

    return parens;
}

struct compare_g *read_compare_g() {
    struct compare_g *compare_g = xmalloc(sizeof(struct compare_g));

    compare_g->expr_left = read_statement();
    compare_g->expr_right = read_statement();
    
    return compare_g;
}

struct compare_ge *read_compare_ge() {
    struct compare_ge *compare_ge = xmalloc(sizeof(struct compare_ge));

    compare_ge->expr_left = read_statement();
    compare_ge->expr_right = read_statement();
    
    return compare_ge;
}

struct compare_l *read_compare_l() {
    struct compare_l *compare_l = xmalloc(sizeof(struct compare_l));

    compare_l->expr_left = read_statement();
    compare_l->expr_right = read_statement();
    
    return compare_l;
}

struct compare_le *read_compare_le() {
    struct compare_le *compare_le = xmalloc(sizeof(struct compare_le));

    compare_le->expr_left = read_statement();
    compare_le->expr_right = read_statement();
    
    return compare_le;
}

struct compare_e *read_compare_e() {
    struct compare_e *compare_e = xmalloc(sizeof(struct compare_e));

    compare_e->expr_left = read_statement();
    compare_e->expr_right = read_statement();
    
    return compare_e;
}

struct compare_ne *read_compare_ne() {
    struct compare_ne *compare_ne = xmalloc(sizeof(struct compare_ne));

    compare_ne->expr_left = read_statement();
    compare_ne->expr_right = read_statement();
    
    return compare_ne;
}

struct if_statement *read_if_statement() {
    struct if_statement *if_statement = xmalloc(sizeof(struct if_statement));

    if_statement->expr = read_statement();
    if_statement->statements = read_statements();

    return if_statement;
}

struct while_loop *read_while_loop() {
    struct while_loop *while_loop = xmalloc(sizeof(struct while_loop));

    while_loop->expr = read_statement();
    while_loop->statements = read_statements();

    return while_loop;
}

struct for_loop *read_for_loop() {
    struct for_loop *for_loop = xmalloc(sizeof(struct for_loop));

    for_loop->initial_statement = read_statement();
    for_loop->expr = read_statement();
    for_loop->iterator_statement = read_statement();
    for_loop->statements = read_statements();

    return for_loop;
}
