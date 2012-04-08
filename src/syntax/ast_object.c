#include"ast_object.h"
#include<stdlib.h>
#include<utility_c/marocs.h>
#include<rstd/gr_std.h>
#include<vm/except.h>
#include<object/module_object.h>
#include<vm/op_code.h>

static LIST_HEAD(pending_ast_object);
static inline void __cache_free(AstObject* ab)
{
	gr_free(ab);
}
static inline AstObject* __cache_alloc(ssize_t size)
{
	assert(size>=sizeof(AstObject));
	AstObject* ao=(AstObject*)gr_malloc(size);
	if(ao==NULL)
	{
		grerr_nomemory();
		return NULL;
	}
	return ao;
}

inline void ast_node_free(AstObject* ab)
{
	AstNodeType* t=ab->a_type;
	BUG_ON(t==NULL,"Error AstObject");
	if(t->n_destruct)
	{
		t->n_destruct(ab);
	}
	__cache_free(ab);
}

void ast_clear_pending()
{
	list_del_init(&pending_ast_object);
}
void ast_free_pending()
{
	AstObject* p=0;
	struct list_head* cur=0;
	while(!list_empty(&pending_ast_object))
	{
		cur=pending_ast_object.next;
		list_del(cur);
		p=list_entry(cur,AstObject,a_link);
		ast_node_free(p);
	}
}

inline void ast_addto_pending(AstObject* ab)
{
	list_add_tail(&ab->a_link,&pending_ast_object);
}

inline void ast_init(AstObject* ab,struct ast_node_type* node_type)
{
	ab->a_type=node_type;
	INIT_LIST_HEAD(&ab->a_sibling);
	INIT_LIST_HEAD(&ab->a_chirldren);
	INIT_LIST_HEAD(&ab->a_link);
	ast_addto_pending(ab);
}

void* __ast_node_new(ssize_t size,struct ast_node_type* node_type)
{
	AstObject* ab=__cache_alloc(size);
	if(ab==NULL)
	{
		return NULL;
	}
	ast_init(ab,node_type);
	return ab;
}
void ast_tree_free(AstObject* node)
{
	struct list_head* head=&node->a_link;
	AstObject* p;
	struct list_head* cur;
	while(!list_empty(head))
	{
		cur=head->next;
		list_del(cur);
		p=list_entry(cur,AstObject,a_link);
		ast_node_free(p);
	}
	ast_node_free(node);
}



static AstNodeType node_object=
{
	.n_name="NormalNode",
};

AstObject* ast_create_object()
{
	return ast_node_new(AstObject,&node_object);
}


static int __ast_to_module(AstObject* ab,ModuleObject* md,OpCode* op)
{
	assert(ab->a_type->n_to_opcode);
	int ret=ab->a_type->n_to_opcode(ab,md,op);
	return ret;
}

ModuleObject*  ast_to_module(AstObject* root)
{
	ModuleObject* md=0;
	OpCode* op=0;
	int ret=0;
	md=module_new();
	op=op_code_new();
	if(md==NULL||op==NULL)
	{
		goto error;
	}
	ret=__ast_to_module(root,md,op);
	if(ret<0)
	{
		goto error;
	}
	module_set_opcode(md,op);
	return md;
error:
	if(md) robject_release(M_TO_R(md));
	if(op) op_code_free(op);
	return NULL;
}





