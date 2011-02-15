#include "statement.h"
#include "xmalloc.h"
#include <stdlib.h>
#include <string.h>

struct statement_node *statement_node_init(void) {
    struct statement_node *s = xmalloc(sizeof(struct statement_node));
    s->next = NULL;
    s->data = NULL;
    s->type = TYPE_INVALID;
    return s;
}

struct statement_list *statement_list_init(void) {
    struct statement_list *l = xmalloc(sizeof(struct statement_list));
    struct statement_node *s = statement_node_init();
    s->type = TYPE_START;
    l->start = s;
    l->end = s;

    return l;
}

void statement_list_end(struct statement_list *list) {
    struct statement_node *e = xmalloc(sizeof(struct statement_node));
    e->data = NULL;
    e->next = NULL;
    e->type = TYPE_END;
    list->end->next = e;
    list->end = e;
}
