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

AstTree : stmts{printf("paser success\n");}

;
stmts: expr{
	 Robject* r=ast_literal_get_value(AST_TO_LITERAL($1));
	 robject_print(r);
	 robject_release(r); }
	
	 | stmts expr{
	 Robject* r=ast_literal_get_value(AST_TO_LITERAL($2));
	 robject_print(r);
	 robject_release(r); }
	| tNEWLINE 
	| stmts tNEWLINE
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
	    AstNodeLiteral* t=ast_create_literal(bl);
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
;
expr :literal
