#ifndef EXEC_H
#define EXEC_H

#include "statement.h"

void exec_prepare(void);
int exec_statement(struct statement_node *s);
void exec_statements(struct statement_list *list);

/* Called from the executer to actually execute a statement node
 *
 * Example:
 * int exec_get_value(struct get_value *get_value);
 */
#define DECLARE_EXEC_FUNC(s) int exec_##s(struct s *s);

/* please use semicolons after the macros */
DECLARE_EXEC_FUNC(call_function);
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
