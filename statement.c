#include "statement.h"
#include "xmalloc.h"

struct statement_node* statement_node_init() {
    return xmalloc(sizeof(struct statement_node));
}

struct statement_list* statement_list_init() {
    struct statement_list* l = xmalloc(sizeof(struct statement_list));
    struct statement_node* s = xmalloc(sizeof(struct statement_node));
    s->type = TYPE_START;
    l->start = s;
    l->end = s;

    return l;
}

void statement_list_end(struct statement_list* list) {
    struct statement_node* e = xmalloc(sizeof(struct statement_node));
    e->type = TYPE_END;
    list->end->next = e;
    list->end = e;
}
