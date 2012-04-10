#ifndef _CODGER_SYNTAX_AST_NODE_LITERAL_H_
#define _CODGER_SYNTAX_AST_NODE_LITERAL_H_
#include"node_type.h"
#include"ast_object.h"
#include<object/robject.h>

/* literal */
struct ast_node_literal
{
	INHERIT_AST_OBJECT;
	Robject* l_value;
};
typedef struct ast_node_literal AstNodeLiteral;
AstObject* ast_create_literal(Robject* value);
AST_TYPE_CAST(LITERAL,Literal,ATN_LITERAL);


/* unary expr */
AstNodeType node_positive;
AstNodeType node_negative;

/* multiply_expr */
AstNodeType node_mul;
AstNodeType node_div;
AstNodeType node_mod;

/* additive expr*/
AstNodeType node_plus;
AstNodeType node_minus;

/* shift expr */
AstNodeType node_lshift;
AstNodeType node_rshift;

/* bitwise expr */
AstNodeType node_and;
AstNodeType node_xor;
AstNodeType node_or;
AstNodeType node_negated;

/* compare expr */
AstNodeType node_lt;
AstNodeType node_le;
AstNodeType node_ge;
AstNodeType node_gt;
AstNodeType node_eq;
AstNodeType node_ne;
/* logic expr */
AstNodeType node_logic_not;
AstNodeType node_logic_and;
AstNodeType node_logic_or;


#endif 
