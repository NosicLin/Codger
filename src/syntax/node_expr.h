#ifndef _CODGER_SYNTAX_AST_NODE_LITERAL_H_ 
#define _CODGER_SYNTAX_AST_NODE_LITERAL_H_ 
#include"ast_type_info.h"
#include"ast_object.h"
#include<object/gr_object.h>
#include<object/gr_string.h>

struct ast_literal
{
	INHERIT_AST_OBJECT;
	GrObject* l_value;
};

typedef struct ast_literal AstLiteral;
AstObject* AstLiteral_New(GrObject* value);

AST_TYPE_CAST(LITERAL,Literal,ATN_LITERAL);

#endif /*_CODGER_SYNTAX_AST_NODE_LITERAL_H_*/


