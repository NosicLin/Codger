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
	if(t->t_destruct)
	{
		t->t_destruct(ab);
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
	ab->a_flags=0;
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



AstNodeType node_normal=
{
	.t_type=ATN_NORMAL,
	.t_name="NormalNode",
};



int ast_to_opcode(AstObject* ab,ModuleObject* md,OpCode* op)
{
	if(ab->a_flags&AST_FLAGS_TO_OPCODE)
	{
		BUG("Synatx Tree Maybe Error");
		return -1;
	}

	if(ab->a_type==NULL)
	{
		BUG("AstNodeType Not Find");
		return -1;
	}
	if(ab->a_type->t_to_opcode==NULL)
	{
		BUG("%s No To OpCode Func",ab->a_type->t_name);
		return -1;
	}

	ab->a_flags|=AST_FLAGS_TO_OPCODE;
	int ret=ab->a_type->t_to_opcode(ab,md,op);
	ab->a_flags&=~AST_FLAGS_TO_OPCODE;

	return ret;
}
int ast_to_assign_opcode(AstObject* ab,ModuleObject* md,OpCode* op)
{
	if(ab->a_flags&AST_FLAGS_TO_OPCODE)
	{
		BUG("Syntax Tree Maybe Error");
		return -1;
	}
	if(ab->a_type==NULL)
	{
		BUG("AstNodeType Not Find");
		return -1;
	}
	if(ab->a_type->t_to_assign_opcode==NULL)
	{
		BUG("No To Assign OpCode Func");
		return -1;
	}
	ab->a_flags|=AST_FLAGS_TO_OPCODE;
	int ret=ab->a_type->t_to_assign_opcode(ab,md,op);
	ab->a_flags&=~AST_FLAGS_TO_OPCODE;
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
	ret=ast_to_opcode(root,md,op);
	if(ret<0)
	{
		goto error;
	}
	ret=op_code_enlarge_more(op,1);
	if(ret<0)
	{
		goto error;
	}
	op_code_push(op,OP_RETURN);
	module_set_opcode(md,op);
	return md;
error:
	if(md) robject_release(M_TO_R(md));
	if(op) op_code_free(op);
	return NULL;
}





