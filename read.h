#ifndef READ_H
#define READ_H

#include "statement.h"
#include <stdio.h>

void read_prepare(char* filename);
void read_end(void);
struct statement_list* read_statements();
struct statement_node* read_statement();

#define DECLARE_READ_FUNC(s) struct s* read_##s();

/* please use semicolons after the macros */
DECLARE_READ_FUNC(call_function);
DECLARE_READ_FUNC(set_variable);
DECLARE_READ_FUNC(get_variable);
DECLARE_READ_FUNC(get_value);
DECLARE_READ_FUNC(add);
DECLARE_READ_FUNC(subtract);
DECLARE_READ_FUNC(multiply);
DECLARE_READ_FUNC(parens);
DECLARE_READ_FUNC(compare_g);
DECLARE_READ_FUNC(compare_ge);
DECLARE_READ_FUNC(compare_l);
DECLARE_READ_FUNC(compare_le);
DECLARE_READ_FUNC(compare_e);
DECLARE_READ_FUNC(compare_ne);
DECLARE_READ_FUNC(if_statement);
DECLARE_READ_FUNC(while_loop);
DECLARE_READ_FUNC(for_loop);

#endif
