#include"parser.h"
static AstObject* s_ast_root=0;
void parser_set_root(AstObject* root)
{
	s_ast_root=root;
}
AstObject* parser_get_root()
{
	return s_ast_root;
}
