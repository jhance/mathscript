#ifndef NEW_H
#define NEW_H

#include "statement.h"

/* Declares helpers for creating nodes based on the structs
 * See also: DEFINE_NEW_FUNC in new.c
 *
 * Example: 
 * struct statement_node *new_get_value(struct get_value *get_value);
 */
#define DECLARE_NEW_FUNC(s) struct statement_node *new_##s(struct s *s);

/* please use semicolons on the macros */
DECLARE_NEW_FUNC(call_function);
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

#endif
