#include "../src/ast.h"
#include "../src/y.tab.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

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

    FreeAST(results);
    results = NULL;
    assert(results == NULL);

    printf("AST OK!\n");
}

void constant_remain_constant_test() {
    yy_scan_string("p");
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left == NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_VAR);
    assert(strcmp(results->val.str, "p") == 0);
    
    yy_scan_string("q");
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left == NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_VAR);
    assert(strcmp(results->val.str, "q") == 0);
}

void negation_constant_test() {   
    yy_scan_string("~p"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_NEG);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);

    yy_scan_string("~q"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right == NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_NEG);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "q") == 0);
}

void conjunction_operator_test() {
    yy_scan_string("p & 1"); 
    assert(yyparse(NULL, &results) == 0);

    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_CONJ);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    yy_scan_string("q & 0"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_CONJ);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "q") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    yy_scan_string("p & q"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_CONJ);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_VAR);
    assert(strcmp(results->right->val.str, "q") == 0);

    yy_scan_string("q & p"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_CONJ);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "q") == 0);
    assert(results->right->type == NODE_VAR);
    assert(strcmp(results->right->val.str, "p") == 0);
}

void disjunction_operator_test() {
    yy_scan_string("p | 1"); 
    assert(yyparse(NULL, &results) == 0);
   
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    yy_scan_string("p | 0"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    yy_scan_string("p | q"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_VAR);
    assert(strcmp(results->right->val.str, "q") == 0);

    yy_scan_string("p | q"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_VAR);
    assert(strcmp(results->right->val.str, "q") == 0);
}

void implication_operator_test() {    

    yy_scan_string("p => 1"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_IMP);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    yy_scan_string("p => 0"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_IMP);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);

    yy_scan_string("0 => p"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_IMP);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == false);
    assert(results->right->type == NODE_VAR);
    assert(strcmp(results->right->val.str, "p") == 0);

    yy_scan_string("1 => p"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_IMP);
    assert(results->left->type == NODE_CONST);
    assert(results->left->val.t_val == true);
    assert(results->right->type == NODE_VAR);
    assert(strcmp(results->right->val.str, "p") == 0);
}

void equivalance_operator_test() {
    
    // True
    yy_scan_string("p <=> 1"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_EQUV);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    yy_scan_string("p <=> p"); 
    assert(yyparse(NULL, &results) == 0);

    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_EQUV);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_VAR);
    assert(strcmp(results->right->val.str, "p") == 0);

    yy_scan_string("p <=> 1"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_EQUV);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == true);

    yy_scan_string("p <=> 0"); 
    assert(yyparse(NULL, &results) == 0);
    
    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_EQUV);
    assert(results->left->type == NODE_VAR);
    assert(strcmp(results->left->val.str, "p") == 0);
    assert(results->right->type == NODE_CONST);
    assert(results->right->val.t_val == false);
}

void precedence_operation_test() {

    /*
     *          '|'
     *          / \
     *         ~   &
     *         |  / \
     *         p q   r
     *
     *   AST Model in Scheme code:
     *   (or
     *       (not p)
     *       (and q r)
     *   )
     */
    yy_scan_string("~p | q & r");
    assert(yyparse(NULL, &results) == 0);
    
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
    assert(results->left->left->type == NODE_VAR);
    assert(strcmp(results->left->left->val.str, "p") == 0);
 
    assert(results->right->left != NULL);
    assert(results->right->right != NULL);
    assert(results->right->type == NODE_OP);
    assert(results->right->val.op == OP_CONJ);

    assert(results->right->left->left == NULL);
    assert(results->right->left->right == NULL);
    assert(results->right->left->type == NODE_VAR);
    assert(strcmp(results->right->left->val.str, "q") == 0);

    assert(results->right->right->left == NULL);
    assert(results->right->right->right == NULL);
    assert(results->right->right->type == NODE_VAR);
    assert(strcmp(results->right->right->val.str, "r") == 0);

    /*
     *              ~
     *              |
     *             '|'
     *             / \
     *             ~  &
     *             | / \
     *             p q  r
     *          
     *
     *   AST Model in Scheme Code:
     *   (not (or 
     *            (not #p)
     *            (and #q #r)
     *        )
     *   ) 
     *
     */
    yy_scan_string("~(~p | q & r)");
    assert(yyparse(NULL, &results) == 0);

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
    assert(results->left->left->left->type == NODE_VAR);
    assert(strcmp(results->left->left->left->val.str, "p") == 0);

    assert(results->left->right->left->left == NULL);
    assert(results->left->right->left->right == NULL);
    assert(results->left->right->left->type == NODE_VAR);
    assert(strcmp(results->left->right->left->val.str, "q") == 0);

    assert(results->left->right->right->left == NULL);
    assert(results->left->right->right->right == NULL);
    assert(results->left->right->right->type == NODE_VAR);
    assert(strcmp(results->left->right->right->val.str, "r") == 0);

    // /*
    //  *                 <=>  
    //  *              /        \
    //  *             ~         '|'
    //  *             |         / \
    //  *            '|'        &  ~
    //  *            /  \      / \ |
    //  *            ~   &     p ~ r
    //  *            |  / \      |
    //  *            p q   r     q
    //  *
    //  *   AST Model in Scheme Code:
    //  *   (equv 
    //  *      (not (or (not p)
    //  *               (and q r)))
    //  *      (or (and p (not q))
    //  *          (not r))
    //  *      )
    //  *
    //  *   Assume equv are exits in Scheme.
    //  */
    // yy_scan_string("~(NOT p | q & r) <=> p & ~q | ~r");
    // assert(yyparse(NULL, &results) == 0);
    // //assert(results == 1);

    /*
     *             '|'
     *             / \
     *            '|' s
     *            / \
     *            p  &
     *              / \
     *              q  r
     *
     *   AST Model in Scheme Code:
     *   (or 
     *      (or p (and q r)) 
     *      s)
     *
     */
    yy_scan_string("p | q & r | s");
    assert(yyparse(NULL, &results) == 0);

    assert(results->left != NULL);
    assert(results->right != NULL);
    assert(results->type == NODE_OP);
    assert(results->val.op == OP_DISJ);

    assert(results->right->left == NULL);
    assert(results->right->right == NULL);
    assert(results->right->type == NODE_VAR);
    assert(strcmp(results->right->val.str, "s") == 0);

    assert(results->left->left != NULL);
    assert(results->left->right != NULL);
    assert(results->left->type == NODE_OP);
    assert(results->left->val.op == OP_DISJ);

    assert(results->left->left->left == NULL);
    assert(results->left->left->right == NULL);
    assert(results->left->left->type == NODE_VAR);
    assert(strcmp(results->left->left->val.str, "p") == 0);

    assert(results->left->right->left != NULL);
    assert(results->left->right->right != NULL);
    assert(results->left->right->type == NODE_OP);
    assert(results->left->right->val.op == OP_CONJ);

    assert(results->left->right->left->left == NULL);
    assert(results->left->right->left->left == NULL);
    assert(results->left->right->left->type == NODE_VAR);
    assert(strcmp(results->left->right->left->val.str, "q") == 0);

    assert(results->left->right->right->left == NULL);
    assert(results->left->right->right->left == NULL);
    assert(results->left->right->right->type == NODE_VAR);
    assert(strcmp(results->left->right->right->val.str, "r") == 0);

    /*
     *             '|'
     *             / \
     *            '|' 0
     *            / \
     *            p  &
     *              / \
     *              0  1
     *
     *   AST Model in Scheme Code:
     *   (or 
     *      (or p (and #f #t)) 
     *      #f)
     *
     */
    yy_scan_string("p | 0 & 1 | 0");
    assert(yyparse(NULL, &results) == 0);

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
    assert(results->left->left->type == NODE_VAR);
    assert(strcmp(results->left->left->val.str, "p") == 0);

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
