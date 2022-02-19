#include "ast.h"
#include "string.h"
#include "symbol_table.h"

unsigned total_char = 0;

Node *CreateOptNode(OPType type, Node *left_node, Node *right_node) {
    Node *t_node = malloc(sizeof(Node));
    t_node->type = NODE_OP;
    t_node->val.op = type;

    t_node->left = left_node;
    t_node->right = right_node;

    if (type & 0x3) total_char += 5;       // Two space, one char, two paren.
    else if (type & 0x4) total_char += 7;  // Two space, three char, two paren.
    else if (type & 0x8) total_char += 6;  // Two space, two char, two paren.
    else if (type & 0x10) total_char += 3; // Zero space, one char, two paren.

    return t_node;
}

Node *CreateConstNode(bool value) {
    Node *t_node = malloc(sizeof(Node));
    t_node->type = NODE_CONST;
    t_node->val.t_val = value;
    
    t_node->left = NULL;
    t_node->right = NULL;
    
    if (value) total_char += 4;
    else total_char += 5;

    return t_node;
}

Node *CreateVarNode(char *_str) {
    Node *t_node = malloc(sizeof(Node));
    t_node->type = NODE_VAR;
    t_node->val.str = _str;

    t_node->left = NULL;
    t_node->right = NULL;

    total_char += strlen(_str);

    return t_node;
}

bool eval_ast(Node **ast) {
    if ((*ast)->type == NODE_VAR) return lookup_context((*ast)->val.str);
    else if ((*ast)->type == NODE_OP) {
        bool left, right; 

        left = eval_ast(&((*ast)->left));
        if ((*ast)->val.op & 0xF) right = eval_ast(&((*ast)->right));

        switch ((*ast)->val.op) {
            case OP_CONJ : return left && right;
            case OP_DISJ : return left || right;
            case OP_EQUV : return (!left || right) && (left || !right);
            case OP_IMP : return !left || right;
            case OP_NEG : return !left;
        }
    }
    return (*ast)->val.t_val;
}

void AstToStr(Node **ast, char *dest) {
    if ((*ast)->type == NODE_VAR) strcat(dest, (*ast)->val.str);
    else if ((*ast)->type == NODE_CONST) strcat(dest, (*ast)->val.t_val ? "True" : "False");
    else if ((*ast)->type == NODE_OP) {
        char left[total_char];
        memset(left, '\0', sizeof left);

        strcat(dest, "(");
        AstToStr(&((*ast)->left), left);
        if ((*ast)->val.op & 0xF) {
            char right[total_char];
            memset(right, '\0', sizeof right);

            //For Binary operator
            AstToStr(&((*ast)->right), right);
            strcat(dest, left);  

            switch((*ast)->val.op) {
                case OP_CONJ : strcat(dest, " & "); break;
                case OP_DISJ : strcat(dest, " | "); break;
                case OP_EQUV : strcat(dest, " <=> "); break;
                case OP_IMP : strcat(dest, " => "); break;
            }

            strcat(dest, right);
        } else {
            strcat(dest, "~"); // For unary operator
            strcat(dest, left);
        }
        strcat(dest, ")");
    }
}

void FreeAST(Node *ast) {
    if (!ast) return;

    FreeAST(ast->left);
    FreeAST(ast->right);
    free(ast);
}
