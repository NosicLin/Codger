#ifndef _CODGER_SYNTAX_NODE_TYPE_H_
#define _CODGER_SYNTAX_NODE_TYPE_H_ 
#include<assert.h>
struct ast_object;
#include<object/gr_opcode.h>
#include<object/gr_object.h>
#include<object/gr_module.h>
struct ast_type_info
{
	int t_type;
	const char* t_name; /* node name */
	/* destruct node */
	void (*t_destruct)(struct ast_object*);

	/* translate syntax tree to gr_opcode*/
	int (*t_to_opcode)(struct ast_object* ab,
						struct gr_module* md,
						struct gr_opcode* op,
						long flags);

	int (*t_to_assign_opcode)(struct ast_object* ab,
						struct gr_module* md,
						struct gr_opcode* op,
						long flags);
	int (*t_to_oper_and_assign_opcode)(struct ast_object* ab,
						struct gr_module* md,
						struct gr_opcode* op,
						int type,
						long flags);
};

typedef struct ast_type_info AstTypeInfo;


enum AST_NODE_TYPE
{
	ATN_UNKOWN=0,
	ATN_NORMAL,


	ATN_VAR,
	ATN_LITERAL,

	ATN_PERIOD,
	ATN_NEW,
	ATN_CALL,
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
	ATN_MINUS_ASSIGN,
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
	ATN_RETURN,
	ATN_FUNC,
	ATN_ARG,
	ATN_CLASS,
	ATN_ATTR,
	ATN_ATTR_DEFAULT,
	ATN_METHOD,
	ATN_CLASS_STMT,

	ATN_EXPORT,
	ATN_EXPORT_AS,
	ATN_IMPORT,

};


enum AST_ASSIGN_TYPE 
{
	AST_ASSIGN_TYPE_MUL,
	AST_ASSIGN_TYPE_DIV,
	AST_ASSIGN_TYPE_MOD,
	AST_ASSIGN_TYPE_PLUS,
	AST_ASSIGN_TYPE_MINUS,
	AST_ASSIGN_TYPE_LSHIFT,
	AST_ASSIGN_TYPE_RSHIFT,
	AST_ASSIGN_TYPE_AND,
	AST_ASSIGN_TYPE_XOR,
	AST_ASSIGN_TYPE_OR,
};

#define AST_TYPE_CAST(Hl,Ll,ast_type) \
	static inline Ast##Ll* AST_TO_##Hl(AstObject* ab) \
	{ \
		assert(ab->a_type->t_type==ast_type); \
		return (Ast##Ll*) ab; \
	} \
	static inline AstObject* Hl##_TO_AST(Ast##Ll* n) \
	{ \
		assert(((AstObject*)n)->a_type->t_type==ast_type); \
		return (AstObject*) n; \
	}

#endif /*_CODGER_SYNTAX_NODE_TYPE_H_*/
