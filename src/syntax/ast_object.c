#include"ast_object.h"
#include<stdlib.h>
#include<utility_c/marocs.h>
#include<engine/except.h>
#include<object/gr_module.h>
#include<object/gr_opcode.h>
#include<memory/memory.h>
#include<memory/gc.h>

static LIST_HEAD(pending_ast_object);

inline void AstNode_Free(AstObject* ab)
{
	AstTypeInfo* t=ab->a_type;
	BUG_ON(t==NULL,"Error AstObject");
	if(t->t_destruct)
	{
		t->t_destruct(ab);
	}
	GrMem_Free(ab);
}

void AstPending_Clear()
{
	list_del_init(&pending_ast_object);
}


void AstPending_Free()
{
	AstObject* p=0;
	struct list_head* cur=0;
	while(!list_empty(&pending_ast_object))
	{
		cur=pending_ast_object.next;
		list_del(cur);
		p=list_entry(cur,AstObject,a_link);
		AstNode_Free(p);
	}
}

inline void AstPending_Add(AstObject* ab)
{
	list_add_tail(&ab->a_link,&pending_ast_object);
}

inline void AstObject_Init(AstObject* ab,struct ast_type_info* node_type)
{
	ab->a_flags=0;
	ab->a_type=node_type;
	INIT_LIST_HEAD(&ab->a_sibling);
	INIT_LIST_HEAD(&ab->a_chirldren);
	INIT_LIST_HEAD(&ab->a_link);
	AstPending_Add(ab);
}

void* __ast_node_new(ssize_t size,struct ast_type_info* node_type)
{
	AstObject* ab=GrMem_Alloc(size);
	if(ab==NULL)
	{
		return NULL;
	}
	AstObject_Init(ab,node_type);
	return ab;
}
void AstTree_Free(AstObject* node)
{
	struct list_head* head=&node->a_link;
	AstObject* p;
	struct list_head* cur;
	while(!list_empty(head))
	{
		cur=head->next;
		list_del(cur);
		p=list_entry(cur,AstObject,a_link);
		AstNode_Free(p);
	}
	AstNode_Free(node);
}



AstTypeInfo Ast_Type_Normal=
{
	.t_type=ATN_NORMAL,
	.t_name="NormalNode",
};



int Ast_ToOpcode(AstObject* ab,GrModule* md,GrOpcode* op,long flags)
{
	assert(md&&op);
	if(ab->a_flags&AST_FLAGS_TO_OPCODE)
	{
		BUG("Synatx Tree Maybe Error(%s)",
				ab->a_type==NULL?"Unkown":ab->a_type->t_name);
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
	int ret=ab->a_type->t_to_opcode(ab,md,op,flags);
	ab->a_flags&=~AST_FLAGS_TO_OPCODE;

	return ret;
}
int Ast_ToAssignOpcode(AstObject* ab,GrModule* md,GrOpcode* op,long flags)
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
	int ret=ab->a_type->t_to_assign_opcode(ab,md,op,flags);
	ab->a_flags&=~AST_FLAGS_TO_OPCODE;
	return ret;
}
int Ast_ToOperAssignOpcode(AstObject* ab,GrModule* md,
							GrOpcode* op,int type,long flags)
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
	int ret=ab->a_type->t_to_oper_and_assign_opcode(ab,md,op,type,flags);
	ab->a_flags&=~AST_FLAGS_TO_OPCODE;
	return ret;
}

GrModule*  Ast_ToModule(AstObject* root)
{
	GrModule* md=0;
	GrOpcode* op=0;
	int ret=0;
	md=GrModule_GcNewFlag(GRGC_HEAP_OLD);
	op=GrOpcode_GcNewFlag(GRGC_HEAP_OLD);

	GrString* op_name=GrString_GcNewFlag("module",GRGC_HEAP_OLD);
	GrArray* op_args_name=GrArray_GcNewFlag(GRGC_HEAP_OLD);

	if(op_name==NULL) goto error;
	if(op_args_name==NULL) goto error;


	GrOpcode_SetArgName(op,op_args_name);
	GrOpcode_SetName(op,op_name);

	if(md==NULL||op==NULL)
	{
		goto error;
	}
	ret=Ast_ToOpcode(root,md,op,0);
	if(ret<0)
	{
		goto error;
	}
	ret=GrOpcode_NeedMore(op,1);
	if(ret<0)
	{
		goto error;
	}
	GrOpcode_Push(op,OP_RETURN);
	GrModule_SetOpcode(md,op);
	return md;
error:
	return NULL;
}





