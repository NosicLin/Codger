#include"ast_object.h"
#include<stdlib.h>
#include<utility_c/marocs.h>
#include<rstd/gr_std.h>
#include<vm/except.h>
#ifdef AST_MACHINE
#include"ast_machine.h"
#endif 

static LIST_HEAD(pending_ast_object);
static inline void __cache_free(AstObject* ab)
{
	gr_free(ab);
}
static inline AstObject* __cache_alloc(ssize_t size,int family)
{
	return gr_malloc(size);
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
		p=list_entry(cur,AstObject,a_sibling);
		ast_node_free(p);
	}
}

inline void ast_addto_pending(AstObject* ab)
{
	list_add_tail(&ab->a_link,&pending_ast_object);
}

inline void ast_init(AstObject* ab,struct ast_node_type* node_type)
{
	BUG_ON(node_type->n_belong==ANF_UNKOWN,
			"NodeType(%s) n_belong attr Not Init",node_type->n_name);
	ab->a_type=node_type;
	INIT_LIST_HEAD(&ab->a_sibling);
	INIT_LIST_HEAD(&ab->a_chirldren);
	INIT_LIST_HEAD(&ab->a_link);
	ast_addto_pending(ab);
}

void* __ast_node_new(ssize_t size,struct ast_node_type* node_type)
{
	int family=node_type->n_belong;
	BUG_ON(node_type->n_belong==ANF_UNKOWN,
			"NodeType(%s) n_belong attr Not Init",node_type->n_name);

	AstObject* ab=__cache_alloc(size,family);
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
#ifdef AST_MACHINE
	.n_execute=ast_node_execute,
#endif 
};

AstObject* ast_create_object()
{
	return ast_node_new(AstObject,&node_object);
}






