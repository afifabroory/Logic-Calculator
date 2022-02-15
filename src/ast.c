#include "ast.h"

Node *CreateOptNode(OPType type, Node *left_node, Node *right_node) {
    Node *t_node = malloc(sizeof(Node));
    t_node->type = NODE_OP;
    t_node->val.op = type;

    t_node->left = left_node;
    t_node->right = right_node;

    return t_node;
}

Node *CreateConstNode(bool value) {
    Node *t_node = malloc(sizeof(Node));
    t_node->type = NODE_CONST;
    t_node->val.t_val = value;
    
    t_node->left = NULL;
    t_node->right = NULL;
    
    return t_node;
}

Node *CreateVarNode(char *_str) {
    Node *t_node = malloc(sizeof(Node));
    t_node->type = NODE_VAR;
    t_node->val.str = _str;

    t_node->left = NULL;
    t_node->right = NULL;

    return t_node;
}

void FreeAST(Node *ast) {
    if (!ast) return;

    FreeAST(ast->left);
    FreeAST(ast->right);
    free(ast);
}
