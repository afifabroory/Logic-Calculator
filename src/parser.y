%{
#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern int yylex();
extern void yy_scan_string(const char *str);
extern void yyerror(int *results, Node **tree, const char *s);

bool directlyEval = true;
%}

%code requires { bool directlyEval; }

%parse-param {int *results} {Node **tree}
%define parse.error verbose

%union { 
    Node *AST; 
    bool t_val;
    char *id;
}

%token EQUV IMP IF THEN
%token DISJ CONJ
%token NEG CONST VAR

%type <id> VAR
%type <t_val> CONST

%left IMP EQUV
%nonassoc IF THEN
%left CONJ DISJ
%nonassoc NEG

%%
Formula    : Equivalance                  { 
                if (directlyEval) *results = $<t_val>1;
                else *tree = $<AST>1; 
              }
           ;

Equivalance: Equivalance EQUV Implication {  
                if (directlyEval) $<t_val>$ = (!$<t_val>1 || $<t_val>3) && ($<t_val>1 || !$<t_val>3);
                else $<AST>$ = CreateOptNode(OP_EQUV, $<AST>1, $<AST>3); 
              }
           | Implication
           ;

Implication: Implication IMP Disjunction  { 
                if (directlyEval) $<t_val>$ = !$<t_val>1 || $<t_val>3;
                else $<AST>$ = CreateOptNode(OP_IMP, $<AST>1, $<AST>3); 
              }
           | Disjunction
           ;

Disjunction: Disjunction DISJ Conjunction { 
                if (directlyEval) $<t_val>$ = $<t_val>1 || $<t_val>3;
                else $<AST>$ = CreateOptNode(OP_DISJ, $<AST>1, $<AST>3); 
              }
           | Conjunction
           ;

Conjunction: Conjunction CONJ Negation    { 
                if (directlyEval) $<t_val>$ = $<t_val>1 && $<t_val>3; 
                else $<AST>$ = CreateOptNode(OP_CONJ, $<AST>1, $<AST>3); 
              }
           | Negation
           ;

Negation   : NEG Negation                 { 
                if (directlyEval) $<t_val>$ = !$<t_val>2;
                else $<AST>$ = CreateOptNode(OP_NEG, $<AST>2, NULL); 
              }
           | Atomic
           ;

Atomic     : VAR                          { $<AST>$ = CreateVarNode($1); }
           | CONST                        { 
                if (directlyEval) $<t_val>$ = $1; 
                else $<AST>$ = CreateConstNode($1); 
              }
           | '(' Equivalance ')'          { 
                if (directlyEval) $<t_val>$ = $<t_val>2; 
                else $<AST>$ = $<AST>2;
              }
           ;
%%

void yyerror(int *results, Node **tree, char const *s) {
  fprintf(stderr, "%s\n", s);
}
