#include "ast.h"
#include "symbol_table.h"
#include <stdio.h>

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

void generate_truth_table(Node **node) {
    char readable_exp[total_char];
    memset(readable_exp, '\0', sizeof readable_exp);
    AstToStr(&(*node), readable_exp);

    // Space between var column and expression column
    char space[(strlen(readable_exp)+1)/2+1];
    memset(space, '\0', sizeof space);
    for (int i = 0; i < (strlen(readable_exp)+1)/2; i++) space[i] = ' ';

    unsigned num_of_vars = count_var();
    unsigned num_of_row = exp_of_two(num_of_vars);

    char *var_list[num_of_vars];
    get_list_var(*&var_list);

    // Print var
    for (unsigned i = 0; i < num_of_vars; i++) printf("%s ", var_list[i]);
    printf("%s", readable_exp); // print expression
    printf("\n");

    unsigned k, context;
    for (unsigned i = 0; i < num_of_row; i++) {
        k = num_of_vars;
        for (unsigned j = 0; j < num_of_vars; j++) {
            context = (i >> --k) & 1;
            replace_context(var_list[j], context);
            printf("%s ", context ? "T" : "F");
        }
        printf("%s", space);
        printf("%s\n", eval_ast(node) ? "T" : "F");
    }

    printf("\n");
    total_char = 0;
}