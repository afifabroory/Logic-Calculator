#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    OP_CONJ,
    OP_DISJ,
    OP_EQUV,
    OP_IMP,
    OP_NEG
} OPType;

typedef enum {
    NODE_OP,
    NODE_VAR,
    NODE_CONST
} NodeType;

struct _Node {
    NodeType type;
    union {
        OPType op;
        bool t_val;
        const char *str;
    } val;
    struct _Node *left, *right;
};
typedef struct _Node Node;

Node *CreateOptNode(OPType type, Node *left_node, Node *right_node);
Node *CreateConstNode(bool value);
Node *CreateVarNode(const char *_str);
void FreeAST(Node *ast);

#endif
