#ifndef _REDY_SYNTAX_NODE_TYPE_H_
#define _REDY_SYNTAX_NODE_TYPE_H_ 
#include"ast_object.h"
#include<assert.h>
enum AST_NODE_TYPE
{
	ATN_UNKOWN=0,

#define ATN_NODE_EXPR_BEGIN ATN_POSITVIE
	ATN_POSITVIE,
	ATN_NEGATIVE,
	ATN_MUL,
	ATN_DIV,
	ATN_MOD,
	ATN_PLUS,
	ATN_MINUS,
	ATN_LS,
	ATN_RS,
	ATN_LT,
	ATN_LE,
	ATN_NE,
	ATN_EQ,
	ATN_GE,
	ATN_GT,
	ATN_AND,
	ATN_OR,
	ATN_XOR,
	ATN_NEGATED,
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
	ATN_LITERAL,
	ATN_STMT,
	ATN_STMTS,
};

#define AST_TYPE_CAST(Hl,Ll,ast_type) \
	static inline AstNode##Ll* AST_TO_##Hl(AstObject* ab) \
	{ \
		assert(ab->a_type==ast_type); \
		return (AstNode##Ll*) ab; \
	} \
	static inline AstObject* Hl##_TO_AST(AstNode##Ll* n) \
	{ \
		assert(((AstObject*)n)->a_type==ast_type); \
		return (AstObject*) n; \
	}

#endif /*_REDY_SYNTAX_NODE_TYPE_H_*/
