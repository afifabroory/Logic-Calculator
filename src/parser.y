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

%type <AST> Binary Imply Atomic
%type <t_val> CONST
%type <id> VAR

%left IMP EQUV
%nonassoc IF THEN
%left CONJ DISJ
%nonassoc NEG

%%
Form    : Binary                { *tree = $1; }
        ;

Binary  : Binary DISJ Binary    { $$ = CreateOptNode(OP_DISJ, $1, $3); }
        | Binary CONJ Binary    { $$ = CreateOptNode(OP_CONJ, $1, $3); }
        | Binary EQUV Binary    { $$ = CreateOptNode(OP_EQUV, $1, $3); }
        | Imply
        | Atomic
        ;        

Imply   : Binary IMP Binary     { $$ = CreateOptNode(OP_IMP, $1, $3); }
        ;

Atomic  : NEG Atomic            { $$ = CreateOptNode(OP_NEG, $2, NULL); }
        |'(' Binary ')'         { $$ = $2; }
        | VAR                   { $$ = CreateVarNode("test"); }
        | CONST                 { $$ = CreateConstNode($1); }
        ;
%%

void yyerror(Node **tree, char const *s) {
  fprintf(stderr, "%s\n", s);
}
