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
typedef struct ast_binary_expr AstNodeLs;
typedef struct ast_binary_expr AstNodeRs;
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
static inline void ast_bexpr_set_left(AstBinaryExpr* ab,AstObject* value)
{
	ab->b_left=value;
}
static inline void ast_bexpr_set_right(AstBinaryExpr* ab,AstObject* value)
{
	ab->b_right=value;
}
static inline  AstObject* ast_bexpr_get_left(AstBinaryExpr* ab)
{
	return  ab->b_left;
}
static inline  AstObject* ast_bexpr_get_right(AstBinaryExpr* ab)
{
	return  ab->b_right;
}

/* creator interface */
AstNodeMul* ast_create_mul();
AstNodeDiv* ast_create_div();
AstNodeMod* ast_create_mod();

/* type cast*/
AST_TYPE_CAST(MUL,Mul,ATN_MUL);
AST_TYPE_CAST(DIV,Div,ATN_DIV);
AST_TYPE_CAST(MOD,Mod,ATN_MOD);
AST_TYPE_CAST(PLUS,Plus,ATN_PLUS);
AST_TYPE_CAST(MINUS,Minus,ATN_MINUS);
AST_TYPE_CAST(LS,Ls,ATN_LS);
AST_TYPE_CAST(RS,Rs,ATN_RS);



#endif /*_REDY_SYNTAX_AST_NODE_BINARY_EXPR_H_*/
