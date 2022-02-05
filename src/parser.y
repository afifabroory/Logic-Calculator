%{
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

extern int yylex();
extern void yy_scan_string(const char *str);
extern void yyerror(Node **tree, const char *s);
%}

%parse-param {Node **tree}
%define parse.error verbose

%union { 
    Node *AST; 
    bool t_val;
    const char *id;
}

%token EQUV IMP IF THEN
%token DISJ CONJ
%token NEG CONST VAR

%type <AST> Equivalance Implication Disjunction Conjunction Negation Atomic
%type <t_val> CONST
%type <id> VAR

%left IMP EQUV
%nonassoc IF THEN
%left CONJ DISJ
%nonassoc NEG

%%
Formula    : Equivalance                  { *tree = $1; }
           ;

Equivalance: Equivalance EQUV Implication { $$ = CreateOptNode(OP_EQUV, $1, $3); }
           | Implication
           ;

Implication: Implication IMP Disjunction  { $$ = CreateOptNode(OP_IMP, $1, $3); }
           | Disjunction
           ;

Disjunction: Disjunction DISJ Conjunction { $$ = CreateOptNode(OP_DISJ, $1, $3); }
           | Conjunction
           ;

Conjunction: Conjunction CONJ Negation       { $$ = CreateOptNode(OP_CONJ, $1, $3); }
           | Negation
           ;

Negation   : NEG Negation                   { $$ = CreateOptNode(OP_NEG, $2, NULL); }
           | Atomic
           ;

Atomic     : VAR                          { $$ = CreateVarNode($1); }
           | CONST                        { $$ = CreateConstNode($1); }
           | '(' Equivalance ')'          { $$ = $2; }
           ;
%%

void yyerror(Node **tree, char const *s) {
  fprintf(stderr, "%s\n", s);
}
