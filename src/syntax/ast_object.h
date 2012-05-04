#ifndef _CODGER_SYNTAX_AST_OBJECT_H_
#define _CODGER_SYNTAX_AST_OBJECT_H_
#include<utility_c/list_head.h>
#include<object/gr_opcode.h>
#include<object/gr_module.h>
#include<utility_c/marocs.h>

#define AST_DEBUG
struct ast_type_info;

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
	struct ast_type_info* a_type;
};
typedef struct ast_object AstObject;
#include"ast_type_info.h"

#define INHERIT_AST_OBJECT struct ast_object ast_base
#define TO_ASTOBJECT(node) ((AstObject*)node)

#define AstNode_New(type_object) \
   	((AstObject*)__ast_node_new(sizeof(AstObject),type_object))

/*interface*/
void AstTree_Free(AstObject* root);
void AstNode_Free(AstObject* node);
void AstObject_Init(AstObject* ab,struct ast_type_info* node_type);
void* __ast_node_new(ssize_t size,struct ast_type_info* node_type);

#define AstNode_NewType(Type,type_object) \
   	((Type*)__ast_node_new(sizeof(Type),type_object))


static inline const char* AstObject_Name(AstObject* ab)
{
	return ab->a_type->t_name;
}
static inline int AstObject_TypeId(AstObject* ab)
{
	return ab->a_type->t_type;
}

#ifdef AST_DEBUG

#define AstNode_Add(father, chirld) \
	do{ \
		assert(father); \
		assert(chirld); \
		list_add_tail(&((AstObject*)chirld)->a_sibling,&((AstObject*)father)->a_chirldren); \
	}while(0)
#else 
static inline void AstNode_Add(AstObject* father,AstObject* chirld)
{
	assert(father);
	assert(chirld);
	//printf("(%s<-%s)\n",father->a_type->t_name,chirld->a_type->t_name);
	list_add_tail(&chirld->a_sibling,&father->a_chirldren);
}
#endif

static inline void AstNode_Del(AstObject* father,AstObject* chirld)
{
	assert(father);
	assert(chirld);
	list_del(&chirld->a_sibling);
}


/* used for generate byte code */
int Ast_ToOpcode(AstObject* ab,GrModule* m,GrOpcode* op,long );
int Ast_ToAssignOpcode(AstObject* ab,GrModule* m,GrOpcode* op,long );
GrModule* Ast_ToModule(AstObject* root);



/* we use LR(1) grammar to parse redy source code
 * but LR(1) is a down to up method, when parse failed
 * we cann't reach the node that already reduced. so we 
 * must link the ast_object together by list_head pending_ast_object
 * if parse faied ,traversal the list and free ast_object
 * if success, break the list by set pending_ast_object 
 */ 

/* success,break the list*/
void AstPending_Clear();
/* failed traversal and free*/
void AstPending_Free();
/* and a new ast_object to list pending_ast_object */
void AstPending_Add(AstObject*);


extern AstTypeInfo Ast_Type_Normal;

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

static inline void AstNode_GetSub3(AstObject* ab,AstObject** sub1,AstObject** sub2,AstObject** sub3)
{
	struct list_head* s1=(&ab->a_chirldren)->next;
	struct list_head* s2=s1->next;
	struct list_head* s3=s2->next;

	*sub1=list_entry(s1,AstObject,a_sibling);
	*sub2=list_entry(s2,AstObject,a_sibling);
	*sub3=list_entry(s3,AstObject,a_sibling);
}
static inline void AstNode_GetSub2(AstObject* ab,AstObject** sub1,AstObject** sub2)
{
	struct list_head* s1=(&ab->a_chirldren)->next;
	struct list_head* s2=s1->next;

	*sub1=list_entry(s1,AstObject,a_sibling);
	*sub2=list_entry(s2,AstObject,a_sibling);
}
static inline void AstNode_GetSub1(AstObject* ab,AstObject** sub1)
{
	struct list_head* l_left=(&ab->a_chirldren)->next;
	*sub1=list_entry(l_left,AstObject,a_sibling);
}

static inline int AstObject_CanAssign(AstObject* ab)
{
	if(ab->a_type->t_to_assign_opcode)
	{
		return 1;
	}
	return 0;
}

#endif  /*_CODGER_SYNTAX_AST_OBJECT_H_*/

