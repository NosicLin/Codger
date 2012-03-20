#include"ast_object.h"
#include<stdlib.h>
#include<utility_c/marocs.h>

static LIST_HEAD(pending_ast_object);

void ast_free(AstObject* ab)
{
	if(ab->a_ops)
	{
		if(ab->a_ops->ao_free)
		{
			ab->a_ops->ao_free(ab);
			return ;
		}
	}
	WARN("AstObject(%s) No Free Func",ab->a_name);
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
void ast_init(AstObject* ab,int type,char* name ,struct ast_object_ops* ops)
{
	ab->a_type=type;
	ab->a_name=name;
	ab->a_ops=ops;
	INIT_LIST_HEAD(&ab->a_pending);
}


