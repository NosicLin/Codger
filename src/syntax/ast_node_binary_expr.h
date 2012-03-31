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

/*multiply_expr*/
typedef struct ast_binary_expr AstNodeMul; 
typedef struct ast_binary_expr AstNodeDiv;
typedef struct ast_binary_expr AstNodeMod;

/*additive_expr*/
typedef struct ast_binary_expr AstNodePlus;
typedef struct ast_binary_expr AstNodeMinus;

/*shift_expr*/
typedef struct ast_binary_expr AstNodeLShift;
typedef struct ast_binary_expr AstNodeRShift;

/*bitwise_expr*/
typedef struct ast_binary_expr AstNodeAnd;
typedef struct ast_binary_expr AstNodeXor;
typedef struct ast_binary_expr AstNodeOr;

/*relational_expr*/
typedef struct ast_binary_expr AstNodeLt;
typedef struct ast_binary_expr AstNodeLe;
typedef struct ast_binary_expr AstNodeGe;
typedef struct ast_binary_expr AstNodeGt;

/*equal_expr*/
typedef struct ast_binary_expr AstNodeNe;
typedef struct ast_binary_expr AstNodeEq;

/*logic_expr*/
typedef struct ast_binary_expr AstNodeLogicAnd;
typedef struct ast_binary_expr AstNodeLogicOr;


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

/*relational_expr*/
AstNodeLt* ast_create_lt(AstObject* l,AstObject* r);
AstNodeLe* ast_create_le(AstObject* l,AstObject* r);
AstNodeGt* ast_create_gt(AstObject* l,AstObject* r);
AstNodeGe* ast_create_ge(AstObject* l,AstObject* r);

/*equal_expr*/
AstNodeGt* ast_create_ne(AstObject* l,AstObject* r);
AstNodeGe* ast_create_eq(AstObject* l,AstObject* r);

/*bitwise_expr*/
AstNodeAnd* ast_create_and(AstObject* l,AstObject* r);
AstNodeXor* ast_create_xor(AstObject* l,AstObject* r);
AstNodeOr* ast_create_or(AstObject* l,AstObject* r);

/*logic_expr*/
AstNodeLogicAnd* ast_create_logic_and(AstObject* l,AstObject* r);
AstNodeLogicOr* ast_create_logic_or(AstObject* l,AstObject* r);


/* type cast*/
/*multiply_expr*/
AST_TYPE_CAST(MUL,Mul,ATN_MUL);
AST_TYPE_CAST(DIV,Div,ATN_DIV);
AST_TYPE_CAST(MOD,Mod,ATN_MOD);

/*additive_expr*/
AST_TYPE_CAST(PLUS,Plus,ATN_PLUS);
AST_TYPE_CAST(MINUS,Minus,ATN_MINUS);

/*shift_expr*/
AST_TYPE_CAST(LSHIFT,LShift,ATN_LSHIFT);
AST_TYPE_CAST(RSHIFT,RShift,ATN_RSHIFT);

/*bitwise_expr*/
AST_TYPE_CAST(AND,And,ATN_AND);
AST_TYPE_CAST(XOR,Xor,ATN_XOR);
AST_TYPE_CAST(OR,Or,ATN_OR);

/*relational_expr*/
AST_TYPE_CAST(LE,Le,ATN_LE);
AST_TYPE_CAST(LT,Lt,ATN_LT);
AST_TYPE_CAST(GE,Ge,ATN_GE);
AST_TYPE_CAST(GT,Gt,ATN_GT);

/*equal_expr*/
AST_TYPE_CAST(NE,Ne,ATN_NE);
AST_TYPE_CAST(EQ,Eq,ATN_EQ);

/*logic_expr*/
AST_TYPE_CAST(LOGIC_AND,LogicAnd,ATN_LOGIC_AND);
AST_TYPE_CAST(LOGIC_OR,LogicOr,ATN_LOGIC_OR);

#endif /*_REDY_SYNTAX_AST_NODE_BINARY_EXPR_H_*/
