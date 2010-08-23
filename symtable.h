#ifndef SYMTABLE_H
#define SYMTABLE_H

#define SYMTABLE_SIZE 50
#define SYMTABLE_HASH_MULTIPLIER 31

struct symtable_chain {
    struct symtable_chain* next;
    char* identifier;
    void* val;
};

struct symtable {
    struct symtable_chain* chains;
};

struct symtable* symtable_init(void);
int symtable_hash(char* identifier);
void* symtable_get(struct symtable* table, char* identifier);
void symtable_set(struct symtable* table, char* identifier, void* val);

#endif
