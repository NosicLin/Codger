%{
#include<assert.h>
#include"yylex.h"
#include"ast_nodes.h"
#include"parser.h"
#include<rtype/rtype.h>
#include<rtype/bt_string.h>
#include<rtype/bt_int.c>
#include<rtype/bt_float.h>
#include<rtype/bt_long.h>
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
%token tCOMMA tPERIOD tL_RB tR_RB tL_SB tR_SB  
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

AstTree : pretty_stmts{parser_set_root($1);}
;
pretty_stmts: stmts {$$=$1;}
	|stmts stmt
	{
		ast_node_add($1,$2);
		$$=$1;
	}
	|stmt
	{
		AstObject* node=ast_node_new(&node_stmts);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		$$=node;
	}
	| 
	{
		AstObject* node=ast_node_new(&node_stmts);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	;		

stmts: pretty_stmt
	 {
		AstObject* node=ast_node_new(&node_stmts);
		if(node==NULL) return AST_MEM_FAILED;
		if($1!=NULL) ast_node_add(node,$1);
		$$=node;
	 }
	 | stmts pretty_stmt
	 {
		if($2!=NULL) ast_node_add($1,$2);
		$$=$1;
	 }
	;

stmt_delimiter:tNEWLINE| tSEMI


pretty_stmt: stmt stmt_delimiter {$$=$1;}
		   |pseudo_stmt {$$=NULL;}

pseudo_stmt: stmt_delimiter {$$=NULL;}

stmt:stmt_expr {$$=$1;}
	|stmt_assign {$$=$1;}
	|stmt_print {$$=$1;}
	|stmt_while {$$=$1;}
	|stmt_if  {$$=$1;}
	|stmt_for {$$=$1;}
	;
literal: tINTEGER 
	{
		BtInt* bi=btint_from_str(yl_cur_string());
		if(bi==NULL) return AST_MEM_FAILED;
		AstObject* node=ast_create_literal(I_TO_R(bi));
		if(node==NULL)
		{
			robject_release(I_TO_R(bi));
			return AST_MEM_FAILED;
		}
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
	}
	| kFALSE
	{
	}
	| kTRUE
	{
	}
	;
identifier:tID
	{
	}
	;
expr_list: expr 
	{
		AstObject* node=ast_node_new(&node_normal);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		$$=node;
	}
	| expr_list tCOMMA expr
	{
		ast_node_add($1,$3);
		$$=$1;
	}
	| 
	{
		AstObject* node=ast_node_new(&node_normal);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	;

array:tL_SB expr_list tR_SB
	{
	}
		
primary_expr: literal {$$=$1;}
	|tL_RB expr tR_RB {$$=$2;}  /* '(' expr ')' */
	|identifier{$$=$1;}
	|array {$$=$1;}
	;

postfix_expr: primary_expr{$$=$1;}
	|postfix_expr tL_SB expr tR_SB
	{
	}
	;
symbols:postfix_expr{$$=$1;}

unary_expr:postfix_expr{$$=$1;}
	|unary_operator unary_expr 
	{  
		AstObject* node=ast_node_new($1);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		$$=node;
	}   
	;
unary_operator:tPLUS{$$=&node_positive;}
	|tMINUS{$$=&node_negative;}
	|tNEGATED{$$=&node_negated;}
	;

multiply_expr: unary_expr {$$=$1;}
	|multiply_expr multiply_operator unary_expr
	{
		AstObject* node=ast_node_new($2);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;
multiply_operator:tMUL{$$=&node_mul;}
	|tDIV {$$=&node_div;}
	|tMOD {$$=&node_mod;}
	;

additive_expr:multiply_expr{$$=$1;}
	|additive_expr additive_operator multiply_expr
	{
		AstObject* node=ast_node_new($2);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;
additive_operator:tPLUS {$$=&node_plus;}
	|tMINUS{$$=&node_minus;}
	;

shift_expr:additive_expr{$$=$1;}
	|shift_expr shift_operator additive_expr
	{
		AstObject* node=ast_node_new($2);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;
shift_operator:tLS{$$=&node_lshift;}
	|tRS{$$=&node_rshift;}
	;


bit_and_expr:shift_expr{$$=$1;}
	|bit_and_expr tAND shift_expr{
		AstObject* node=ast_node_new(&node_and);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;
bit_xor_expr:bit_and_expr{$$=$1;}
	|bit_xor_expr tXOR bit_and_expr
	{
		AstObject* node=ast_node_new(&node_xor);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;
bit_or_expr:bit_xor_expr{$$=$1;}
	|bit_or_expr tOR bit_xor_expr
	{
		AstObject* node=ast_node_new(&node_or);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;


relational_expr:bit_or_expr{$$=$1;} 
	|relational_expr relational_operator bit_or_expr
	;	
relational_operator:tLE{$$=&node_normal;}
	|tLT{$$=&node_normal;}
	|tGE{$$=&node_normal;}
	|tGT{$$=&node_normal;}
	;


equal_expr:relational_expr{$$=$1;}
	|equal_expr equal_operator relational_expr
	;
equal_operator:tEQ{$$=&node_normal;}
	|tNE {$$=&node_normal;}
	;



logic_not_expr:equal_expr{$$=$1;}
	|kNOT logic_not_expr
	;
logic_and_expr:logic_not_expr{$$=$1;}
	|logic_and_expr kAND logic_not_expr
	;	
logic_or_expr:logic_and_expr{$$=$1;}
	|logic_or_expr kOR logic_and_expr
	;
expr :logic_or_expr{$$=$1;}
	;

stmt_expr:expr {$$=$1;}
		 ;

stmt_assign: symbols tASSIGN expr
	{
	}
	;

stmt_print:kPRINT expr_list
	{
		AstObject* node=ast_node_new(&node_print);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		$$=node;
	}
	;
stmt_while: kWHILE  expr while_delimter pretty_stmts kEND 
	{
	}
	;
while_delimter: tNEWLINE |kDO |tSEMI ;	


stmt_if:if_pre kEND {$$=$1;}
	|if_pre else_part kEND
	{
	}
	;

if_pre:if_part 
	{
	}
	|if_pre elif_part
	{
	}
	;
if_part: kIF expr if_delimter pretty_stmts 
	{
	}
	;
elif_part: kELIF expr if_delimter pretty_stmts
	{
	}
	;
else_part: kELSE if_delimter pretty_stmts
	{
	}
	;

if_delimter:tNEWLINE|kTHEN|tSEMI;
	
stmt_for: kFOR symbols kIN expr for_delimter pretty_stmts kEND
	{
	}
for_delimter: tNEWLINE|kDO|tSEMI;
















