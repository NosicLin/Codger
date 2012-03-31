#include"ast_object.h"
#include<stdlib.h>
#include<utility_c/marocs.h>
#include<rstd/redy_std.h>

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



