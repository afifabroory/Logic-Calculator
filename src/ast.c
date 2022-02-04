#include "ast.h"

Tree *CreateEmptyNode() {
    Tree *tree = malloc(sizeof(Tree));
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

Data *CreateOptNode(OPType type) {
    Data *data = malloc(sizeof(Data));
    data->type = OP;
    data->value.op = type;
    return data;
}

Data *CreateConstNode(bool value) {
    Data *data = malloc(sizeof(Data));
    data->type = CONST;
    data->value.val = value;
    return data;
}

Data *CreateVarNode(const char *_str) {
    Data *data = malloc(sizeof(Data));
    data->type = VAR;
    data->value.str = _str;
    return data;
}

int main() {
    Tree *syntaxTree = CreateEmptyNode();
    syntaxTree->data = CreateVarNode("p");
}
