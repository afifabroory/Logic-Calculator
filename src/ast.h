#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    NODE_OP = 1 << 0,
    NODE_VAR = 1 << 1,
    NODE_CONST = 1 << 2
} NodeType;

typedef enum {
    OP_CONJ = 1 << 0,
    OP_DISJ = 1 << 1,
    OP_EQUV = 1 << 2,
    OP_IMP = 1 << 3,
    OP_NEG = 1 << 4
} OPType;

struct _Node {
    NodeType type;
    union {
        OPType op;
        bool t_val;
        char *str;
    } val;
    struct _Node *left, *right;
};
typedef struct _Node Node;

extern unsigned total_char;

Node *CreateOptNode(OPType type, Node *left_node, Node *right_node);
Node *CreateConstNode(bool value);
Node *CreateVarNode(char *_str);
bool eval_ast(Node **ast);
void AstToStr(Node **ast, char *dest);
void FreeAST(Node *ast);

#endif
