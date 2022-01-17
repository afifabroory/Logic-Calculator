%option caseless

ID			[a-z][a-z0-9_]*

CONJ		"&"|"*"|"and"

DISJ 		"|"|"+"|"or"

NEG			"~"|"!"|"not"

EQUV		"="

IMP 		"->"|">"
IF 			"if"
THEN		"then"

TRUE 		"true"
TRUEALT		"1"
FALSE		"false"
FALSEALT	 "0"

PARENO		"("
PARENC 		")"
CURLYO		"{"
CURLYC		"}"
BRACKO		"["
BRACKC		"]"

OGROUP		"("|"{"|"["	
CGROUP 		")"|"}"|"]"	

DIGIT			[0-9]+
WHITESPACE 		.|[ \t\n]

%%

{CONJ}				printf("An Conjunction: %s\n", yytext);

{DISJ}				printf("An Disjunction: %s\n", yytext);

{NEG}				printf("An Negation: %s\n", yytext);

{EQUV}				printf("An Equivalence: %s\n", yytext);

{IMP}				printf("An Implication: %s\n", yytext);

{IF}				printf("An If: %s\n", yytext);

{THEN}				printf("An Then: %s\n", yytext);

{OGROUP} 			printf("An open grouping: %s\n", yytext);

{CGROUP}			printf("An close grouping: %s\n", yytext); 

{TRUE}				printf("An true: %s\n", yytext);

{FALSE}				printf("An false: %s\n", yytext);

{ID}                printf("An Identifier: %s\n", yytext);

{TRUEALT}			printf("An true: %s\n", yytext);

{FALSEALT}			printf("An false: %s\n", yytext);

{DIGIT} 			/* We should warn user */

{WHITESPACE} 		/* Ignore */

%%

int yywrap(){}
int main() {
	yylex();
	return 0;
}
