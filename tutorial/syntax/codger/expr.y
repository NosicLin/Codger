%{
#include<stdio.h>
#include<ctype.h>
int reg[26];
%}

%start list
%token digit  letter

%%

list: list start '\n' 
	| list error '\n' 
	| start '\n'
	;

start: expr {printf("\t%d\n\n",$1);}
	| assign
	;

number:number digit {$$=$1*10+$2;}
	  |digit 	
		;

primary_expr: '(' expr ')' {$$=$2;}
			| number	
			| letter {$$=reg[$1];}
			;

unary_expr: primary_expr 
		  | '-' primary_expr {$$=-$2;}
		  ;

mul_expr:unary_expr {$$=$1;}
		| mul_expr '*' unary_expr {$$=$1*$3;}
		| mul_expr '/' unary_expr {$$=$1/$3;}
		;

add_expr:mul_expr {$$=$1;}
		| add_expr '+' mul_expr {$$=$1+$3;}
		| add_expr '-' mul_expr {$$=$1-$3;}
		;

assign: letter '=' add_expr {reg[$1]=$3;}
		;

expr: add_expr 
	;

%%
int yylex(int a)
{
	int ch=' ';
	while(isspace(ch)&&ch!='\n')
		 ch=fgetc(stdin);

	if(isdigit(ch))
	{
		yylval=ch-'0';
		return digit;
	}
	if(isalpha(ch))
	{
		yylval=ch-'a';
		return letter;
	}
	return ch;
}
int main()
{
	return yyparse();
}
int yyerror(char* s)
{
	fprintf(stderr,"%s\n",s);
}

