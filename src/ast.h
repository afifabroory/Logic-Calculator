#ifndef _TREE_H
#define _TREE_H

#include <stdbool.h>

typedef enum OPType {
    NONE,
    CONJ,
    DISJ,
    EQUV,
    IMP,
    NEG
} OPType;

typedef enum TokenType {
    OP,
    VAR,
    CONST
} TokenType;

struct _Data {
    TokenType type;
    union {
        OPType op;
        bool val;
        char *str;  // Identifier name
    } value;
};
typedef struct _Data Data;

struct _Tree {
    Date *data;
    struct Node *left;
    struct Node *right;
};
typedef struct _Tree Tree;

Tree CreateEmptyNode();
Data CreateOptNode(OPType type);
Data CraeteConstNode(bool value);
Data CreateVarNode(const char *_str);

#endif
