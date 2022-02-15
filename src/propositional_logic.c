#include "ast.h"
#include "symbol_table.h"

// https://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
unsigned exp_of_two(unsigned exp) {

    unsigned base = 2, result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

bool eval_ast(Node **node) {
    if ((*node)->type == NODE_VAR) return lookup_context((*node)->val.str);
    else if ((*node)->type == NODE_OP) {
        bool left, right; 

        left = eval_ast(&((*node)->left));
        if ((*node)->val.op & 0xF) right = eval_ast(&((*node)->right));

        switch ((*node)->val.op) {
            case OP_CONJ : return left && right;
            case OP_DISJ : return left || right;
            case OP_EQUV : return (!left || right) && (left || !right);
            case OP_IMP : return !left || right;
            case OP_NEG : return !left;
        }
    }
    return (*node)->val.t_val;
}

void generate_truth_table(Node **node) {
    
    unsigned num_of_vars = count_var();
    unsigned num_of_row = exp_of_two(num_of_vars);

    char *var_list[num_of_vars];
    get_list_var(*&var_list);

    unsigned k, context;
    for (unsigned i = 0; i < num_of_row; i++) {
        k = num_of_vars;
        for (unsigned j = 0; j < num_of_vars; j++) {
            context = (i >> --k) & 1;
            replace_context(var_list[j], context);
        }
        eval_ast(node);
    }
}