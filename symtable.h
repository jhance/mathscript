#ifndef SYMTABLE_H
#define SYMTABLE_H

typedef void** symtable;
typedef void* symtable_val;

symtable symtable_init();
int symtable_calc_index(char identifier);
symtable_val symtable_get(symtable table, char identifier);
void symtable_set(symtable table, char identifier, void* val);

#endif
