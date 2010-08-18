#include "mathscript.h"
#include "xmalloc.h"
#include <stdlib.h>

struct statement_node* statement_node_init() {
    return xmalloc(sizeof(struct statement_node));
}

struct statement_list* statement_list_init() {
    struct statement_list* l = xmalloc(sizeof(struct statement_list));
    struct statement_node* s = xmalloc(sizeof(struct statement_node));
    s->type = TYPE_ROOT;
    l->start = s;
    l->end = s;

    return l;
}

/* s = function type, t = enum type */
#define DEFINE_NEW_FUNC(s,t)                                    \
    struct statement_node* new_##s(struct s* s) {             \
        struct statement_node* new = statement_node_init();     \
        new->type = t;                                          \
        new->data.s = s;                                        \
                                                                \
        return new;                                             \
    }

/* please use semicolons on then end of the macros */
DEFINE_NEW_FUNC(call_function, TYPE_CALL_FUNCTION);
DEFINE_NEW_FUNC(set_variable, TYPE_SET_VARIABLE);
DEFINE_NEW_FUNC(get_variable, TYPE_GET_VARIABLE);
DEFINE_NEW_FUNC(get_value, TYPE_GET_VALUE);
DEFINE_NEW_FUNC(add, TYPE_ADD);
DEFINE_NEW_FUNC(subtract, TYPE_SUBTRACT);
DEFINE_NEW_FUNC(multiply, TYPE_MULTIPLY);
DEFINE_NEW_FUNC(parens, TYPE_PARENS);
DEFINE_NEW_FUNC(compare_g, TYPE_COMPARE_G);
DEFINE_NEW_FUNC(compare_ge, TYPE_COMPARE_GE);
DEFINE_NEW_FUNC(compare_l, TYPE_COMPARE_L);
DEFINE_NEW_FUNC(compare_le, TYPE_COMPARE_LE);
DEFINE_NEW_FUNC(compare_e, TYPE_COMPARE_E);
DEFINE_NEW_FUNC(compare_ne, TYPE_COMPARE_NE);
DEFINE_NEW_FUNC(if_statement, TYPE_IF_STATEMENT);
DEFINE_NEW_FUNC(while_loop, TYPE_WHILE_LOOP);
DEFINE_NEW_FUNC(for_loop, TYPE_FOR_LOOP);
