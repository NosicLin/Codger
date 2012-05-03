#ifndef _CODGER_SYNTAX_AST_OBJECT_H_
#define _CODGER_SYNTAX_AST_OBJECT_H_
#include<utility_c/list_head.h>
#include<vm/op_code.h>
#include<object/module_object.h>
#include<utility_c/marocs.h>

#define AST_DEBUG
struct ast_node_type;

#define AST_FLAGS_TO_OPCODE 0x1

struct ast_object
{
	int a_flags;
	/* the two attribute provide a simple way 
	 * to organize synatx tree structure
	 */
	struct list_head a_chirldren;
	struct list_head a_sibling;

	/* attribute a_link used to link  all node together*/
	struct list_head a_link;

	/* node type */
	struct ast_node_type* a_type;
};
typedef struct ast_object AstObject;
#include"node_type.h"

#define INHERIT_AST_OBJECT struct ast_object ast_base
#define TO_ASTOBJECT(node) ((AstObject*)node)

#define ast_node_new(type_object) \
   	((AstObject*)__ast_node_new(sizeof(AstObject),type_object))

/*interface*/
void ast_tree_free(AstObject* root);
void ast_node_free(AstObject* node);
void ast_init(AstObject* ab,struct ast_node_type* node_type);
void* __ast_node_new(ssize_t size,struct ast_node_type* node_type);

#define ast_node_new_type(Type,type_object) \
   	((Type*)__ast_node_new(sizeof(Type),type_object))


static inline const char* ast_name(AstObject* ab)
{
	return ab->a_type->t_name;
}
static inline int ast_typeid(AstObject* ab)
{
	return ab->a_type->t_type;
}

#ifdef AST_DEBUG

#define ast_node_add(father, chirld) \
	do{ \
		assert(father); \
		assert(chirld); \
		list_add_tail(&((AstObject*)chirld)->a_sibling,&((AstObject*)father)->a_chirldren); \
	}while(0)
#else 
static inline void ast_node_add(AstObject* father,AstObject* chirld)
{
	assert(father);
	assert(chirld);
	//printf("(%s<-%s)\n",father->a_type->t_name,chirld->a_type->t_name);
	list_add_tail(&chirld->a_sibling,&father->a_chirldren);
}
#endif

static inline void ast_node_del(AstObject* father,AstObject* chirld)
{
	assert(father);
	assert(chirld);
	list_del(&chirld->a_sibling);
}


/* used for generate byte code */
int ast_to_opcode(AstObject* ab,ModuleObject* m,OpCode* op);
int ast_to_assign_opcode(AstObject* ab,ModuleObject* m,OpCode* op);
ModuleObject* ast_to_module(AstObject* root);



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


AstNodeType node_normal;

#define AST_MEM_FAILED -2

#ifdef AST_DEBUG
#define CHECK_SUB_NODE_NUM( node ,num)  \
	do{ \
		struct list_head* head=&node->a_chirldren; \
		struct list_head* p=head; \
		int i=0; \
		for(i=0;i<num;i++) \
		{ \
			p=p->next; \
			if(p==head) BUG("Synatx Tree Error"); \
		} \
		if(p->next!=head) BUG("Synatx Tree Error"); \
	}while(0)

#define CHECK_NODE_TYPE(node,type) \
	do{ \
		if(node->a_type->t_type!=type) \
		{ \
			BUG("AstNode Type Error(%s<%d,%d>)",node->a_type->t_name, \
					node->a_type->t_type,type); \
		} \
	}while(0)
#else 
#define CHECK_SUB_NODE_NUM(node,num) do{}while(0) 
#define CHECK_NODE_TYPE(node,type) do{}while(0)
#endif  /*AST_DEBUG*/

static inline void ast_node_getsub3(AstObject* ab,AstObject** sub1,AstObject** sub2,AstObject** sub3)
{
	struct list_head* s1=(&ab->a_chirldren)->next;
	struct list_head* s2=s1->next;
	struct list_head* s3=s2->next;

	*sub1=list_entry(s1,AstObject,a_sibling);
	*sub2=list_entry(s2,AstObject,a_sibling);
	*sub3=list_entry(s3,AstObject,a_sibling);
}
static inline void ast_node_getsub2(AstObject* ab,AstObject** sub1,AstObject** sub2)
{
	struct list_head* s1=(&ab->a_chirldren)->next;
	struct list_head* s2=s1->next;

	*sub1=list_entry(s1,AstObject,a_sibling);
	*sub2=list_entry(s2,AstObject,a_sibling);
}
static inline void ast_node_getsub1(AstObject* ab,AstObject** sub1)
{
	struct list_head* l_left=(&ab->a_chirldren)->next;
	*sub1=list_entry(l_left,AstObject,a_sibling);
}

static inline int ast_check_can_assign(AstObject* ab)
{
	if(ab->a_type->t_to_assign_opcode)
	{
		return 1;
	}
	return 0;
}

#endif  /*_CODGER_SYNTAX_AST_OBJECT_H_*/

