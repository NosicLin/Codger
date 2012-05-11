#include"gr_module.h"
#include<memory/gc.h>
#include<engine/except.h>
#include"gr_symbol.h"

GrModule* GrModule_GcNew()
{
	GrModule* m=GrGc_New(GrModule,&Gr_Type_Module);
	if(m==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For GrModule Object");
		return NULL;
	}

	if(GrModule_Init(m)<0)
	{
		return NULL;
	}
	return m;
}

GrModule* GrModule_GcNewFlag(long flags)
{
	GrModule* m=GrGc_Alloc(GrModule,&Gr_Type_Module,flags);
	if(m==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For GrModule Object");
		return NULL;
	}
	if(GrModule_Init(m)<0)
	{
		return NULL;
	}
	return m;
}

int GrModule_Init(GrModule* m)
{
	GrArray* consts_pool=GrArray_GcNewFlag(GRGC_HEAP_OLD);
	if(consts_pool==NULL) goto error;

	GrArray* symbols_pool=GrArray_GcNewFlag(GRGC_HEAP_OLD);
	if(symbols_pool==NULL) goto error;

	GrArray* opcodes_pool=GrArray_GcNewFlag(GRGC_HEAP_OLD);
	if(opcodes_pool==NULL) goto error;
	GrArray* attrs_pool=GrArray_GcNewFlag(GRGC_HEAP_OLD);
	if(attrs_pool==NULL) goto error;

	GrHash* attrs=GrHash_GcNewFlag(GRGC_HEAP_OLD);
	if(attrs_pool==NULL) goto error ;

	if(attrs==NULL) goto error;

	m->m_consts_pool=consts_pool;
	m->m_symbols_pool=symbols_pool;
	m->m_opcodes_pool=opcodes_pool;
	m->m_attrs_pool=attrs_pool;

	m->m_attrs=attrs;
	m->m_name=NULL;
	m->m_codes=NULL;
	return 0;
error:
	GrErr_MemFormat("Can't Alloc Memory For GrModule Object To Init");
	return -1;
}
u_int32_t GrModule_MapOpcode(GrModule* m,GrOpcode* op)
{
	if(GrArray_Push(m->m_opcodes_pool,OPCODE_TO_GR(op))<0)
	{
		return GR_MODULE_MAP_ERR;
	}
	
	return GrArray_Size(m->m_opcodes_pool)-1;
}

u_int32_t GrModule_MapConst(GrModule* m,GrObject* g)
{
	if(GrArray_Push(m->m_consts_pool,g)<0)
	{
		return GR_MODULE_MAP_ERR;
	}

	return GrArray_Size(m->m_consts_pool)-1;
}

u_int32_t GrModule_MapSymbol(GrModule* m ,GrObject* g)
{
	if(GrArray_Push(m->m_symbols_pool,g))
	{
		return GR_MODULE_MAP_ERR;
	}

	return GrArray_Size(m->m_symbols_pool)-1;
}

int GrModule_SetName(GrModule* m,GrString* name)
{
	m->m_name=name;
	return 0;
}

int GrModule_SetOpcode(GrModule* m,GrOpcode* op)
{
	m->m_codes=op;
	return 0;
}
GrString* GrModule_GetName(GrModule* m)
{
	return m->m_name;
}


int GrModule_WriteToFile(GrModule* m,FILE* f,long flags)
{
	fprintf(f,"@ModuleName %s\n",m->m_name->s_value);
	fprintf(f,"@ConstNum %d \n{\n\t",GrArray_Size(m->m_consts_pool));

	int i;
	int size=GrArray_Size(m->m_consts_pool);
	GrObject* cur;


	for(i=0;i<size;i++)
	{
		cur=GrArray_Get(m->m_consts_pool,i);
		//assert(cur);
		GrObject_Print(cur,f,0);
		fprintf(f," ");
		if((i+1)%10==0)
		{
			fprintf(f,"\n\t");
		}
	}
	fprintf(f,"\n}\n");


	size=GrArray_Size(m->m_symbols_pool);

	fprintf(f,"@SymbolsNum %d \n{\n\t",size);
	for(i=0;i<size;i++)
	{
		cur=GrArray_Get(m->m_symbols_pool,i);
		GrObject_Print(cur,f,0);
		fprintf(f," ");
		if((i+1)%10==0)
		{
			fprintf(f,"\n\t");
		}
	}
	fprintf(f,"\n}\n");

	size=GrArray_Size(m->m_attrs_pool);
	fprintf(f,"@AttrNum %d \n{\n\t",size);
	for(i=0;i<size;i++)
	{
		cur=GrArray_Get(m->m_attrs_pool,i);
		GrObject_Print(cur,f,0);
		assert(GrSymbol_Verify(cur));
		fprintf(f,"(%lx)",((GrSymbol*)cur)->s_flags);

		fprintf(f," ");
		if((i+1)%10==0)
		{
			fprintf(f,"\n\t");
		}
	}
	fprintf(f,"\n}\n");

	fprintf(f,"@OpCode Module(%s) \n{\n",m->m_name->s_value);
	GrOpcode_WriteToFile(m->m_codes,f,1);
	fprintf(f,"}\n");

	size=GrArray_Size(m->m_opcodes_pool);

	for(i=0;i<size;i++)
	{
		cur=GrArray_Get(m->m_opcodes_pool,i);
		GrOpcode* op=(GrOpcode*)cur;
		fprintf(f,"@OpCode<%d> Func(%s) \n{\n",i,op->o_name->s_value);

		GrOpcode_WriteToFile(op,f,1);
		fprintf(f,"}\n");
	}

	return 1;
}


GrTypeInfo Gr_Type_Module=
{
	.t_name="ModuleObject",
	.t_size=sizeof(GrModule),
	.t_ops=&GR_TYPE_OPS_NOT_SUPPORT,
};



u_int32_t GrModule_MapAttr(GrModule* m,GrString* g ,long flags)
{
	GrSymbol* s=GrSymbol_GcNewFlag(g,flags,GRGC_HEAP_STATIC);

	if(GrArray_Push(m->m_attrs_pool,(GrObject*) s)<0)
	{
		return GR_MODULE_MAP_ERR;
	}
	return GrArray_Size(m->m_attrs_pool)-1;
}











