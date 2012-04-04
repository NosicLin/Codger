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
#define YYSTYPE  AstObject* 
%}

/* redy token follow enum REDY_TOKEN from lexical/token.h */

%token tUNKOWN tERR 
/*base type */
%token tINTEGER tLONG tFLAOT tSTRING tID
/*delimiter*/
%token tCOMMA tPERIOD tL_RB tR_RB tL_SB tR_SB  
/*expr operator and assign */
%token tASSIGN tAMUL tADIV tAMOD tAPLUS tAMINUS tALS tARS tAAND tAOR tAXOR
/* expr operator */
%token tMUL  tDIV  tMOD tPLUS tMINUS tLS tRS tAND tOR tXOR tNegated 
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
		AstNodeStmts* stmts=AST_TO_STMTS($1);
		assert($2);
		ast_stmts_add(stmts,$2);
		$$=STMTS_TO_AST(stmts);
	}
	|stmt
	{
		AstNodeStmts* stmts=ast_create_stmts();
		ast_addto_pending(STMTS_TO_AST(stmts));
		ast_stmts_add(stmts,$1);
		$$=STMTS_TO_AST(stmts);
	}
	| 
	{
		AstNodeStmts* stmts=ast_create_stmts();
		ast_addto_pending(STMTS_TO_AST(stmts));
		$$=STMTS_TO_AST(stmts);
	}
	;		

stmts: pretty_stmt
	 {
		AstNodeStmts* stmts=ast_create_stmts();
		ast_addto_pending(STMTS_TO_AST(stmts));
		if($1!=NULL)
		{
			ast_stmts_add(stmts,$1);
		}
		$$=STMTS_TO_AST(stmts);
	 }
	 | stmts pretty_stmt
	 {
		AstNodeStmts* stmts=AST_TO_STMTS($1);
		if($2!=NULL)
		{
			ast_stmts_add(stmts,$2);
		}
		$$=STMTS_TO_AST(stmts);
		
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
		
	 ;
literal: tINTEGER 
	{
		BtInt* bi=btint_from_str(yl_cur_string());
		AstNodeLiteral* t=ast_create_literal(I_TO_R(bi));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(I_TO_R(bi));
		$$=LITERAL_TO_AST(t); 
	}

	| tLONG
	{
		BtLong* bl=btlong_from_str(yl_cur_string());
		AstNodeLiteral* t=ast_create_literal(L_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(L_TO_R(bl));
		$$=LITERAL_TO_AST(t);
	}

	| tFLAOT
	{
		BtFloat* bf=btfloat_from_str(yl_cur_string());
		AstNodeLiteral* t=ast_create_literal(F_TO_R(bf));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(F_TO_R(bf));
		$$=LITERAL_TO_AST(t);
	}
	| tSTRING
	{
		BtString* bs=btstring_create(yl_cur_string());
		AstNodeLiteral* t=ast_create_literal(S_TO_R(bs));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(S_TO_R(bs));
		$$=LITERAL_TO_AST(t);
	}
	| kFALSE
	{
		BtBool* bl=btbool_create(0);
		AstNodeLiteral* node=ast_create_literal(B_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(node));
		robject_release(B_TO_R(bl));
		$$=LITERAL_TO_AST(node);
	}
	| kTRUE
	{
		BtBool* bl=btbool_create(1);
		AstNodeLiteral* node=ast_create_literal(B_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(node));
		robject_release(B_TO_R(bl));
		$$=LITERAL_TO_AST(node);
	}
	;
identifier:tID
	{
		BtString* bs=btstring_create_no_esc(yl_cur_string());
		AstNodeVar* node=ast_create_var(bs);
		ast_addto_pending(VAR_TO_AST(node));
		robject_release(S_TO_R(bs));
		$$=VAR_TO_AST(node);
	}
	;
expr_list: expr 
	{
		AstObject* node=ast_create_object();
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
		AstObject* node=ast_create_object();
		$$=node;
	}
	;

array:tL_SB expr tR_SB 

primary_expr: literal {$$=$1;}
	|tL_RB expr tR_RB {$$=$2;}  /* '(' expr ')' */
	|identifier{$$=$1}
	|array
	;

unary_expr:primary_expr{$$=$1;}
		  |tPLUS unary_expr 
	{  
		AstNodePositive* node=ast_create_positive($2);
		AstObject* ab=POSITIVE_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}   
	|tMINUS unary_expr
	{ 
		AstNodeNegative* node=ast_create_negative($2);
		AstObject* ab=NEGATIVE_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}   
	|tNegated unary_expr
	{  
		AstNodeNegated* node=ast_create_negated($2);
		AstObject* ab=NEGATED_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	} 
	;

multiply_expr: unary_expr{
			 $$=$1;
			}
	|multiply_expr tMUL unary_expr{
			AstNodeMul* t=ast_create_mul($1,$3);
			AstObject* ab=MUL_TO_AST(t);
			ast_addto_pending(ab);
			$$=ab;
	}
	| multiply_expr tDIV unary_expr{
			AstNodeDiv* t=ast_create_div($1,$3);
			AstObject* ab=DIV_TO_AST(t);
			ast_addto_pending(ab);
			$$=ab;
	}
	| multiply_expr tMOD unary_expr{
			AstNodeDiv* t=ast_create_mod($1,$3);
			AstObject* ab=MOD_TO_AST(t);
			ast_addto_pending(ab);
			$$=ab;
	}
;
additive_expr:multiply_expr{$$=$1;}
			 |additive_expr tPLUS multiply_expr{
		AstNodePlus* node=ast_create_plus($1,$3);
		AstObject* ab=PLUS_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	|additive_expr tMINUS multiply_expr{
		AstNodeMinus* node=ast_create_minus($1,$3);
		AstObject* ab=MINUS_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;
shift_expr:additive_expr{$$=$1;}
		  |shift_expr tLS additive_expr{   /*left shift*/
		AstNodeLShift* node=ast_create_lshift($1,$3);
		AstObject* ab=LSHIFT_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	|shift_expr tRS additive_expr{  /* right shift */
		AstNodeRShift* node=ast_create_rshift($1,$3);
		AstObject* ab=RSHIFT_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
;

bit_and_expr:shift_expr{$$=$1;}
	|bit_and_expr tAND shift_expr{
		AstNodeAnd* node=ast_create_and($1,$3);
		AstObject* ab=AND_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;
bit_xor_expr:bit_and_expr{$$=$1;}
	|bit_xor_expr tXOR bit_and_expr{
		AstNodeXor* node=ast_create_xor($1,$3);
		AstObject* ab=XOR_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;
bit_or_expr:bit_xor_expr{$$=$1;}
   |bit_or_expr tOR bit_xor_expr{
		AstNodeOr* node=ast_create_or($1,$3);
		AstObject* ab=OR_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;

relational_expr:bit_or_expr{$$=$1;} 
   |relational_expr tLT bit_or_expr{
		AstNodeLt* node =ast_create_lt($1,$3);
		AstObject* ab=LT_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	|relational_expr tLE bit_or_expr{
		AstNodeLe* node=ast_create_le($1,$3);
		AstObject* ab=LE_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	|relational_expr tGE bit_or_expr{
		AstNodeGe* node=ast_create_ge($1,$3);
		AstObject* ab=GE_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}	
	|relational_expr tGT bit_or_expr{
		AstNodeGt* node=ast_create_gt($1,$3);
		AstObject* ab=GT_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;

equal_expr:relational_expr{$$=$1;}
  |equal_expr tEQ relational_expr{
		AstNodeEq* node=ast_create_eq($1,$3);
		AstObject* ab=EQ_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	|equal_expr tNE relational_expr{
		AstNodeNe* node=ast_create_ne($1,$3);
		AstObject* ab=NE_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;
logic_not_expr:equal_expr{$$=$1;}
	|kNOT logic_not_expr{
		AstNodeLogicNot* node=ast_create_logic_not($2);
		AstObject* ab=LOGIC_NOT_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;
logic_and_expr:logic_not_expr{$$=$1;}
	|logic_and_expr kAND logic_not_expr{
		AstNodeLogicAnd* node=ast_create_logic_and($1,$3);
		AstObject* ab=LOGIC_AND_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;	
logic_or_expr:logic_and_expr{$$=$1;}
	|logic_or_expr kOR logic_and_expr{
		AstNodeLogicOr* node=ast_create_logic_or($1,$3);
		AstObject* ab=LOGIC_OR_TO_AST(node);
		ast_addto_pending(ab);
		$$=ab;
	}
	;
expr :logic_or_expr{$$=$1;}
	 ;

stmt_expr:expr {$$=$1;}
		 ;

stmt_assign:identifier tASSIGN expr
   {
		AstNodeAssign* node=ast_create_assign(AST_TO_VAR($1),$3);
		ast_addto_pending(ASSIGN_TO_AST(node));
		$$=ASSIGN_TO_AST(node);
	}
	;

stmt_print:kPRINT expr_list
	{
		AstNodePrint* node=ast_create_print($2);
		ast_addto_pending(PRINT_TO_AST(node));
		$$=PRINT_TO_AST(node);
	}
	;
stmt_while: kWHILE  expr while_delimter pretty_stmts kEND 
	{
		AstNodeWhile* node=ast_create_while($2,$4);
		ast_addto_pending(WHILE_TO_AST(node));
		$$=WHILE_TO_AST(node);
	}
	;
while_delimter: tNEWLINE
	|kDO
	|tSEMI
	;	


stmt_if:if_pre kEND {$$=$1;}
	|if_pre else_part kEND
	{
		ast_if_add(AST_TO_IF($1),AST_TO_IF_SUB($2));
		$$=$1;
	}
	;

if_pre:if_part 
	{
		AstNodeIf* node=ast_create_if();
		ast_addto_pending(IF_TO_AST(node));
		ast_if_add(node,AST_TO_IF_SUB($1));
		$$=IF_TO_AST(node);
	}
	|if_pre elif_part
	{
		ast_if_add(AST_TO_IF($1),AST_TO_IF_SUB($2));
		$$=$1;
	}
	;
if_part: kIF expr if_delimter pretty_stmts 
	{
		AstNodeIfSub* node=ast_create_if_sub($2,$4);
		ast_addto_pending(IF_SUB_TO_AST(node));
		$$=IF_SUB_TO_AST(node);
	}
	;
elif_part: kELIF expr if_delimter pretty_stmts
	{
		AstNodeIfSub* node=ast_create_if_sub($2,$4);
		ast_addto_pending(IF_SUB_TO_AST(node));
		$$=IF_SUB_TO_AST(node);
	}
	;
else_part: kELSE if_delimter pretty_stmts
	{
		AstNodeIfSub* node=ast_create_if_sub(NULL,$3);
		ast_addto_pending(IF_SUB_TO_AST(node));
		$$=IF_SUB_TO_AST(node);
	}
	;

if_delimter:tNEWLINE|kTHEN|tSEMI;
	

















