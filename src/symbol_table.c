#include "symbol_table.h"
#include <string.h>
#include <stdlib.h>

Hash *var_table = NULL;

void get_list_var(char *list[]) {
    Hash *var;

    unsigned cnt = 0;
    for (var = var_table; var != NULL; var = var->hh.next) list[cnt++] = strdup(var->name);
}

void add_var(char *s) {
    Hash *var;

    HASH_FIND_STR(var_table, s, var);
    if (var == NULL) {
        var = malloc(sizeof *var);
        var->name = s;
        var->context = false; // default value

        HASH_ADD_KEYPTR(hh, var_table, var->name, strlen(var->name), var);
    }
}

bool lookup_context(char *s) {
    Hash *var;

    HASH_FIND_STR(var_table, s, var);
    return var->context;
}

void replace_context(char *s, bool ctx) {
    Hash *var;

    HASH_FIND_STR(var_table, s, var);
    var->context = ctx;
}

unsigned count_var() {
    return HASH_COUNT(var_table);
}

void free_hash() {
    Hash *var, *tmp;

    HASH_ITER(hh, var_table, var, tmp) {
        HASH_DEL(var_table, var);
        free(var);
    }
}