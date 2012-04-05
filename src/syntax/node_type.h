#ifndef _REDY_SYNTAX_NODE_TYPE_H_
#define _REDY_SYNTAX_NODE_TYPE_H_ 
#include<assert.h>
struct ast_object;
struct ast_node_type
{
	int n_type;
	const char* n_name;
	void (*n_free)(struct ast_object*);
	void (*n_free_node)(struct ast_object*);
#ifdef AST_MACHINE
	int (*n_execute)(struct ast_object*);
#endif 
};

typedef struct ast_node_type AstNodeType;

enum AST_NODE_TYPE
{
	ATN_UNKOWN=0,

#define ATN_NODE_EXPR_BEGIN ATN_POSITVIE
	ATN_POSITIVE,
	ATN_NEGATIVE,
	ATN_NEGATED,
	ATN_MUL,
	ATN_DIV,
	ATN_MOD,
	ATN_PLUS,
	ATN_MINUS,
	ATN_LSHIFT,
	ATN_RSHIFT,
	ATN_LT,
	ATN_LE,
	ATN_NE,
	ATN_EQ,
	ATN_GE,
	ATN_GT,
	ATN_AND,
	ATN_OR,
	ATN_XOR,

	ATN_LOGIC_NOT,
	ATN_LOGIC_OR,
	ATN_LOGIC_AND,
	

	/*operator and assign*/
	ATN_ASSIGN,
	ATN_MUL_ASSIGN,
	ATN_DIV_ASSIGN,
	ATN_MOD_ASSIGN,
	ATN_PLUS_ASSIGN,
	ATN_LSHIFT_ASSIGN,
	ATN_RSHIFT_ASSIGN,
	ATN_AND_ASSIGN,
	ATN_OR_ASSIGN,
	ATN_XOR_ASSIGN,
#define ATN_NODE_EXPR_END ATN_XOR_ASSIGN
#define ATN_EXPR_NUM (ATN_NODE_EXPR_END-ATN_NODE_EXPR_BEGIN+1)
	ATN_UEXPR,
	ATN_VAR,
	ATN_LITERAL,
	ATN_STMT,
	ATN_STMTS,
	ATN_PRINT,
	ATN_WHILE,
	ATN_IF,
	ATN_IF_SUB,
	ATN_ARRAY,
	ATN_GET_ITEM,
};

#define AST_TYPE_CAST(Hl,Ll,ast_type) \
	static inline AstNode##Ll* AST_TO_##Hl(AstObject* ab) \
	{ \
		assert(ab->a_type->n_type==ast_type); \
		return (AstNode##Ll*) ab; \
	} \
	static inline AstObject* Hl##_TO_AST(AstNode##Ll* n) \
	{ \
		assert(((AstObject*)n)->a_type->n_type==ast_type); \
		return (AstObject*) n; \
	}

#endif /*_REDY_SYNTAX_NODE_TYPE_H_*/
