#ifndef _REDY_SYNTAX_AST_NODE_BINARY_EXPR_H_
#define _REDY_SYNTAX_AST_NODE_BINARY_EXPR_H_
#include"node_type.h"

struct ast_binary_expr
{
	BASE_AST_OBJECT;
	struct ast_object* b_left;
	struct ast_object* b_right;
};
typedef struct ast_binary_expr AstBinaryExpr;

typedef struct ast_binary_expr AstNodeMul; 
typedef struct ast_binary_expr AstNodeDiv;
typedef struct ast_binary_expr AstNodeMod;
typedef struct ast_binary_expr AstNodePlus;
typedef struct ast_binary_expr AstNodeMinus;
typedef struct ast_binary_expr AstNodeLShift;
typedef struct ast_binary_expr AstNodeRShift;
typedef struct ast_binary_expr AstNodeLt;
typedef struct ast_binary_expr AstNodeLe;
typedef struct ast_binary_expr AstNodeNe;
typedef struct ast_binary_expr AstNodeEq;
typedef struct ast_binary_expr AstNodeGe;
typedef struct ast_binary_expr AstNodeGt;
typedef struct ast_binary_expr AstNodeAnd;
typedef struct ast_binary_expr AstNodeOr;
typedef struct ast_binary_expr AstNodeXor;

/*binary expr getter and setter*/
/* don't need setter any more */
/*
static inline void ast_bexpr_set_left(AstBinaryExpr* ab,AstObject* value)
{
	ab->b_left=value;
}
static inline void ast_bexpr_set_right(AstBinaryExpr* ab,AstObject* value)
{
	ab->b_right=value;
}
*/
static inline  AstObject* ast_bexpr_get_left(AstBinaryExpr* ab)
{
	return  ab->b_left;
}
static inline  AstObject* ast_bexpr_get_right(AstBinaryExpr* ab)
{
	return  ab->b_right;
}

/* creator interface */
/*multiply_expr*/
AstNodeMul* ast_create_mul(AstObject* l,AstObject* r);
AstNodeDiv* ast_create_div(AstObject* l,AstObject* r);
AstNodeMod* ast_create_mod(AstObject* l,AstObject* r);

/*additive_expr*/
AstNodePlus* ast_create_plus(AstObject* l,AstObject* r);
AstNodeMinus* ast_create_minus(AstObject* l,AstObject* r);

/*shift_expr*/
AstNodeLShift* ast_create_lshift(AstObject* l, AstObject* r);
AstNodeRShift* ast_create_rshift(AstObject* l,AstObject* r);

/* type cast*/
AST_TYPE_CAST(MUL,Mul,ATN_MUL);
AST_TYPE_CAST(DIV,Div,ATN_DIV);
AST_TYPE_CAST(MOD,Mod,ATN_MOD);
AST_TYPE_CAST(PLUS,Plus,ATN_PLUS);
AST_TYPE_CAST(MINUS,Minus,ATN_MINUS);
AST_TYPE_CAST(LSHIFT,LShift,ATN_LSHIFT);
AST_TYPE_CAST(RSHIFT,RShift,ATN_RSHIFT);



#endif /*_REDY_SYNTAX_AST_NODE_BINARY_EXPR_H_*/