%{
#include<assert.h>
#include"yylex.h"
#include"ast_nodes.h"
#include"parser.h"
#include<object/gr_int.h>
#include<object/gr_string.h>
#include<memory/gc.h>
/* I don't want to use void* for default symbol type
 * but if not,i will give every symbol a type,
 * so awfull 
 * FIXME wish someday, someone tell me  how to give part of symbols 
 * a default type 
 */
#define YYSTYPE void*  
%}



/* codger token follow enum REDY_TOKEN from lexical/token.h */

%token tUNKOWN tERR 
/*base type */
%token tINTEGER tLONG tFLAOT tSTRING tID
/*delimiter*/
%token tDOLLAR tCOMMA tPERIOD tL_RB tR_RB tL_SB tR_SB  
/*expr operator and assign */
%token tASSIGN tAMUL tADIV tAMOD tAPLUS tAMINUS tALS tARS tAAND tAOR tAXOR
/* expr operator */
%token tMUL  tDIV  tMOD tPLUS tMINUS tLS tRS tAND tOR tXOR tNEGATED
%token tLT tLE tNE tEQ tGE tGT
/* sentence break*/
%token tSEMI tNEWLINE 

/* keyword */
%token kAND kAS kAttr kBREAK kCATCH kCLASS kCONTINUE kDO kELIF 
%token kELSE kEND kFINALLY kFOR kFROM kFUNC kIF  kIMPORT kIN 
%token kINHRIT kNOT kOR kPRINT kRETURN kTHEN kTO KTRY kVFUNC kWHILE 
%token kTRUE kFALSE 


%start AstTree
%%

AstTree : block{parser_set_root($1);} ;

stmts:stmt 
	{
	}
	|stmt_delimiter 
	{
	}

	|stmt_delimiter stmt 
	{
	}

	|stmts stmt_delimiter stmt 
	{
	}
	|stmts stmt_delimiter {$$=$1;}
	;

block:stmts{$$=$1;}
	|
	{
	}
	;

stmt:stmt_expr {$$=$1;}
	|stmt_assign {$$=$1;}
	|stmt_print {$$=$1;}
	|stmt_while {$$=$1;}
	|stmt_if  {$$=$1;}
	|stmt_for {$$=$1;}
	|stmt_break{$$=$1;}
	|stmt_continue{$$=$1;}
	|stmt_func{$$=$1;}
	|stmt_return{$$=$1;}
	;

stmt_delimiter:tNEWLINE| tSEMI;


literal: tINTEGER 
	{
		GrInt* gi=GrInt_GcNewFromStrFlag(yl_cur_string(),GRGC_HEAP_STATIC);
		if(gi==NULL) return AST_MEM_FAILED;
		AstObject* node=AstLiteral_New(I_TO_GR(gi));
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	| tLONG
	{
	}
	| tFLAOT
	{
	}
	| tSTRING
	{
		GrString* gs=GrGc_AllocStatic(GrString,&Gr_Type_String);
		if(gs==NULL) return AST_MEM_FAILED;
		if(GrString_InitEscWithQuote(gs,yl_cur_string())<0)
			return AST_MEM_FAILED;
		
		AstObject* node=AstLiteral_New(S_TO_GR(gs));
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	| kFALSE
	{
		AstObject* node=AstLiteral_New(I_TO_GR(Gr_False));
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	| kTRUE
	{
		AstObject* node=AstLiteral_New(I_TO_GR(Gr_True));
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	;
identifier:tID
	{
	}
	;
global_id:tDOLLAR tID
	{
	}
	;



expr_list:expr_list_pre {$$=$1;}
	|expr_list_pre tCOMMA{$$=$1;}
	;

expr_list_pre:expr 
	{
	}
	|expr_list_pre tCOMMA expr 
	{
	}
	;


array:l_sb expr_list r_sb 
	{
	}
	|l_sb r_sb 
	{
	}

l_sb :tL_SB{yl_ignore_newline();};
r_sb:tR_SB{yl_restore_newline();};
l_rb:tL_RB{yl_ignore_newline();};
r_rb:tR_RB{yl_restore_newline();};
		   
primary_expr: literal {$$=$1;}
	|tL_RB expr tR_RB {$$=$2;}  /* '(' expr ')' */
	|identifier{$$=$1;}
	|array {$$=$1;}
	|global_id{$$=$1;}
	;

postfix_expr: primary_expr{$$=$1;}
	|postfix_expr l_sb expr r_sb 
	{
	}
	|postfix_expr l_rb expr_list r_rb
	{
	}
	|postfix_expr l_rb r_rb 
	{
	}
	;
symbols:postfix_expr{$$=$1;}

unary_expr:postfix_expr{$$=$1;}
	|unary_operator unary_expr 
	{  
	}   
	;
unary_operator:tPLUS{}
	|tMINUS{}
	|tNEGATED{}
	;

multiply_expr: unary_expr {$$=$1;}
	|multiply_expr multiply_operator unary_expr
	{
	}
	;
multiply_operator:tMUL{}
	|tDIV {}
	|tMOD {}
	;

additive_expr:multiply_expr{$$=$1;}
	|additive_expr additive_operator multiply_expr
	{
	}
	;
additive_operator:tPLUS {}
	|tMINUS{}
	;

shift_expr:additive_expr{}
	|shift_expr shift_operator additive_expr
	{
	}
	;
shift_operator:tLS{}
	|tRS{}
	;


bit_and_expr:shift_expr{$$=$1;}
	|bit_and_expr tAND shift_expr{
	}
	;
bit_xor_expr:bit_and_expr{$$=$1;}
	|bit_xor_expr tXOR bit_and_expr
	{
	}
	;
bit_or_expr:bit_xor_expr{$$=$1;}
	|bit_or_expr tOR bit_xor_expr
	{
	}
	;


relational_expr:bit_or_expr{$$=$1;} 
	|relational_expr relational_operator bit_or_expr
	{
	}
	;	

relational_operator:tLT{}
	|tLE{}
	|tGE{}
	|tGT{}
	;


equal_expr:relational_expr{$$=$1;}
	|equal_expr equal_operator relational_expr
	{
	}
	;
equal_operator:tEQ{}
	|tNE {}
	;



logic_not_expr:equal_expr{$$=$1;}
	|kNOT logic_not_expr
	{
	}
	;
logic_and_expr:logic_not_expr{$$=$1;}
	|logic_and_expr kAND logic_not_expr
	{
	}
	;	
logic_or_expr:logic_and_expr{$$=$1;}
	|logic_or_expr kOR logic_and_expr
	{
	}
	;

expr :logic_or_expr{$$=$1;} ;

stmt_expr:expr 
	{
	} 
	;

stmt_assign: symbols tASSIGN expr
	{
		
	}
	;

stmt_print:kPRINT expr_list
	{
	}
	;
stmt_while: kWHILE  expr while_delimter block kEND 
	{
	}
	;
while_delimter: tNEWLINE |kDO |tSEMI ;	


stmt_if:if_pre kEND {$$=$1;}
	|if_pre kELSE if_delimter block kEND
	{
	}
	;

if_pre:kIF expr if_delimter block
	{
	}
	|if_pre  kELIF expr if_delimter block
	{
	}
	;

if_delimter:tNEWLINE|kTHEN|tSEMI;
	

stmt_for: kFOR symbols kIN expr for_delimter block kEND
	{
	}
for_delimter: tNEWLINE|kDO|tSEMI;

stmt_break: kBREAK
	{
	}
	;
stmt_continue: kCONTINUE
	{
	}
	;
stmt_return: kRETURN expr
	{
	}
	|kRETURN
	{
	}
	;



stmt_func:func_declare{$$=$1;};


func_declare:kFUNC identifier l_rb args_list r_rb func_delimeter block kEND 
	{
	}
	;


func_delimeter:tNEWLINE|tCOMMA;


args_list:arg
	{
	}
	|args_list tCOMMA arg 
	{
	}
	|
	{
	}
	;
		 
arg:simply_arg{$$=$1;}
	|default_arg{$$=$1;}
	|many_args{$$=$1;}
	;
 
simply_arg:identifier
	{
		
	}
	;
default_arg:identifier tASSIGN expr 
	{
	}
	;

many_args:tMUL identifier 
	{
	}
	|tMUL
	{
	}
	;
	
