#include "statement.h"
#include "xmalloc.h"

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

