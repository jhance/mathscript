#include "symtable.h"
#include "xmalloc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct symtable* symtable_init() {
    struct symtable* table = xmalloc(sizeof(struct symtable));
    table->chains = xmalloc(sizeof(struct symtable_chain) * SYMTABLE_SIZE);
    return table;
}

int symtable_hash(char* identifier) {
    int h = 0;
    char* p;

    for(p = identifier; *p != '\0'; p++) {
        h = SYMTABLE_HASH_MULTIPLIER * h + *p;
    }
    return h % SYMTABLE_SIZE;
}

void* symtable_get(struct symtable* table, char* identifier) {
    int index = symtable_hash(identifier);
    struct symtable_chain* chain = table->chains + index;

    struct symtable_chain* cur = chain;
    while(cur->next != NULL) {
        cur = cur->next;
        if(strcmp(cur->identifier, identifier) == 0) {
            return cur->val;
        }
    }

    fprintf(stderr, "Error: No such identifier in symtable: %s\n", identifier);
    exit(1);
}

void symtable_set(struct symtable* table, char* identifier, void* val) {
    int index = symtable_hash(identifier);
    struct symtable_chain* chain = table->chains + index;
    
    struct symtable_chain* cur = chain;
    while(cur->next != NULL) {
        cur = cur->next;

        if(strcmp(cur->identifier, identifier) == 0) {
            cur->val = val;
            return;
        }
    }

    struct symtable_chain* new = xmalloc(sizeof(struct symtable_chain));
    new->identifier = identifier;
    new->val = val;
    cur->next = new;
}
