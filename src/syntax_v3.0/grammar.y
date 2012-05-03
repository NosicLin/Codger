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
		AstObject* node=ast_node_new(&node_stmts);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		$$=node;
	}
	|stmt_delimiter 
	{
		AstObject* node=ast_node_new(&node_stmts);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}

	|stmt_delimiter stmt 
	{
		AstObject* node=ast_node_new(&node_stmts);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		$$=node;
	}

	|stmts stmt_delimiter stmt 
	{
		ast_node_add($1,$3);
		$$=$1;
	}
	|stmts stmt_delimiter {$$=$1;}
	;

block:stmts{$$=$1;}
	|
	{
		AstObject* node=ast_node_new(&node_stmts);
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
		BtInt* bi=btint_from_str(yl_cur_string());
		if(bi==NULL) return AST_MEM_FAILED;
		AstObject* node=ast_create_literal(I_TO_R(bi));
		robject_release(I_TO_R(bi));
		if(node==NULL)
		{
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
		AstObject* node=ast_create_literal(B_TO_R(ObjectFalse));
		if(node==NULL)
		{
			return AST_MEM_FAILED;
		}
		$$=node;
	}
	| kTRUE
	{
		AstObject* node=ast_create_literal(B_TO_R(ObjectTrue));
		if(node==NULL)
		{
			return AST_MEM_FAILED;
		}
		$$=node;
	}
	;
identifier:tID
	{
	}
	;
global_id:tDOLLAR tID
	{
		BtString* symbol=btstring_create_no_esc(yl_cur_string());
		if(symbol==NULL) return AST_MEM_FAILED;
		AstObject* node=ast_create_global(symbol);
		robject_release(S_TO_R(symbol));
		if(node==NULL)
		{
			return AST_MEM_FAILED;
		}
		$$=node;
	}
	;



expr_list:expr_list_pre {$$=$1;}
	|expr_list_pre tCOMMA{$$=$1;}
	;

expr_list_pre:expr 
	{
		AstObject* node=ast_node_new(&node_normal);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		$$=node;
	}
	|expr_list_pre tCOMMA expr 
	{
		ast_node_add($1,$3);
		$$=$1;
	}
	;


array:l_sb expr_list r_sb 
	{
		AstObject* node=ast_node_new(&node_array);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		$$=node;
	}
	|l_sb r_sb 
	{
		AstObject* node=ast_node_new(&node_array);
		if(node==NULL) return AST_MEM_FAILED;
		AstObject* sub_node=ast_node_new(&node_normal);
		if(sub_node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,sub_node);
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
	|global_id{$$=$1;}
	;

postfix_expr: primary_expr{$$=$1;}
	|postfix_expr l_sb expr r_sb 
	{
		AstObject* node=ast_node_new(&node_square);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	|postfix_expr l_rb expr_list r_rb
	{
		AstObject* node=ast_node_new(&node_call);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	|postfix_expr l_rb r_rb 
	{
		AstObject* node=ast_node_new(&node_call);
		AstObject* sub_node=ast_node_new(&node_normal);
		if(node==NULL||sub_node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,sub_node);
		$$=node;
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
	{
		AstObject* node=ast_node_new($2);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;	

relational_operator:tLT{$$=&node_lt;}
	|tLE{$$=&node_le;}
	|tGE{$$=&node_ge;}
	|tGT{$$=&node_gt;}
	;


equal_expr:relational_expr{$$=$1;}
	|equal_expr equal_operator relational_expr
	{
		AstObject* node=ast_node_new($2);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;
equal_operator:tEQ{$$=&node_eq;}
	|tNE {$$=&node_ne;}
	;



logic_not_expr:equal_expr{$$=$1;}
	|kNOT logic_not_expr
	{
		AstObject* node=ast_node_new(&node_logic_not);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		$$=node;
	}
	;
logic_and_expr:logic_not_expr{$$=$1;}
	|logic_and_expr kAND logic_not_expr
	{
		AstObject* node=ast_node_new(&node_logic_and);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;	
logic_or_expr:logic_and_expr{$$=$1;}
	|logic_or_expr kOR logic_and_expr
	{
		AstObject* node=ast_node_new(&node_logic_or);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;

expr :logic_or_expr{$$=$1;} ;

stmt_expr:expr 
	{
		AstObject* node= ast_node_new(&node_expr);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		$$=node;
	} 
	;

stmt_assign: symbols tASSIGN expr
	{
		if(!ast_check_can_assign($1))
		{	
			yyerror("Node Can'nt Assign");
			return -1;
		}
		AstObject* node=ast_node_new(&node_assign);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
		
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
stmt_while: kWHILE  expr while_delimter block kEND 
	{
		AstObject* node=ast_node_new(&node_while);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		ast_node_add(node,$4);
		$$=node;
	}
	;
while_delimter: tNEWLINE |kDO |tSEMI ;	


stmt_if:if_pre kEND {$$=$1;}
	|if_pre kELSE if_delimter block kEND
	{
		AstObject* sub_node=ast_node_new(&node_else);
		if(sub_node==NULL) return AST_MEM_FAILED;
		ast_node_add($1,sub_node);  /* make sure add sequence?*/
		ast_node_add(sub_node,$4);
		$$=$1;
	}
	;

if_pre:kIF expr if_delimter block
	{
		AstObject* node=ast_node_new(&node_if);
		if(node==NULL) return AST_MEM_FAILED;
		AstObject* sub_node=ast_node_new(&node_if_elif);
		if(sub_node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,sub_node); /* make sure add sequence? */
		ast_node_add(sub_node,$2);
		ast_node_add(sub_node,$4);
		$$=node;
	}
	|if_pre  kELIF expr if_delimter block
	{
		AstObject* sub_node=ast_node_new(&node_if_elif);
		if(sub_node==NULL) return AST_MEM_FAILED;
		ast_node_add($1,sub_node); /* make sure add sequence? */

		ast_node_add(sub_node,$3);
		ast_node_add(sub_node,$5);
		$$=$1;
	}
	;

if_delimter:tNEWLINE|kTHEN|tSEMI;
	

stmt_for: kFOR symbols kIN expr for_delimter block kEND
	{
		AstObject* node=ast_node_new(&node_for);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		ast_node_add(node,$4);
		ast_node_add(node,$6);
		$$=node;
	}
for_delimter: tNEWLINE|kDO|tSEMI;

stmt_break: kBREAK
	{
		AstObject* node=ast_node_new(&node_break);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	;
stmt_continue: kCONTINUE
	{
		AstObject* node=ast_node_new(&node_continue);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	;
stmt_return: kRETURN expr
	{
		AstObject* node=ast_node_new(&node_return);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		$$=node;
	}
	|kRETURN
	{
		AstObject* node=ast_node_new(&node_return);
		if(node==NULL) return AST_MEM_FAILED;
		$$=node;
	}
	;



stmt_func:func_declare{$$=$1;};


func_declare:kFUNC identifier l_rb args_list r_rb func_delimeter block kEND 
	{
		AstObject* node=ast_node_new(&node_func);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$2);
		ast_node_add(node,$4);
		ast_node_add(node,$7);
		$$=node;
	}
	;


func_delimeter:tNEWLINE|tCOMMA;


args_list:arg
	{
		AstObject* node=ast_node_new(&node_normal);
		if(node==NULL) return AST_MEM_FAILED;
		ast_node_add(node,$1);
		$$=node;
	}
	|args_list tCOMMA arg 
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
		 
arg:simply_arg{$$=$1;}
	|default_arg{$$=$1;}
	|many_args{$$=$1;}
	;
 
simply_arg:identifier
	{
		
		BtString* name=AST_TO_VAR($1)->v_symbol;
		AstObject* node=ast_create_arg(ARG_SIMPLY,name);
		if(node==NULL)
		{
			return AST_MEM_FAILED;
		}
		ast_node_add(node,$1);
		$$=node;
	}
	;
default_arg:identifier tASSIGN expr 
	{
		BtString* name=AST_TO_VAR($1)->v_symbol;
		AstObject* node=ast_create_arg(ARG_DEFALUT_VALUE,name);
		if(node==NULL)
		{
			return AST_MEM_FAILED;
		}
		ast_node_add(node,$1);
		ast_node_add(node,$3);
		$$=node;
	}
	;

many_args:tMUL identifier 
	{
		BtString* name=AST_TO_VAR($2)->v_symbol;
		AstObject* node=ast_create_arg(ARG_MANY,name);
		if(node==NULL)
		{
			return AST_MEM_FAILED;
		}
		ast_node_add(node,$2);
		$$=node;
	}
	|tMUL
	{
		BtString* arg_list=btstring_create_no_esc("@arg_list");
		if(arg_list==NULL) return AST_MEM_FAILED;

		AstObject* node=ast_create_arg(ARG_MANY,arg_list);
		if(node==NULL)
		{
			robject_release(S_TO_R(arg_list));
			return AST_MEM_FAILED;
		}
		AstObject* sub_node=ast_create_var(arg_list);
		robject_release(S_TO_R(arg_list));
		if(sub_node==NULL)
		{
			return AST_MEM_FAILED;
		}
		ast_node_add(node,sub_node);
		$$=node;
	}
	;
	









