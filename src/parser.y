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
Form    : Binary EOL            {  printf("Result: %d\n", $1); }
        ;

Binary  : Binary DISJ Binary    { $$ = $1 || $3; }
        | Binary CONJ Binary    { $$ = $1 && $3; }
        | Binary EQUV Binary    { $$ = (!$1 || $3) && ($1 || !$3); }
        | Imply
        | Atomic
        ;        

Imply   : Binary IMP Atomic     { $$ = !$1 || $3; }
        | IF Binary THEN Atomic { $$ = !$2 || $4; }
        | Binary IF Atomic      { $$ = !$3 || $1; }
        ;

Atomic  : NEG Atomic            { $$ = !$2; }
        |'(' Binary ')'         { $$ = $2; }
        | VAR
        | CONST
        ;
%%

void yyerror(char const *s) {
  fprintf(stderr, "%s\n", s);
}

int main() {
    yyparse();
}
