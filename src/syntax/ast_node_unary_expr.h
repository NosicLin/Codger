#ifndef _REDY_SYNTAX_AST_UNARY_EXPR_H_
struct ast_unary_expr
{
	struct ast_object u_base;
	struct ast_object* u_value;
};

typedef struct ast_unary_expr AstUnaryExpr;
typedef struct ast_unary_expr AstNodePositive;
typedef struct ast_unary_expr AstNodeNegative;
typedef struct ast_unary_expr AstNodeNegated;
typedef struct ast_unary_expr AstNodeMulAssign;
typedef struct ast_unary_expr AstNodeDivAssign;
typedef struct ast_unary_expr AstNodeModAssign;
typedef struct ast_unary_expr AstNodePlusAssign;
typedef struct ast_unary_expr AstNodeMinusAssign;
typedef struct ast_unary_expr AstNodeLsAssign;
typedef struct ast_unary_expr AstNodeRsAssign;
typedef struct ast_unary_expr AstNodeAndAssign;
typedef struct ast_unary_expr AstNodeOrAssign;
typedef struct ast_unary_expr AstNodeXorAssign;


/*unary expr getter and setter */
static inline  AstObject* ast_uexpr_get_value(AstUnaryExpr* ab)
{
	return  ab->u_value;
}

static inline void ast_uexpr_set_value(AstUnaryExpr* ab,AstObject* value)
{
	ab->u_value=value;
}

/* creater interface*/
AstNodeMul* ast_create_mul();
AstNodeDiv* ast_create_div();
AstNodeMod* ast_create_mod();
AstNodePlus* ast_create_plus();
AstNodeMinus* ast_create_minus();

#endif /*_REDY_SYNTAX_AST_UNARY_EXPR_H_*/

