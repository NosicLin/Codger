#include"gr_symbol.h"
#include<memory/gc.h>
#include"gr_class.h"
#include<engine/except.h>


GrSymbol* GrSymbol_GcNew(GrString* name ,long pemission)
{
	GrSymbol* s=GrGc_Alloc(GrSymbol,&Gr_Type_Symbol,GRGC_HEAP_YOUNG);
	if(s==NULL) 
	{
		GrErr_MemFormat("Can't Alloc Memory For SymbolObject");
		return NULL;
	}
	s->s_flags=pemission;
	s->s_name=name;
	return s;
}

GrSymbol* GrSymbol_GcNewFlag(GrString* name,long pemission ,long flags)
{
	GrSymbol* s=GrGc_Alloc(GrSymbol,&Gr_Type_Symbol,flags);
	if(s==NULL) 
	{
		GrErr_MemFormat("Can't Alloc Memory For SymbolObject");
		return NULL;
	}
	s->s_flags=pemission;
	s->s_name=name;
	return s;
}

GrSymbol* GrSymbol_GcNewFromStr(const char* str,long pemission)
{
	GrString* gs=GrString_GcNewFlag(str,GRGC_HEAP_YOUNG);
	if(gs==NULL)
	{
		return NULL;
	}
	GrSymbol* sy=GrGc_Alloc(GrSymbol,&Gr_Type_Symbol,GRGC_HEAP_YOUNG);
	if(sy==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For SymbolObject");
		return NULL;
	}

	sy->s_flags=pemission;
	sy->s_name=gs;
	return sy;
}
GrSymbol* GrSymbol_GcNewFlagFromStr(const char* str,
							long pemission,long flags)
{
	GrString* gs=GrString_GcNewFlag(str,flags);
	if(gs==NULL)
	{
		return NULL;
	}
	GrSymbol* sy=GrGc_Alloc(GrSymbol,&Gr_Type_Symbol,flags);
	if(sy==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For SymbolObject");
		return NULL;
	}

	sy->s_flags=pemission;
	sy->s_name=gs;
	return sy;
}

ssize_t GrSymbol_Hash(GrSymbol* sy)
{
	assert(sy->s_name);
	return GrString_Hash(sy->s_name);
}

char* GrSymbol_PermName(GrSymbol* sy)
{
	if(sy->s_flags&GR_CLASS_PUBLIC)
	{
		return "public";
	}
	if(sy->s_flags&GR_CLASS_PROTECTED)
	{
		return "protected";
	}
	if(sy->s_flags&GR_CLASS_PRIVATE)
	{
		return "private";
	}
	return "public";
}



static int symbol_cmp(GrObject* x,GrObject* y)
{
	if(GrString_Verify(y))
	{
		return GrString_Cmp(((GrSymbol*)x)->s_name,(GrString*)y);
	}

	return GR_CMP_NOT_SUPPORT;
}
static int symbol_cmp_reverse(GrObject* x,GrObject* y)
{
	if(GrString_Verify(y))
	{
		return GrString_Cmp((GrString*)y,((GrSymbol*)x)->s_name);
	}
	return GR_CMP_NOT_SUPPORT;
}

int GrSymbol_Print(GrSymbol* s,FILE* f)
{
	GrString_Print(s->s_name,f);
	return 0;
}

static struct  gr_type_ops symbol_type_ops=
{
	.t_hash=(GrHashFunc)GrSymbol_Hash,
	.t_cmp=symbol_cmp,
	.t_cmp_reverse=symbol_cmp_reverse,
	.t_print=(GrPrintFunc)GrSymbol_Print,
};

GrTypeInfo Gr_Type_Symbol=
{
	.t_name="SymbolObject",
	.t_size=sizeof(GrSymbol),
	.t_ops=&symbol_type_ops,
};
