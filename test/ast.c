#include "../src/ast.h"
#include "../src/y.tab.h"

#include <stdio.h>
#include <assert.h>

extern void yy_scan_string(const char *s);

void constant_remain_constant_test();
void negation_constant_test();
void conjunction_operator_test();
void disjunction_operator_test();
void implication_operator_test();
void equivalance_operator_test();
void precedence_operation_test();
void syntax_error_test();

Node *results;

int main() {
    results = malloc(sizeof(Node));
    constant_remain_constant_test();
    negation_constant_test();
    conjunction_operator_test();
    disjunction_operator_test();
    implication_operator_test();
    equivalance_operator_test();
    precedence_operation_test();   
    printf("AST OK!\n");
}

void constant_remain_constant_test() {
    yy_scan_string("1");
    assert(yyparse(&results) == 0);
    
    assert(results->left == NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_CONST);
    assert(results->val.t_val == true);
    
    yy_scan_string("0");
    assert(yyparse(&results) == 0);
    
    assert(results->left == NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_CONST);
    assert(results->val.t_val == false);
}

void negation_constant_test() {   
    
    // ¬T = F
    yy_scan_string("~1"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_NEG);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);

    // ¬F = T
    yy_scan_string("~0"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_NEG);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
}

void conjunction_operator_test() {
    
    // T ∧ T (True)
    yy_scan_string("1 & 1"); 
    assert(yyparse(&results) == 0);

    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_CONJ);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    // F ∧ F (False)
    yy_scan_string("0 & 0"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_CONJ);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    // T ∧ F = F ∧ T (False)
    yy_scan_string("1 & 0"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_CONJ);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    yy_scan_string("0 & 1"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_CONJ);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);
}

void disjunction_operator_test() {
    
    // T ∨ T (True)
    yy_scan_string("1 | 1"); 
    assert(yyparse(&results) == 0);
   
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    // F ∨ F (False)
    yy_scan_string("0 | 0"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    // T ∨ F = F ∨ T (True)
    yy_scan_string("1 | 0"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    yy_scan_string("0 | 1"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);
}

void implication_operator_test() {    

    // True
    yy_scan_string("1 => 1"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_IMP);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    yy_scan_string("0 => 0"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_IMP);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    yy_scan_string("0 => 1"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_IMP);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    // False
    yy_scan_string("1 => 0"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_IMP);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);
}

void equivalance_operator_test() {
    
    // True
    yy_scan_string("1 <=> 1"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_EQUV);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    yy_scan_string("0 <=> 0"); 
    assert(yyparse(&results) == 0);

    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_EQUV);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    // False
    yy_scan_string("0 <=> 1"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_EQUV);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    yy_scan_string("1 <=> 0"); 
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_EQUV);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);
}

void precedence_operation_test() {

    /*
     *          '|'
     *          / \
     *         ~   &
     *         |  / \
     *         0 0   1
     *
     *   AST Model in Scheme code:
     *   (or
     *       (not #f)
     *       (and #f #t)
     *   )
     */
    yy_scan_string("~0 | 0 & 1");
    assert(yyparse(&results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ); 

    assert(results->left->left != NULL);
    assert(results->left->right == NULL);
    assert(results->left->type == NODE_OP);
    assert(results->left->val.op == OP_NEG);

    assert(results->left->left->left == NULL);
    assert(results->left->left->right == NULL);
    assert(results->left->left->type == NODE_CONST);
    assert(results->left->left->val.t_val == false);
 
    assert(results->right->left != NULL);
    assert(results->right->right != NULL);
    assert(results->right->type == NODE_OP);
    assert(results->right->val.op == OP_CONJ);

    assert(results->right->left->left == NULL);
    assert(results->right->left->right == NULL);
    assert(results->right->left->type == NODE_CONST);
    assert(results->right->left->val.t_val == false);

    assert(results->right->right->left == NULL);
    assert(results->right->right->right == NULL);
    assert(results->right->right->type == NODE_CONST);
    assert(results->val.t_val == true);

    /*
     *              ~
     *              |
     *             '|'
     *             / \
     *             ~  &
     *             | / \
     *             f f  t
     *          
     *
     *   AST Model in Scheme Code:
     *   (not (or 
     *            (not #f)
     *            (and #f #t)
     *        )
     *   ) 
     *
     */
    yy_scan_string("~(~0 | 0 & 1)");
    assert(yyparse(&results) == 0);

    assert(results->left != NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_NEG);
    
    assert(results->left->left != NULL);
    assert(results->left->right != NULL);
    assert(results->left->type == NODE_OP);
    assert(results->left->val.op == OP_DISJ);
 
    assert(results->left->right->left != NULL);
    assert(results->left->right->right != NULL); 
    assert(results->left->right->type == NODE_OP);
    assert(results->left->right->val.op == OP_CONJ);
  
    assert(results->left->left->left != NULL);
    assert(results->left->left->right == NULL);
    assert(results->left->left->type == NODE_OP);
    assert(results->left->left->val.op == OP_NEG);

    assert(results->left->left->left->left == NULL);
    assert(results->left->left->left->right == NULL);
    assert(results->left->left->left->type == NODE_CONST);
    assert(results->left->left->left->val.t_val == false);

    assert(results->left->right->left->left == NULL);
    assert(results->left->right->left->right == NULL);
    assert(results->left->right->left->type == NODE_CONST); 
    assert(results->left->right->left->val.t_val == false);

    assert(results->left->right->right->left == NULL);
    assert(results->left->right->right->right == NULL);
    assert(results->left->right->right->type == NODE_CONST);
    assert(results->left->right->right->val.t_val == true);

    yy_scan_string("~(NOT 0 | 0 & 1) <=> 0 & ~0 | ~1");
    assert(yyparse(&results) == 0);
    //assert(results == 1);

    /*
     *             '|'
     *             / \
     *            '|' 0
     *            / \
     *            0  &
     *              / \
     *              0  1
     *
     *   AST Model in Scheme Code:
     *   (or 
     *      (or 
     *          0 
     *          (and 0 1)
     *      ) 
     *      0
     *    )
     *
     */
    yy_scan_string("0 | 0 & 1 | 0");
    assert(yyparse(&results) == 0);

    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);

    assert(results->right->left == NULL);
    assert(results->right->right == NULL);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    assert(results->left->left != NULL);
    assert(results->left->right != NULL);
    assert(results->left->type == NODE_OP);
    assert(results->left->val.op == OP_DISJ);

    assert(results->left->left->left == NULL);
    assert(results->left->left->right == NULL);
    assert(results->left->left->type == NODE_CONST);
    assert(results->left->left->val.t_val == false);

    assert(results->left->right->left != NULL);
    assert(results->left->right->right != NULL);
    assert(results->left->right->type == NODE_OP);
    assert(results->left->right->val.op == OP_CONJ);

    assert(results->left->right->left->left == NULL);
    assert(results->left->right->left->left == NULL);
    assert(results->left->right->left->type == NODE_CONST);
    assert(results->left->right->left->val.t_val == false);

    assert(results->left->right->right->left == NULL);
    assert(results->left->right->right->left == NULL);
    assert(results->left->right->right->type == NODE_CONST);
    assert(results->left->right->right->val.t_val == true);
}
