#include "symtable.h"
#include "xmalloc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

symtable symtable_init() {
    /* There are 52 available slots */
    symtable table = xmalloc(sizeof(symtable_val) * 52);
    return table;
}

int symtable_calc_index(char identifier) {
    if(identifier >= 'A' && identifier <= 'Z') {
        return identifier - 'A';
    }
    else if(identifier >= 'a' && identifier <= 'z') { 
        return identifier - 'a' + 26;
    }
    else {
        fprintf(stderr, "Error: Invalid identifier");
        exit(1);
    }
}

symtable_val symtable_get(symtable table, char identifier) {
    symtable_val val = table[symtable_calc_index(identifier)];
    if(val != NULL) {
        return val;
    }
    else {
        fprintf(stderr, "Error: Undefined identifier");
        exit(1);
    }
}

void symtable_set(symtable table, char identifier, symtable_val val) {
    table[symtable_calc_index(identifier)] = val;
}
