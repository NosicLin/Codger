#ifndef _CODGER_SYNTAX_AST_NODE_STMT_H_
#define _CODGER_SYNTAX_AST_NODE_STMT_H_
#include"ast_object.h"

extern AstTypeInfo Ast_Type_Print;
extern AstTypeInfo Ast_Type_Stmts;
extern AstTypeInfo Ast_Type_Expr;
extern AstTypeInfo Ast_Type_Break;
extern AstTypeInfo Ast_Type_Continue;
extern AstTypeInfo Ast_Type_Assign;

extern AstTypeInfo Ast_Type_Mul_Assign;
extern AstTypeInfo Ast_Type_Div_Assign;
extern AstTypeInfo Ast_Type_Mod_Assign;
extern AstTypeInfo Ast_Type_Plus_Assign;
extern AstTypeInfo Ast_Type_Minus_Assign;
extern AstTypeInfo Ast_Type_LShift_Assign;
extern AstTypeInfo Ast_Type_RShift_Assign;
extern AstTypeInfo Ast_Type_And_Assign;
extern AstTypeInfo Ast_Type_Xor_Assign;
extern AstTypeInfo Ast_Type_Or_Assign;

extern AstTypeInfo Ast_Type_For;
extern AstTypeInfo Ast_Type_While;


extern AstTypeInfo Ast_Type_If;
extern AstTypeInfo Ast_Type_If_Elif;
extern AstTypeInfo Ast_Type_Else;
extern AstTypeInfo Ast_Type_Return;
extern AstTypeInfo Ast_Type_Func;


#endif /*_CODGER_SYNTAX_AST_NODE_STMT_H_*/

