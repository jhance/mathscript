#include "write.h"
#include "statement.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

static FILE* fout;

void write_prepare(char* filename) {
    if(filename == NULL) {
        fout = stdout;
        return;
    }
    fout = fopen(filename, "w");
    if(fout == NULL) {
        fprintf(stderr, "Error: Couldn't open file\n");
        exit(1);
    }
}

void write_end() {
    if(fout != stdout) {
        fclose(fout);
    }
}

void write_statements(struct statement_list* list) {
    struct statement_node* cur = list->start;
    while(cur != NULL) {
        write_statement(cur);

        /* break AFTER we do TYPE_END */
        if(cur->type == TYPE_END) {
            break;
        }

        cur = cur->next;
    }
}

void write_statement(struct statement_node* s) {
    fwrite(&(s->type), sizeof(int), 1, fout);
    switch(s->type) {
        case TYPE_INVALID:
            fprintf(stderr, "Error: Invalid statement\n");
            exit(1);
        case TYPE_START:
        case TYPE_END:
            return;
        case TYPE_CALL_FUNCTION:
            write_call_function(s->data->call_function);
            return;
        case TYPE_SET_VARIABLE:
            write_set_variable(s->data->set_variable);
            return;
        case TYPE_GET_VARIABLE:
            write_get_variable(s->data->get_variable);
            return;
        case TYPE_GET_VALUE:
            write_get_value(s->data->get_value);
            return;
        case TYPE_ADD:
            write_add(s->data->add);
            return;
        case TYPE_SUBTRACT:
            write_subtract(s->data->subtract);
            return;
        case TYPE_MULTIPLY:
            write_multiply(s->data->multiply);
            return;
        case TYPE_PARENS:
            write_parens(s->data->parens);
            return;
        case TYPE_COMPARE_G:
            write_compare_g(s->data->compare_g);
            return;
        case TYPE_COMPARE_GE:
            write_compare_ge(s->data->compare_ge);
            return;
        case TYPE_COMPARE_L:
            write_compare_l(s->data->compare_l);
            return;
        case TYPE_COMPARE_LE:
            write_compare_le(s->data->compare_le);
            return;
        case TYPE_COMPARE_E:
            write_compare_e(s->data->compare_e);
            return;
        case TYPE_COMPARE_NE:
            write_compare_ne(s->data->compare_ne);
            return;
        case TYPE_IF_STATEMENT:
            write_if_statement(s->data->if_statement);
            return;
        case TYPE_WHILE_LOOP:
            write_while_loop(s->data->while_loop);
            return;
        case TYPE_FOR_LOOP:
            write_for_loop(s->data->for_loop);
            return;
    }

    fprintf(stderr, "Error: Invalid statement\n");
}

void write_call_function(struct call_function* call_function) {
    size_t size = strlen(call_function->identifier); /* exclude \0 */
    fwrite(&size, sizeof(size_t), 1, fout);
    fwrite(call_function->identifier, sizeof(char), size, fout);

    /* assume args != NULL and that theres only one arg */
    write_statement(call_function->args);
}

void write_set_variable(struct set_variable* set_variable) {
    size_t size = strlen(set_variable->identifier); /* exclude \0 */
    fwrite(&size, sizeof(size_t), 1, fout);
    fwrite(set_variable->identifier, sizeof(char), size, fout);

    write_statement(set_variable->expr);
}

void write_get_variable(struct get_variable* get_variable) {
    size_t size = strlen(get_variable->identifier);
    fwrite(&size, sizeof(size_t), 1, fout);
    fwrite(get_variable->identifier, sizeof(char), size, fout);
}

void write_get_value(struct get_value* get_value) {
    fwrite(&(get_value->val), sizeof(int), 1, fout);
}

void write_add(struct add* add) {
    write_statement(add->expr_left);
    write_statement(add->expr_right);
}

void write_subtract(struct subtract* subtract) {
    write_statement(subtract->expr_left);
    write_statement(subtract->expr_right);
}

void write_multiply(struct multiply* multiply) {
    write_statement(multiply->expr_left);
    write_statement(multiply->expr_right);
}

void write_parens(struct parens* parens) {
    write_statement(parens->expr);
}

void write_compare_g(struct compare_g* compare_g) {
    write_statement(compare_g->expr_left);
    write_statement(compare_g->expr_right);
}

void write_compare_ge(struct compare_ge* compare_ge) {
    write_statement(compare_ge->expr_left);
    write_statement(compare_ge->expr_right);
}

void write_compare_l(struct compare_l* compare_l) {
    write_statement(compare_l->expr_left);
    write_statement(compare_l->expr_right);
}

void write_compare_le(struct compare_le* compare_le) {
    write_statement(compare_le->expr_left);
    write_statement(compare_le->expr_right);
}

void write_compare_e(struct compare_e* compare_e) {
    write_statement(compare_e->expr_left);
    write_statement(compare_e->expr_right);
}

void write_compare_ne(struct compare_ne* compare_ne) {
    write_statement(compare_ne->expr_left);
    write_statement(compare_ne->expr_right);
}

void write_if_statement(struct if_statement* if_statement) {
    write_statement(if_statement->expr);
    write_statements(if_statement->statements);
}

void write_while_loop(struct while_loop* while_loop) {
    write_statement(while_loop->expr);
    write_statements(while_loop->statements);
}

void write_for_loop(struct for_loop* for_loop) {
    write_statement(for_loop->initial_statement);
    write_statement(for_loop->expr);
    write_statement(for_loop->iterator_statement);
    write_statements(for_loop->statements);
}
