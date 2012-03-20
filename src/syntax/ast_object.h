#ifndef _REDY_SYNTAX_AST_OBJECT_H_
#define _REDY_SYNTAX_AST_OBJECT_H_
#include<utility_c/list_head.h>

#define AST_MACHINE
struct ast_object;

struct ast_object_ops
{
	void (*ao_free)(struct ast_object*);
#ifdef AST_MACHINE
	int (*ao_execute)(struct ast_object*);
#endif 

};

struct ast_object
{
	int a_type;
	char* a_name;
	struct list_head a_pending;
	struct ast_object_ops* a_ops;
};
typedef struct ast_object AstObject;
#define BASE_AST_OBJECT struct ast_object ast_base
#define AST_BASE(node) (&node->ast_base)
/*interface*/

void ast_free(AstObject* ab);

void ast_init(AstObject* ab,int type,char* name ,struct ast_object_ops* ops);

static inline char* ast_name(AstObject* ab)
{
	return ab->a_name;
}
static inline int ast_type(AstObject* ab)
{
	return ab->a_type;
}


/* we use LR(1) grammar to parse redy source code
 * but LR(1) is a down to up method, when parse failed
 * we cann't reach the node that already reduced. so we 
 * must link the ast_object together by list_head pending_ast_object
 * if parse faied ,traversal the list and free ast_object
 * if success, break the list by set pending_ast_object 
 */ 

/* success,break the list*/
void ast_clear_pending();
/* failed traversal and free*/
void ast_free_pending();
/* and a new ast_object to list pending_ast_object */
void ast_addto_pending(AstObject*);
#endif 

