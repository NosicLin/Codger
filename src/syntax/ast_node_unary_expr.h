#ifndef _REDY_SYNTAX_AST_UNARY_EXPR_H_
#include"ast_object.h"
#include"node_type.h"
struct ast_unary_expr
{
	BASE_AST_OBJECT;
	struct ast_object* u_value;
};

typedef struct ast_unary_expr AstNodeUExpr;
typedef struct ast_unary_expr AstNodePositive;
typedef struct ast_unary_expr AstNodeNegative;
typedef struct ast_unary_expr AstNodeBitNegated;
typedef struct ast_unary_expr AstNodeLogicNot;


/*unary expr getter and setter */
static inline  AstObject* ast_uexpr_get_value(AstNodeUExpr* ab)
{
	return  ab->u_value;
}

/* creater interface*/
AstNodePositive* ast_create_positive(AstObject* sub_node);
AstNodeNegative* ast_create_negative(AstObject* sub_node);
AstNodeBitNegated* ast_create_bit_negated(AstObject* sub_node);
AstNodeLogicNot* ast_create_logic_not(AstObject* sub_node);

/*type cast*/
AST_TYPE_CAST(UEXPR,UExpr,ATN_UEXPR);
AST_TYPE_CAST(POSITIVE,Positive,ATN_POSITIVE);
AST_TYPE_CAST(NEGATIVE,Negative,ATN_NEGATIVE);
AST_TYPE_CAST(BIT_NEGATED,BitNegated,ATN_BIT_NEGATED);
AST_TYPE_CAST(LOGIC_NOT,LogicNot,ATN_LOGIC_NOT);
#endif /*_REDY_SYNTAX_AST_UNARY_EXPR_H_*/

