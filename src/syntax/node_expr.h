#ifndef _CODGER_SYNTAX_AST_NODE_EXPR_H_ 
#define _CODGER_SYNTAX_AST_NODE_EXPR_H_ 
#include"ast_type_info.h"
#include"ast_object.h"
#include<object/gr_object.h>
#include<object/gr_string.h>


struct ast_literal
{
	INHERIT_AST_OBJECT;
	GrObject* l_value;
};

typedef struct ast_literal AstLiteral;
AstObject* AstLiteral_New(GrObject* value);

AST_TYPE_CAST(LITERAL,Literal,ATN_LITERAL);

struct ast_var
{
	INHERIT_AST_OBJECT;
	GrString* v_value;
};
typedef struct ast_var AstVar;
AstObject* AstVar_New(GrString*);
AstObject* AstUpperVar_New(GrString*);
AST_TYPE_CAST(VAR,Var,ATN_VAR);


extern AstTypeInfo Ast_Type_Call;
extern AstTypeInfo Ast_Type_Square;

extern AstTypeInfo Ast_Type_Period;
extern AstTypeInfo Ast_Type_New;

extern AstTypeInfo Ast_Type_Positive;
extern AstTypeInfo Ast_Type_Negative;
extern AstTypeInfo Ast_Type_Negated;
extern AstTypeInfo Ast_Type_Mul;
extern AstTypeInfo Ast_Type_Div;
extern AstTypeInfo Ast_Type_Mod;
extern AstTypeInfo Ast_Type_Plus;
extern AstTypeInfo Ast_Type_Minus;
extern AstTypeInfo Ast_Type_LShift;
extern AstTypeInfo Ast_Type_RShift;
extern AstTypeInfo Ast_Type_And;
extern AstTypeInfo Ast_Type_Xor;
extern AstTypeInfo Ast_Type_Or;
extern AstTypeInfo Ast_Type_Lt;
extern AstTypeInfo Ast_Type_Le;
extern AstTypeInfo Ast_Type_Gt;
extern AstTypeInfo Ast_Type_Ge;
extern AstTypeInfo Ast_Type_Eq;
extern AstTypeInfo Ast_Type_Ne;

extern AstTypeInfo Ast_Type_Logic_Not;
extern AstTypeInfo Ast_Type_Logic_And;
extern AstTypeInfo Ast_Type_Logic_Or;

extern AstTypeInfo Ast_Type_Array;




#endif /*_CODGER_SYNTAX_AST_NODE_EXPR_H_*/


