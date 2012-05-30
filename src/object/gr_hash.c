#include"gr_hash.h"
#include"string.h"
#include<assert.h>
#include<engine/except.h>
#include<utility_c/marocs.h>
#include<memory/gc.h>
#include<memory/memory.h>
#include"gr_string.h"
#include"gr_consts.h"
#include"gr_util.h"

#define DEFALULT_PERTURB_SHIFT 5
#define GR_HASH_PRINT_FLAG 0x1l
static GrObject __Gr_Hash_Dummy;

GrObject* Gr_Hash_Dummy=&__Gr_Hash_Dummy;

static inline int ht_init(GrHash* h,GrHashLookUpFunc f)
{
	h->h_fill=0;
	h->h_used=0;
	h->h_mask=GR_HASH_MIN_SIZE-1;
	h->h_flags=0;
	h->h_look_up=f;
	h->h_table=GrMem_Alloc(sizeof(GrHashEntry)*GR_HASH_MIN_SIZE);
	if(h->h_table==NULL)
	{
		return -1;
	}

	memset(h->h_table,0,sizeof(GrHashEntry)*GR_HASH_MIN_SIZE);
	return 0;
}


static inline int ht_is_print(GrHash* h)
{
	return  h->h_flags&GR_HASH_PRINT_FLAG;
}
static inline void ht_clr_print(GrHash* h)
{
	h->h_flags=h->h_flags&(~GR_HASH_PRINT_FLAG);
}
static inline void ht_set_print(GrHash* h)
{
	h->h_flags=h->h_flags| GR_HASH_PRINT_FLAG;
}




static inline GrHash* ht_malloc(long flags)
{
	GrHash* h=GrGc_Alloc(GrHash,&Gr_Type_Hash,flags);
	if(h==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For GrHash Object");
	}
	return h;
}

static GrHashEntry* ht_normal_lookup_func(GrHash* h,GrObject* key,
									register ssize_t code)
{

	register size_t mask=(size_t)h->h_mask;
	register size_t i=code&mask;
	register size_t perturb;


	/* first look up entry by mod */
	register GrHashEntry* table=h->h_table;
	register GrHashEntry* p=&table[i];
	GrHashEntry* freeslot=0;
	int cmp;

	/* if p->e_key is null, mean this slot is free,so just return it */
	if(p->e_key==NULL)
	{
		return p;
	}
	/* if p->e_key is Gr_Hash_Dummy, mean this slot used before,but deleted */
	if(p->e_key==Gr_Hash_Dummy)
	{
		freeslot=p;
	}
	/* if find a slot is used, compare it */
	else if(p->e_code==code)
	{
		cmp=GrObject_RichEq(key,p->e_key);
		if(cmp<0)
		{
			/* error happend*/
			return NULL;
		}
		if(cmp>0)
		{
			return p;
		}
	}

	/* open address confilt solve*/
	for(perturb=code;;perturb>>=DEFALULT_PERTURB_SHIFT)
	{
		
		i=(i<<2)+i+1+perturb;
		p=&table[i&mask];

		if(p->e_key==NULL)
		{
			return freeslot==NULL?p:freeslot;
		}
		if(p->e_key==Gr_Hash_Dummy&&freeslot!=NULL)
		{
			freeslot=p;
		}
		else if(p->e_code==code)
		{
			cmp=GrObject_RichEq(key,p->e_key);
			if(cmp<0)
			{
				/* error happend*/
				return NULL;
			}
			if(cmp>0)
			{
				return p;
			}
		}
	}
	assert(0); /* never reached*/
	return NULL;
}

static int  ht_simple_insert(GrHash* h,GrObject* key,ssize_t code,GrObject* value)
{
	size_t mask=(size_t)h->h_mask;
	size_t i=code&mask;
	size_t perturb=code;

	GrHashEntry* table=h->h_table;
	GrHashEntry* p=&table[i];
	while(p->e_key!=NULL)
	{
		i=(i<<2)+i+1+perturb;
		perturb>>=DEFALULT_PERTURB_SHIFT;
		p=&table[i&mask];
	}
	assert(p->e_value==NULL);
	p->e_key=key;
	p->e_value=value;
	p->e_code=code;

	h->h_fill++;
	h->h_used++;

	return 0;
}

static int ht_resize(GrHash* h,ssize_t minisize)
{
	register GrHashEntry* old_table=0;
	register GrHashEntry* new_table=0;
	register GrHashEntry* p=0;
	ssize_t new_size=GR_HASH_MIN_SIZE;
	ssize_t i;
	while(new_size<minisize&&new_size>0) new_size<<=1;

	if(new_size<0)
	{
		GrErr_MemFormat("Can't Alloc Memory For Resize Hash Object");
		return -1;
	}

	new_table=GrMem_Alloc(sizeof(GrHashEntry)*new_size);
	if(new_table==NULL)
	{
		GrErr_MemFormat("Can't Alloc Memory For Resize Hash Object");
		return -1;
	}

	old_table=h->h_table;

	h->h_table=new_table;
	h->h_mask=new_size-1;
	h->h_used=0;

	i=h->h_fill;
	h->h_fill=0;
	memset(new_table,0,sizeof(GrHashEntry)*new_size);

	for(p=old_table;i>0;p++)
	{
		if(p->e_key!=NULL)
		{
			i--;
			if(p->e_key!=Gr_Hash_Dummy)
			{
				ht_simple_insert(h,p->e_key,p->e_code,p->e_value);
			}
		}
	}
	GrMem_Free(old_table);

	return 0;
}


inline int GrHash_Init(GrHash* h)
{
	return ht_init(h,ht_normal_lookup_func);
}

GrHash* GrHash_GcNew()
{
	GrHash* h=ht_malloc(GRGC_HEAP_YOUNG);
	if(h==NULL)
	{
		return NULL;
	}
	if(ht_init(h,ht_normal_lookup_func)<0)
	{
		return NULL;
	}
	return h;
}
GrHash* GrHash_GcNewFlag(long flags)
{
	GrHash* h=ht_malloc(flags);
	if(h==NULL)
	{
		return NULL;
	}
	if(ht_init(h,ht_normal_lookup_func)<0)
	{
		return NULL;
	}
	return h;
}

void GrHash_Destruct(GrHash* h)
{
	if(h->h_table!=NULL)
	{
		GrMem_Free(h->h_table);
	}
}


int GrHash_Map(GrHash* h,GrObject* key,GrObject* value)
{
	assert(value);
	ssize_t code=GrObject_Hash(key);
	ssize_t used=h->h_used;
	int ret=0;
	GrHashEntry* p=h->h_look_up(h,key,code);
	if(p==NULL)
	{
		return -1;
	}
	if(p->e_key==NULL)
	{
		h->h_fill++;
		h->h_used++;
	}
	if(p->e_key==Gr_Hash_Dummy)
	{
		h->h_used++;
		p->e_key=NULL;
	}
	if(p->e_key==NULL) p->e_key=key;
	p->e_value=value;
	p->e_code=code;

	/* check space, make sure 1/3 free slot */
	if(used<h->h_used &&  h->h_fill*3 >h->h_mask*2)
	{
		ret=ht_resize(h,(h->h_used>50000?2:4)*h->h_used);
	}
	GrGc_Intercept(h,key);
	GrGc_Intercept(h,value);
	return ret;
}

int GrHash_MapWithNewKey(GrHash* h,GrObject* key,GrObject* value)
{
	assert(value);
	ssize_t code=GrObject_Hash(key);
	ssize_t used=h->h_used;
	int ret=0;
	GrHashEntry* p=h->h_look_up(h,key,code);
	if(p==NULL)
	{
		return -1;
	}
	if(p->e_key==NULL)
	{
		h->h_fill++;
		h->h_used++;
	}
	if(p->e_key==Gr_Hash_Dummy)
	{
		h->h_used++;
	}
	p->e_key=key;
	p->e_value=value;
	p->e_code=code;

	/* check space, make sure 1/3 free slot */
	if(used<h->h_used &&  h->h_fill*3 >h->h_mask*2)
	{
		ret=ht_resize(h,(h->h_used>50000?2:4)*h->h_used);
	}
	GrGc_Intercept(h,key);
	GrGc_Intercept(h,value);
	return ret;
}



GrObject* GrHash_Lookup(GrHash* h,GrObject* key)
{
	ssize_t code=GrObject_Hash(key);
	if(code==-1) 
	{
		return NULL;
	}
	GrHashEntry* p=h->h_look_up(h,key,code);
	if(p==NULL)
	{
		return NULL;
	}
	if(p->e_key==NULL||p->e_key==Gr_Hash_Dummy)
	{
		GrErr_KeyFormat("Hash Object Not Map Key");
		return NULL;
	}
	assert(p->e_value);
	return p->e_value;
}
GrObject* GrHash_LookupName(GrHash* h,GrObject* key)
{
	assert(GrString_Verify(key));
	ssize_t code=GrObject_Hash(key);
	GrHashEntry* p=h->h_look_up(h,key,code);
	if(p==NULL)
	{
		return NULL;
	}
	if(p->e_key==NULL||p->e_key==Gr_Hash_Dummy)
	{
		GrErr_NameFormat("Name '%s' Is Not Define",GR_TO_S(key)->s_value);
		return NULL;
	}
	assert(p->e_value);
	return p->e_value;
}


GrHashEntry* GrHash_GetEntry(GrHash* h,GrObject* key)
{
	ssize_t code=GrObject_Hash(key);
	if(code==-1)
	{
		return NULL;
	}
	return h->h_look_up(h,key,code);
}

int GrHash_Del(GrHash* h,GrObject* key)
{
	ssize_t code=GrObject_Hash(key);

	if(code==-1)
	{
		return -1;
	}
	GrHashEntry* p=h->h_look_up(h,key,code);
	if(p==NULL)
	{
		return -1;
	}
	if(p->e_key==NULL||p->e_key==Gr_Hash_Dummy)
	{
		GrErr_KeyFormat("Hash Object Not Map Key");
		return -1;
	}
	p->e_key=Gr_Hash_Dummy;
	p->e_value=NULL;
	return 0;
}

int GrHash_Bool(GrHash* h)
{
	return h->h_used!=0;
}

int GrHash_Print(GrHash* h,FILE* f)
{
	ssize_t i=h->h_used;
	GrHashEntry* table=h->h_table;
	GrHashEntry* p=&table[0];
	if(i==0)
	{
		fprintf(f,"{}");
		return 0;
	}
	if(ht_is_print(h))
	{
		fprintf(f,"{...}");
		return 0;
	}
	else 
	{
		ht_set_print(h);
	}
	fprintf(f,"{\n");

	int print_first=0;
	while(!print_first)
	{
		if(p->e_key==NULL||p->e_key==Gr_Hash_Dummy)
		{
			p++;
			continue;
		}
		i--;
		fprintf(f,"\t");
		GrObject_Print(p->e_key,f,0);
		fprintf(f,"  =>  ");
		assert(p->e_value);
		GrObject_Print(p->e_value,f,0);
		print_first=1;
		p++;
	}
	while(i>0)
	{
		if(p->e_key==NULL||p->e_key==Gr_Hash_Dummy)
		{
			p++;
			continue;
		}
		i--;
		fprintf(f,"\n");
		fprintf(f,"\t");
		GrObject_Print(p->e_key,f,0);
		fprintf(f,"  =>  ");
		assert(p->e_value);
		GrObject_Print(p->e_value,f,0);
		p++;
	}
	fprintf(f,"\n}");

	ht_clr_print(h);
	return 0;
}

int GrHash_GcUpdate(GrHash* h)
{
	ssize_t used=h->h_used;
	ssize_t i=0;
	struct gr_hash_entry* entry=h->h_table;
	//printf("hash used =%d \n",used);
	while(i<used)
	{
		assert(i<=h->h_mask);
		if(GrHashEntry_Valid(entry))
		{
			entry->e_key=GrGc_Update(entry->e_key);
			entry->e_value=GrGc_Update(entry->e_value);
			i++;
		}
		entry++;
	}
	return 0;
}


static struct gr_type_ops hash_type_ops=
{
	.t_hash=GrUtil_HashNotSupport,
	.t_print=(GrPrintFunc)GrHash_Print,
	.t_destruct=(GrDestructFunc)GrHash_Destruct,
	.t_gc_update=(GrGcUpdateFunc)GrHash_GcUpdate,

	.t_set_item=(GrSetItemFunc)GrHash_Map,
	.t_get_item=(GrGetItemFunc)GrHash_Lookup,
	.t_bool=(GrBoolFunc)GrHash_Bool,
};

struct gr_type_info Gr_Type_Hash=
{
	.t_name="HashObject",
	.t_size=sizeof(GrHash),
	.t_ops=&hash_type_ops,
};


