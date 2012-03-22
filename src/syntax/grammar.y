%{

#include"yylex.h"
#include"ast_nodes.h"
#include"parser.h"
#include<rtype/rtype.h>
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
%token kINHRIT kNOT kOR kPRINT kTHEN kTO KTRY kVFUNC kWHILE 
%token kTRUE kFALSE 

%start AstTree
%%

AstTree : stmts{parser_set_root($1);}
;

stmts: stmt 
	 {
		AstNodeStmts* stmts=ast_create_stmts();
		ast_addto_pending(STMTS_TO_AST(stmts));
		AstNodeStmt* node=AST_TO_STMT($1);
		ast_stmts_add(stmts,node);
		$$=STMTS_TO_AST(stmts);
	 }
	 | tNEWLINE
	 {
		AstNodeStmts* node=ast_create_stmts();
		ast_addto_pending(STMTS_TO_AST(node));
		$$=STMTS_TO_AST(node);
	 }
	 | stmts stmt  tNEWLINE
	 {
		AstNodeStmts* stmts=AST_TO_STMTS($1);
		AstNodeStmt* node=AST_TO_STMT($2);
		ast_stmts_add(stmts,node);
		$$=STMTS_TO_AST(stmts);
	 }
	 | stmts tNEWLINE 
;

stmt: stmt_expr
	{
	AstNodeStmt* node=ast_create_stmt($1);
	ast_addto_pending(STMT_TO_AST(node));
	$$=STMT_TO_AST(node);
	}
	 ;
literal: tINTEGER 
	   {
		BtInt* bi=bt_int_from_str(yl_cur_string());
	    AstNodeLiteral* t=ast_create_literal(I_TO_R(bi));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(I_TO_R(bi));
		$$=LITERAL_TO_AST(t); }

		| tLONG
		{
		BtLong* bl=bt_long_from_str(yl_cur_string());
	    AstNodeLiteral* t=ast_create_literal(L_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(L_TO_R(bl));
		$$=LITERAL_TO_AST(t);}

		| tFLAOT{
		BtFloat* bf=bt_float_from_str(yl_cur_string());
	   	AstNodeLiteral* t=ast_create_literal(F_TO_R(bf));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(F_TO_R(bf));
		$$=LITERAL_TO_AST(t);}
		| tSTRING{
		BtString* bs=bt_string_create(yl_cur_string());
	   	AstNodeLiteral* t=ast_create_literal(S_TO_R(bs));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(S_TO_R(bs));
		$$=LITERAL_TO_AST(t);}
		| kFALSE{
		BtBoolean* bl=bt_boolean_create(0);
		AstNodeLiteral* node=ast_create_literal(B_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(node));
   		robject_release(B_TO_R(bl));
		$$=LITERAL_TO_AST(node);
		}
		| kTRUE{
		BtBoolean* bl=bt_boolean_create(1);
		AstNodeLiteral* node=ast_create_literal(B_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(node));
   		robject_release(B_TO_R(bl));
		$$=LITERAL_TO_AST(node);
		}
;
primary_expr: literal {$$=$1;}
			|tL_RB expr tR_RB {$$=$2;}  /* '(' expr ')' */
			;
unary_expr:primary_expr{$$=$1;}
		  	|tPLUS unary_expr {    /*eg. +4*/
			AstNodePositive* node=ast_create_positive($2);
			AstObject* ab=POSITIVE_TO_AST(node);
			ast_addto_pending(ab);
			$$=ab;
			}   
			|tMINUS unary_expr{   /*eg. -4*/
			AstNodeNegative* node=ast_create_negative($2);
			AstObject* ab=NEGATIVE_TO_AST(node);
			ast_addto_pending(ab);
			$$=ab;

			}   
			|tNegated unary_expr{  /*eg. ~4*/
			AstNodeBitNegated* node=ast_create_bit_negated($2);
			AstObject* ab=BIT_NEGATED_TO_AST(node);
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

expr :shift_expr{$$=$1;}
	;
stmt_expr:expr {$$=$1;}
		 ;