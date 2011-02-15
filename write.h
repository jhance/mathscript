#ifndef WRITE_H
#define WRITE_H

#include "statement.h"
#include <stdio.h>

void write_prepare(char *filename);
void write_end(void);
void write_statements(struct statement_list *list);
void write_statement(struct statement_node *node);

#define DECLARE_WRITE_FUNC(s) void write_##s(struct s *s);

/* please use semicolons after the macros */
DECLARE_WRITE_FUNC(call_function);
DECLARE_WRITE_FUNC(set_variable);
DECLARE_WRITE_FUNC(get_variable);
DECLARE_WRITE_FUNC(get_value);
DECLARE_WRITE_FUNC(add);
DECLARE_WRITE_FUNC(subtract);
DECLARE_WRITE_FUNC(multiply);
DECLARE_WRITE_FUNC(parens);
DECLARE_WRITE_FUNC(compare_g);
DECLARE_WRITE_FUNC(compare_ge);
DECLARE_WRITE_FUNC(compare_l);
DECLARE_WRITE_FUNC(compare_le);
DECLARE_WRITE_FUNC(compare_e);
DECLARE_WRITE_FUNC(compare_ne);
DECLARE_WRITE_FUNC(if_statement);
DECLARE_WRITE_FUNC(while_loop);
DECLARE_WRITE_FUNC(for_loop);

#endif
