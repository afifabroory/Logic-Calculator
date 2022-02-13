%{
#include "ast.h"
#include "y.tab.h"
#include "symbol_table.h"
%}

%option caseless
%option noyywrap

VAR                 [a-z][a-z0-9_]*

CONJ                "&"|"*"|"and"|"dan"

DISJ                "|"|"+"|"or"|"atau"

NEG                 "~"|"!"|"not"|"bukan"

IMP                 "->"|"=>"
IF                  "if"|"jika"
THEN                "then"|"maka"

EQUV                "="|"<->"|"<=>"

TRUE                "true"|"benar"|"1"
FALSE               "false"|"salah"|"0"

INVALID_TRUTH       "1"[a-z]+|"0"[a-z]+

OGROUP              "("|"{"|"["
CGROUP              ")"|"}"|"]"

DIGIT               [0-9]+
WHITESPACE          [ \t\n]
IGNORE_TOKEN        .

%%

{CONJ}              { return CONJ; }

{DISJ}              { return DISJ; }

{NEG}               { return NEG; }

{IMP}               { return IMP; }

{EQUV}              { return EQUV; }

{IF}                /*{ return IF; }*/

{THEN}              /*{ return THEN; }*/

{OGROUP}            { return '('; }

{CGROUP}            { return ')'; }

{INVALID_TRUTH}     /* Ignore */

{TRUE}              { yylval.t_val = true; return CONST; }

{FALSE}             { yylval.t_val = false; return CONST; }

{VAR}               { 
        if (directlyEval) directlyEval = false;
        char *name = strdup(yytext);
        yylval.id = name;
        add_var(name);

        return VAR; 
    }

{DIGIT}             /* Ignore */
{WHITESPACE}        /* Ignore */
{IGNORE_TOKEN}      /* Ignore */

%%
