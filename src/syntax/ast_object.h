#ifndef _CODGER_SYNTAX_AST_OBJECT_H_
#define _CODGER_SYNTAX_AST_OBJECT_H_
#include<utility_c/list_head.h>
#include"node_type.h"

struct ast_node_type;

struct ast_object
{
	/* the two attribute provide a simple way 
	 * to organize synatx tree structure
	 * if sub class don't used it ,just ignore
	 */
	struct list_head a_chirldren;
	struct list_head a_sibling;
	/* attribute a_link used to link  all node together*/
	struct list_head a_link;

	/* node type */
	struct ast_node_type* a_type;
};
typedef struct ast_object AstObject;
#define INHERIT_AST_OBJECT struct ast_object ast_base
#define TO_ASTOBJECT(node) ((AstObject*)node)

#define ast_node_new(TYPE,type_object) \
   	((TYPE*)__ast_node_new(sizeof(TYPE),type_object))

/*interface*/
void ast_tree_free(AstObject* root);
void ast_node_free(AstObject* node);
void ast_init(AstObject* ab,struct ast_node_type* node_type);
void* __ast_node_new(ssize_t size,struct ast_node_type* node_type);

static inline const char* ast_name(AstObject* ab)
{
	return ab->a_type->n_name;
}
static inline int ast_typeid(AstObject* ab)
{
	return ab->a_type->n_type;
}

AstObject* ast_create_object();
static inline void ast_node_add(AstObject* father,AstObject* chirld)
{
	list_add_tail(&chirld->a_sibling,&father->a_chirldren);
}
static inline void ast_node_del(AstObject* father,AstObject* chirld)
{
	list_del(&chirld->a_sibling);
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

