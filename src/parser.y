%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(const char* s);
%}

%token EQUV
%token IMP
%token IF
%token THEN
%token DISJ
%token CONJ
%token NEG
%token CONST
%token VAR
%token EOL

%left IMP EQUV
%left CONJ DISJ
%precedence NEG 
%precedence IF 
%precedence THEN

%%
Expr    : Form EOL              {  printf("Result: %d\n", $1); }
        | Expr EOL
        | // ε
        ;
         
Form    : Binary
        ;

Binary  : Binary DISJ Atomic    { $$ = $1 || $3; }
        | Binary CONJ Atomic    { $$ = $1 && $3; }
        | Binary EQUV Atomic    { $$ = !$1 || $3 && !$3 || $1; }
        | Imply
        | CImply
        | Atomic
        ;        

Imply   : Atomic IMP Atomic     { $$ = !$1 || $3; }
        | IF Atomic THEN Atomic { $$ = !$2 || $4; }
        ;

CImply  : Atomic IF Atomic      { $$ = !$3 || $1; }
        ;

Atomic  : '(' Form ')'          { $$ = $2; }
        | NEG VAR               { $$ = $2; }
        | NEG CONST             { $$ = !$2; }
        | VAR
        | CONST
        ;
%%

void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}

int main () {
    yyparse ();
}
