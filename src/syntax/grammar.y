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
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		$$=node;
		
	}
	|stmt_delimiter 
	{
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}

	|stmt_delimiter stmt 
	{
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		$$=node;
	}

	|stmts stmt_delimiter stmt 
	{
		AstNode_Add($1,$3);
		$$=$1;
	}
	|stmts stmt_delimiter {$$=$1;}
	;

block:stmts{$$=$1;}
	|
	{
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
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
		GrString* gs=GrString_GcNewFlag(yl_cur_string(),GRGC_HEAP_STATIC);
		if(gs==NULL) return AST_MEM_FAILED;
		
		AstObject* node=AstVar_New(gs);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	;
upper_id:tDOLLAR tID
	{
		GrString* gs=GrString_GcNewFlag(yl_cur_string(),GRGC_HEAP_STATIC);
		if(gs==NULL) return AST_MEM_FAILED;
		
		AstObject* node=AstUpperVar_New(gs);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	;



expr_list:expr_list_pre {$$=$1;}
	|expr_list_pre tCOMMA{$$=$1;}
	;

expr_list_pre:expr 
	{
		AstObject* node=AstNode_New(&Ast_Type_Normal);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		$$=node;
	}
	|expr_list_pre tCOMMA expr 
	{
		AstNode_Add($1,$3);
		$$=$1;
	}
	;


array:l_sb expr_list r_sb 
	{
		AstObject* node=AstNode_New(&Ast_Type_Array);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$2);
		$$=node;
	}
	|l_sb r_sb 
	{
		AstObject* node=AstNode_New(&Ast_Type_Array);
		if(node==NULL) return AST_MEM_FAILED;
		AstObject* expr=AstNode_New(&Ast_Type_Normal);
		if(expr==NULL) return AST_MEM_FAILED;
		
		AstNode_Add(node,expr);
		$$=node;
	}

l_sb :tL_SB{yl_ignore_newline();};
r_sb:tR_SB{yl_restore_newline();};
l_rb:tL_RB{yl_ignore_newline();};
r_rb:tR_RB{yl_restore_newline();};
		   
primary_expr: literal {$$=$1;}
	|tL_RB expr tR_RB {$$=$2;}  /* '(' expr ')' */
	|identifier{$$=$1;}
	|array {$$=$1;}
	|upper_id{$$=$1;}
	;

postfix_expr: primary_expr{$$=$1;}
	|postfix_expr l_sb expr r_sb 
	{
		AstObject* node=AstNode_New(&Ast_Type_Square);
		if(node==NULL) return -1;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	|postfix_expr l_rb expr_list r_rb
	{
		AstObject* node=AstNode_New(&Ast_Type_Call);
		if(node==NULL) return -1;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
		
	}
	|postfix_expr l_rb r_rb 
	{
		AstObject* node=AstNode_New(&Ast_Type_Call);
		if(node==NULL) return -1;
		AstObject* expr_list=AstNode_New(&Ast_Type_Normal);
		if(expr_list==NULL) return -1;
		
		AstNode_Add(node,$1);
		AstNode_Add(node,expr_list);
		$$=node;
	}
	;
symbols:postfix_expr{$$=$1;}

unary_expr:postfix_expr{$$=$1;}
	|unary_operator unary_expr 
	{  
		AstObject* node=AstNode_New($1);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$2);
		$$=node;
	}   
	;
unary_operator:tPLUS{$$=&Ast_Type_Positive;}
	|tMINUS{$$=&Ast_Type_Negative;}
	|tNEGATED{$$=&Ast_Type_Negated;}
	;

multiply_expr: unary_expr {$$=$1;}
	|multiply_expr multiply_operator unary_expr
	{
		AstObject* node=AstNode_New($2);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;
multiply_operator:tMUL{$$=&Ast_Type_Mul;}
	|tDIV {$$=&Ast_Type_Div;}
	|tMOD {$$=&Ast_Type_Mod;}
	;

additive_expr:multiply_expr{$$=$1;}
	|additive_expr additive_operator multiply_expr
	{
		AstObject* node=AstNode_New($2);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;
additive_operator:tPLUS {$$=&Ast_Type_Plus;}
	|tMINUS{$$=&Ast_Type_Minus;}
	;

shift_expr:additive_expr{}
	|shift_expr shift_operator additive_expr
	{
		AstObject* node=AstNode_New($2);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;
shift_operator:tLS{$$=&Ast_Type_LShift;}
	|tRS{$$=&Ast_Type_RShift;}
	;


bit_and_expr:shift_expr{$$=$1;}
	|bit_and_expr tAND shift_expr{
		AstObject* node=AstNode_New(&Ast_Type_And);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;
bit_xor_expr:bit_and_expr{$$=$1;}
	|bit_xor_expr tXOR bit_and_expr
	{
		AstObject* node=AstNode_New(&Ast_Type_Xor);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;
bit_or_expr:bit_xor_expr{$$=$1;}
	|bit_or_expr tOR bit_xor_expr
	{
		AstObject* node=AstNode_New(&Ast_Type_Or);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;


relational_expr:bit_or_expr{$$=$1;} 
	|relational_expr relational_operator bit_or_expr
	{
		AstObject* node=AstNode_New($2);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;	

relational_operator:tLT{$$=&Ast_Type_Lt;}
	|tLE{$$=&Ast_Type_Le;}
	|tGE{$$=&Ast_Type_Ge;}
	|tGT{$$=&Ast_Type_Gt}
	;


equal_expr:relational_expr{$$=$1;}
	|equal_expr equal_operator relational_expr
	{
		AstObject* node=AstNode_New($2);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;
equal_operator:tEQ{$$=&Ast_Type_Eq;}
	|tNE {$$=&Ast_Type_Ne;}
	;



logic_not_expr:equal_expr{$$=$1;}
	|kNOT logic_not_expr
	{
		AstObject* node=AstNode_New(&Ast_Type_Logic_Not);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$2);
		$$=node;
		
	}
	;
logic_and_expr:logic_not_expr{$$=$1;}
	|logic_and_expr kAND logic_not_expr
	{
		AstObject* node=AstNode_New(&Ast_Type_Logic_And);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
	}
	;	
logic_or_expr:logic_and_expr{$$=$1;}
	|logic_or_expr kOR logic_and_expr
	{
		AstObject* node=AstNode_New(&Ast_Type_Logic_Or);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$1);
		AstNode_Add(node,$3);
		$$=node;
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
		AstObject* node=AstNode_New(&Ast_Type_Print);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,$2);
		$$=node;
	}
	|kPRINT
	{
		AstObject* node=AstNode_New(&Ast_Type_Print);
		if(node==NULL) return AST_MEM_FAILED;
		AstObject* expr_list=AstNode_New(&Ast_Type_Normal);
		if(expr_list==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,expr_list);
		$$=node;
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
	
