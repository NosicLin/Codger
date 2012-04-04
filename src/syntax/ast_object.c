#include"ast_object.h"
#include<stdlib.h>
#include<utility_c/marocs.h>
#include<rstd/redy_std.h>
#include<vm/except.h>
#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

static LIST_HEAD(pending_ast_object);

void ast_free(AstObject* ab)
{
	AstNodeType* t=ab->a_type;
	if(t==NULL)
	{
		BUG("Error AstObject");
		goto error;
	}
	if(t->n_free)
	{
		t->n_free(ab);
		return ;
	}
	WARN("AstObject No Free Func");
error:
	free(ab);
}

void ast_clear_pending()
{
	list_del_init(&pending_ast_object);
}
void ast_free_pending()
{
	AstObject* p;
	list_for_each_entry(p,&pending_ast_object,a_pending)
	{
		ast_free(p);
	}
	ast_clear_pending();
}

void ast_addto_pending(AstObject* ab)
{
	list_add_tail(&ab->a_pending,&pending_ast_object);
}

inline void ast_init(AstObject* ab,struct ast_node_type* node_type)
{
	ab->a_type=node_type;
	INIT_LIST_HEAD(&ab->a_pending);
	INIT_LIST_HEAD(&ab->a_chirldren);
	INIT_LIST_HEAD(&ab->a_sibling);
}

void* __ast_node_new(ssize_t size,struct ast_node_type* node_type)
{
	AstObject* ab=(AstObject*)ry_malloc(size);
	if(ab==NULL)
	{
		ryerr_nomemory();
		return NULL;
	}
	ast_init(ab,node_type);
	return ab;
}
void ast_node_free(AstObject* node)
{
	struct list_head* head=&node->a_chirldren;
	AstObject* p;
	struct list_head* cur;
	while(!list_empty(head))
	{
		cur=head->next;
		list_del(cur);
		p=list_entry(cur,AstObject,a_sibling);
		ast_free(p);
	}
	ry_free(node);
}
void ast_node_free_self(AstObject* node)
{
	ry_free(node);
}


#ifdef AST_MACHINE
static int ast_node_execute(AstObject* a)
{
	except_unkown_err_format("normal node can't execute");
	return AST_EXE_EXCEPTION;
}
#endif 

static AstNodeType node_object=
{
	.n_name="NormalNode",
	.n_type=ATN_UNKOWN,
	.n_free=ast_node_free,
	.n_free_node=ast_node_free_self,
#ifdef AST_MACHINE
	.n_execute=ast_node_execute,
#endif 
};

AstObject* ast_create_object()
{
	return ast_node_new(AstObject,&node_object);
}






