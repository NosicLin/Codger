#ifndef _CODGER_SYNTAX_NODE_TYPE_H_
#define _CODGER_SYNTAX_NODE_TYPE_H_ 
#include<assert.h>
struct ast_object;
#include<vm/op_code.h>
#include<object/robject.h>
#include<object/module_object.h>
struct ast_node_type
{
	int t_type;
	const char* t_name; /* node name */
	/* destruct node */
	void (*t_destruct)(struct ast_object*);

	/* translate syntax tree to op_code*/
	int (*t_to_opcode)(struct ast_object* ab,
						struct module_object* md,
						struct op_code* op);
	int (*t_to_assign_opcode)(struct ast_object* ab,
						struct module_object* md,
						struct op_code* op);
};

typedef struct ast_node_type AstNodeType;


enum AST_NODE_TYPE
{
	ATN_UNKOWN=0,
	ATN_NORMAL,


	ATN_VAR,
	ATN_LITERAL,

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

	ATN_EXPR,
	ATN_STMT,
	ATN_STMTS,
	ATN_PRINT,
	ATN_WHILE,
	ATN_IF,
	ATN_IF_ELIF,
	ATN_ELSE,
	ATN_ARRAY,
	ATN_SQUARE,
	ATN_FOR,
	ATN_BREAK,
	ATN_CONTINUE,
	ATN_FUNC,
	ATN_ARG,
};

#define AST_TYPE_CAST(Hl,Ll,ast_type) \
	static inline AstNode##Ll* AST_TO_##Hl(AstObject* ab) \
	{ \
		assert(ab->a_type->t_type==ast_type); \
		return (AstNode##Ll*) ab; \
	} \
	static inline AstObject* Hl##_TO_AST(AstNode##Ll* n) \
	{ \
		assert(((AstObject*)n)->a_type->t_type==ast_type); \
		return (AstObject*) n; \
	}

#endif /*_CODGER_SYNTAX_NODE_TYPE_H_*/
