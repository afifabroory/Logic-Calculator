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

int results;

int main() {
    constant_remain_constant_test();
    negation_constant_test();
    conjunction_operator_test();
    implication_operator_test();
    equivalance_operator_test();
    precedence_operation_test();   
    printf("OK!\n");
}

void constant_remain_constant_test() {
    yy_scan_string("1");
    yyparse(&results);
    assert(results == 1);
    
    yy_scan_string("0");
    yyparse(&results);
    assert(results == 0);
}

void negation_constant_test() {   
    
    // ¬T = F
    yy_scan_string("~1"); 
    yyparse(&results);
    assert(results == 0);

    // ¬F = T
    yy_scan_string("~0"); 
    yyparse(&results);
    assert(results == 1);
}

void conjunction_operator_test() {
    
    // T ∧ T (True)
    yy_scan_string("1 & 1"); 
    yyparse(&results);
    assert(results == 1);

    // F ∧ F (False)
    yy_scan_string("0 & 0"); 
    yyparse(&results);
    assert(results == 0);

    // T ∧ F = F ∧ T (False)
    yy_scan_string("1 & 0"); 
    yyparse(&results);
    assert(results == 0);

    yy_scan_string("0 & 1"); 
    yyparse(&results);
    assert(results == 0);
}

void disjunction_operator_test() {
    
    // T ∨ T (True)
    yy_scan_string("1 | 1"); 
    yyparse(&results);
    assert(results == 1);

    // F ∨ F (False)
    yy_scan_string("0 | 0"); 
    yyparse(&results);
    assert(results == 0);

    // T ∨ F = F ∨ T (True)
    yy_scan_string("1 | 0"); 
    yyparse(&results);
    assert(results == 1);

    yy_scan_string("0 | 1"); 
    yyparse(&results);
    assert(results == 1);
}

void implication_operator_test() {    

    // True
    yy_scan_string("1 => 1"); 
    yyparse(&results);
    assert(results == 1);

    yy_scan_string("0 => 0"); 
    yyparse(&results);
    assert(results == 1);

    yy_scan_string("0 => 1"); 
    yyparse(&results);
    assert(results == 1);

    // False
    yy_scan_string("1 => 0"); 
    yyparse(&results);
    assert(results == 0);
}

void equivalance_operator_test() {
    
    // True
    yy_scan_string("1 <=> 1"); 
    yyparse(&results);
    assert(results == 1);

    yy_scan_string("0 <=> 0"); 
    yyparse(&results);
    assert(results == 1);

    // False
    yy_scan_string("0 <=> 1"); 
    yyparse(&results);
    assert(results == 0);

    yy_scan_string("1 <=> 0"); 
    yyparse(&results);
    assert(results == 0);
}

void precedence_operation_test() {
    yy_scan_string("~0 | 0 & 1");
    yyparse(&results);
    assert(results == 1);

    yy_scan_string("~(~0 | 0 & 1)");
    yyparse(&results);
    assert(results == 0);
   
    yy_scan_string("~(NOT 0 | 0 & 1) <=> 0 & ~0 | ~1");
    yyparse(&results);
    assert(results == 1);
}
