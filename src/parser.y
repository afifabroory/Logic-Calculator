%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern void yy_scan_string(const char *str);
void yyerror(int *results, const char* s);
%}

%parse-param {int *results}

%define parse.error verbose

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
%nonassoc IF THEN
%left CONJ DISJ
%nonassoc NEG

%%
Form    : Binary                { *results = $1; }
        ;

Binary  : Binary DISJ Binary    { $$ = $1 || $3; }
        | Binary CONJ Binary    { $$ = $1 && $3; }
        | Binary EQUV Binary    { $$ = (!$1 || $3) && ($1 || !$3); }
        | Imply
        | Atomic
        ;        

Imply   : Binary IMP Binary     { $$ = !$1 || $3; }
        | IF Binary THEN Binary { $$ = !$2 || $4; }
        | Binary IF Binary      { $$ = !$3 || $1; }
        ;

Atomic  : NEG Atomic            { $$ = !$2; }
        |'(' Binary ')'         { $$ = $2; }
        | VAR
        | CONST
        ;
%%

void yyerror(int *results, char const *s) {
  fprintf(stderr, "%s\n", s);
}
