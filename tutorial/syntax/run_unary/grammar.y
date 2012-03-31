%{

#include"yylex.h"
#include"ast_nodes.h"
#include"parser.h"
#include<rtype/bt_int.h>
#include<rtype/bt_string.h>
#include<rtype/bt_float.h>
#include<rtype/bt_long.h>
#include<rtype/bt_bool.h>
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

AstTree : stmts{parser_set_root($1);}
		| stmts stmt{
		    AstNodeStmts* stmts=AST_TO_STMTS($1);
			AstNodeStmt* node=AST_TO_STMT($2);
			ast_stmts_add(stmts,node);
			parser_set_root(STMTS_TO_AST(stmts));
		}
        
;

stmts: stmt  tNEWLINE
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

	 ;
literal: tINTEGER 
	   {
		BtInt* bi=btint_from_str(yl_cur_string());
	    AstNodeLiteral* t=ast_create_literal(I_TO_R(bi));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(I_TO_R(bi));
		$$=LITERAL_TO_AST(t); }

		| tLONG
		{
		BtLong* bl=btlong_from_str(yl_cur_string());
	    AstNodeLiteral* t=ast_create_literal(L_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(L_TO_R(bl));
		$$=LITERAL_TO_AST(t);}

		| tFLAOT{
		BtFloat* bf=btfloat_from_str(yl_cur_string());
	   	AstNodeLiteral* t=ast_create_literal(F_TO_R(bf));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(F_TO_R(bf));
		$$=LITERAL_TO_AST(t);}
		| tSTRING{
		BtString* bs=btstring_create(yl_cur_string());
	   	AstNodeLiteral* t=ast_create_literal(S_TO_R(bs));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(S_TO_R(bs));
		$$=LITERAL_TO_AST(t);}
		| kFALSE{
		BtBool* bl=btbool_create(0);
		AstNodeLiteral* node=ast_create_literal(B_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(node));
   		robject_release(B_TO_R(bl));
		$$=LITERAL_TO_AST(node);
		}
		| kTRUE{
		BtBool* bl=btbool_create(1);
		AstNodeLiteral* node=ast_create_literal(B_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(node));
   		robject_release(B_TO_R(bl));
		$$=LITERAL_TO_AST(node);
		}
;
primary_expr: literal {$$=$1;}
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
			AstNodeNegated* node=ast_create_negated($2);
			AstObject* ab=NEGATED_TO_AST(node);
			ast_addto_pending(ab);
			$$=ab;
			} 
			;

stmt: unary_expr
	{
	AstNodeStmt* node=ast_create_stmt($1);
	ast_addto_pending(STMT_TO_AST(node));
	$$=STMT_TO_AST(node);
	}
