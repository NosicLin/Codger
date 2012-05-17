#include"gr_scope.h"
#include<memory/gc.h>
#include<memory/memory.h>
#include<engine/except.h>
#include"gr_string.h"
#include<engine/eg_buildin.h>

GrScope* GrScope_GcNew(GrScope* upper)
{
	GrScope* s=GrGc_New(GrScope,&Gr_Type_Scope);
	if(s==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Scope Object");
		return NULL;
	}
	if(GrScope_Init(s,upper)<0)
	{
		return NULL;
	}
	return s;
}

inline int GrScope_Init(GrScope* s,GrScope* upper)
{
	GrHash* h=GrHash_GcNew();
	if(h==NULL)
	{
		return -1;
	}
	s->s_table=h;
	s->s_upper=upper;
	return 0;
}

int GrScope_GcUpdate(GrScope* s)
{
	if(s->s_upper!=NULL)
	{
		s->s_upper=GrGc_Update(s->s_upper);
	}
	s->s_table=GrGc_Update(s->s_table);
	return 0;
}


static struct gr_type_ops scope_type_ops=
{
	.t_gc_update=(GrGcUpdateFunc) GrScope_GcUpdate,
};


GrTypeInfo Gr_Type_Scope=
{
	.t_name="ScopeObject",
	.t_size=sizeof(GrScope),
	.t_ops=&scope_type_ops,
};


int GrScope_Map(GrScope* s,GrObject* key,GrObject* value)
{
	assert(key);
	assert(GrString_Verify(key));

	GrHash* table=EgCodger_GetBuildin();
	GrHashEntry* entry=GrHash_GetEntry(table,key);

	assert(entry);
	if(GrHashEntry_Valid(entry))
	{
		GrErr_PermFormat("Buildin '%s' Is Protected,Can't Assign To It",
				GR_TO_S(key)->s_value);

	}
	return GrHash_Map(s->s_table,key,value);
}

int GrScope_MapUpper(GrScope* s,GrObject* key,GrObject* value)
{
	assert(value);
	assert(GrString_Verify(key));

	GrHash* table;
	GrScope* cur=s->s_upper;
	GrHashEntry* entry;
	while(cur!=NULL)
	{
		entry=GrHash_GetEntry(cur->s_table,key);
		assert(entry);
		if(entry->e_key==NULL||entry->e_key==Gr_Hash_Dummy)
		{
			cur=cur->s_upper;
			continue;
		}
		entry->e_value=value;
		GrGc_Intercept(cur->s_table,value);
		return 0;
	}

	table=EgCodger_GetBuildin();
	entry=GrHash_GetEntry(table,key);
	assert(entry);
	if(GrHashEntry_Valid(entry))
	{
		GrErr_PermFormat("Buildin '%s' Is Protected,Can't Assign To It",
				GR_TO_S(key)->s_value);

	}

	GrErr_NameFormat("upper Name '%s' Is Not Define",GR_TO_S(key)->s_value);
	return -1;

}

GrObject* GrScope_Lookup(GrScope* s,GrObject* key)
{
	assert(GrString_Verify(key));
	/* look up current scope */
	GrHash* table=s->s_table;
	GrHashEntry* entry=GrHash_GetEntry(table,key);
	assert(entry);
	if(GrHashEntry_Valid(entry))
	{
		assert(entry->e_value);
		return entry->e_value;
	}

	/* look up  buildin */
	table=EgCodger_GetBuildin();
	entry=GrHash_GetEntry(table,key);
	assert(entry);
	if(GrHashEntry_Valid(entry))
	{
		assert(entry->e_value);
		return entry->e_value;
	}

	GrErr_NameFormat("Name '%s' Is Not Define",GR_TO_S(key)->s_value);
	return NULL;

}
GrObject* GrScope_LookupUpper(GrScope* s,GrObject* key)
{
	GrHash* table;
	GrScope* cur=s->s_upper;
	GrHashEntry* entry;
	while(cur!=NULL)
	{
		entry=GrHash_GetEntry(cur->s_table,key);
		if(entry->e_key==NULL||entry->e_key==Gr_Hash_Dummy)
		{
			cur=cur->s_upper;
			continue;
		}
		return entry->e_value;
	}

	table=EgCodger_GetBuildin();
	entry=GrHash_GetEntry(table,key);
	assert(entry);
	if(GrHashEntry_Valid(entry))
	{
		assert(entry->e_value);
		return entry->e_value;
	}

	GrErr_NameFormat("upper Name '%s' Is Not Define",GR_TO_S(key)->s_value);
	return NULL;
}







