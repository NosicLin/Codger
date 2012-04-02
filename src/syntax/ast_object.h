#ifndef _REDY_SYNTAX_AST_OBJECT_H_
#define _REDY_SYNTAX_AST_OBJECT_H_
#include<utility_c/list_head.h>
#include"node_type.h"

struct ast_node_type;

struct ast_object
{
	struct list_head a_pending;
	struct ast_node_type* a_type;
};
typedef struct ast_object AstObject;
#define INHERIT_AST_OBJECT struct ast_object ast_base
#define TO_ASTOBJECT(node) ((AstObject*)node)

#define ast_node_new(TYPE,type_object) \
   	((TYPE*)__ast_node_new(sizeof(TYPE),type_object))

/*interface*/

static inline void ast_destory(AstObject* ab){} /*TODO*/
void ast_free(AstObject* ab);
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

