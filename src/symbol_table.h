#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "uthash.h"
#include <stdbool.h>

struct _Hash {
    char *name;
    bool context;
    UT_hash_handle hh;
};

typedef struct _Hash Hash;

extern Hash *var_table;

void add_var(char *s);
bool lookup_context(char *s);
void replace_context(char *s, bool ctx);
unsigned count_var();
void free_hash();

#endif