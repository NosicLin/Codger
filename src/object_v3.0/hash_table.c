#include"hash_table.h"
#include<rstd/redy_std.h>
#include<string.h>
#include<assert.h>
#include<vm/except.h>
#include<utility_c/marocs.h>

#define HASH_SMALL_TABLE_MEM_INIT(h) \
	do{ \
		memset(h->t_small_table,0,sizeof(HashEntry)*HASH_TABLE_SMALL_TABLE);\
	}while(0) 

#define HASH_TABLE_INIT(h) \
	do{ \
		HASH_SMALL_TABLE_MEM_INIT(h); \
		h->t_table=h->t_small_table; \
		h->t_mask=HASH_TABLE_SMALL_TABLE-1;  \
		h->t_fill=0; \
		h->t_used=0; \
		h->t_flags=0; \
	}while(0)

#define DEFALULT_PERTURB_SHIFT 5
#define HASH_MAX_CACHE 200

#define HASH_PRINT_FLAG 0x1 

static inline int ht_is_print(HashTable* h)
{
	return  h->t_flags&HASH_PRINT_FLAG;
}
static inline void ht_clr_print(HashTable* h)
{
	h->t_flags=h->t_flags&(~HASH_PRINT_FLAG);
}
static inline void ht_set_print(HashTable* h)
{
	h->t_flags=h->t_flags| HASH_PRINT_FLAG;
}


	


static HashTable* s_htable_cache[HASH_MAX_CACHE];
static int s_cache_free=0;

/*dummy object*/
static void dummy_free(Robject* dummy)
{
	BUG("free dummy");
}
static struct object_ops dummy_object_ops=
{
	.ro_free=dummy_free,
};
static TypeObject type_dummy=
{
	.t_name="dummy",
	.t_object_funcs=&dummy_object_ops,
	.t_type=TYPE_UNKOWN,
};
static Robject __dummy=
{
	.r_ref=1,
	.r_type=&type_dummy,
};
static Robject* dummy=&__dummy;



TypeObject hash_type;
HashTable* hash_new()
{
	HashTable* ret=0;
	assert(s_cache_free>=0);
	if(s_cache_free)
	{
		ret=s_htable_cache[--s_cache_free];
	}
	else
	{
		ret=robject_new(HashTable,&hash_type);
	}
	if(ret==NULL)
	{
		ryerr_nomemory();
		return NULL;
	}
	robject_initref(HASH_TO_R(ret));
	HASH_TABLE_INIT(ret);
	return ret;
}
void hash_free(HashTable* h)
{
	robject_addref(HASH_TO_R(h));
	ssize_t i=h->t_fill;
	HashEntry* p=h->t_table;
	assert(p);
	while(i)
	{
		if(p->e_key!=NULL)
		{
			--i;
			if(p->e_key==dummy)
			{
				robject_release(dummy);
			}
			else
			{
				robject_release(p->e_key);
				robject_release(p->e_value);
			}
		}
		p++;
	}
	if(h->t_table!=h->t_small_table)
	{
		ry_free(h->t_table);
	}
	if(s_cache_free<HASH_MAX_CACHE)
	{
		s_htable_cache[s_cache_free++]=h;
	}
	else
	{
		assert(robject_refcnt(HASH_TO_R(h))==1);
		ry_free(h);
	}
}
static HashEntry* ht_look_up(HashTable* h,Robject* key,ssize_t hash)
{
	size_t mask=(size_t)h->t_mask;
	size_t i=hash&mask;
	size_t perturb;

	HashEntry* table=h->t_table;
	HashEntry* p=&table[i];
	HashEntry* freeslot=0;
	int cmp;

	if(p->e_key==NULL)
	{
		return p;
	}
	if(p->e_key==dummy)
	{
		freeslot=p;
	}
	else if(p->e_hash==hash)
	{
		cmp=robject_richcmp(key,p->e_key,CMP_EQ);
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

	for(perturb=hash;;perturb>>=DEFALULT_PERTURB_SHIFT)
	{
		
		i=(i<<2)+i+1+perturb;
		p=&table[i&mask];

		/*
		printf("cur pos=%d\n",i&mask);
		printf("fill=%d\n",h->t_fill);
		printf("used=%d\n",h->t_used);
		*/

		if(p->e_key==NULL)
		{
			return freeslot==NULL?p:freeslot;
		}
		if(p->e_key==dummy&&freeslot!=NULL)
		{
			freeslot=p;
		}
		else if(p->e_hash==hash)
		{
			cmp=robject_richcmp(key,p->e_key,CMP_EQ);
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


/* if error return -1
 * else return 0;
 */
static int ht_insert(HashTable* h,Robject* key,ssize_t hash,Robject* value)
{
	HashEntry* p=ht_look_up(h,key,hash);
	if(p==NULL)
	{
		return -1;
	}
	if(p->e_key==NULL)
	{
		h->t_fill++;
	}
	robject_addref(key);
	robject_addref(value);
	if(p->e_key==dummy)
	{
		robject_release(dummy);
		assert(p->e_value==NULL);
		p->e_key=NULL;
	}
	if(p->e_key!=NULL)
	{
		robject_release(p->e_key);
		assert(p->e_value);
		robject_release(p->e_value);
	}
	else
	{
		h->t_used++;
	}
	p->e_key=key;
	p->e_value=value;
	p->e_hash=hash;
	return 0;
}

Robject* hash_get_item(HashTable* h,Robject* key)
{
	ssize_t hash=robject_hash(key);
	if(hash==-1)
	{
		/* error happend*/
		return NULL;
	}
	HashEntry* p=ht_look_up(h,key,hash);
	if(p==NULL)
	{
		return NULL;
	}
	if(p->e_key==NULL||p->e_key==dummy)
	{
		return NULL;
	}
	Robject* value=p->e_value;
	robject_addref(value);
	return value;
}
HashEntry* hash_get_entry(HashTable* h,Robject* key)
{
	ssize_t hash=robject_hash(key);
	if(hash==-1)
	{
		return NULL;
	}
	HashEntry* p=ht_look_up(h,key,hash);
	return p;
}

static int  ht_simple_insert(HashTable* h,Robject* key,ssize_t hash,Robject* value)
{
	size_t mask=(size_t)h->t_mask;
	size_t i=hash&mask;
	size_t perturb=hash;

	HashEntry* table=h->t_table;
	HashEntry* p=&table[i];
	while(p->e_key!=NULL)
	{
		i=(i<<2)+i+1+perturb;
		perturb>>=DEFALULT_PERTURB_SHIFT;
		p=&table[i&mask];
	}
	assert(p->e_value==NULL);
	p->e_key=key;
	p->e_value=value;
	p->e_hash=hash;

	h->t_fill++;
	h->t_used++;

	return 0;
}



int ht_resize(HashTable* h,ssize_t minisize)
{
	HashEntry* old_table=0;
	HashEntry* new_table=0;
	HashEntry* p=0;
	HashEntry small_copy[HASH_TABLE_SMALL_TABLE];
	int used_small_table=h->t_table==h->t_small_table;
	ssize_t new_size=HASH_TABLE_SMALL_TABLE;
	ssize_t i;
	while(new_size<minisize&&new_size>0) new_size<<=1;

	if(new_size==HASH_TABLE_SMALL_TABLE)
	{
		if(used_small_table)
		{
			old_table=small_copy;
			new_table=h->t_small_table;
			memcpy(old_table,new_table,sizeof(HashEntry)*HASH_TABLE_SMALL_TABLE);

		}
		else 
		{
			new_table=h->t_small_table;
			old_table=h->t_table;
		}
	}
	else
	{
		new_table=ry_malloc(sizeof(HashEntry)*new_size);
		if(new_table==NULL)
		{
			ryerr_nomemory();
			return -1;
		}
		old_table=h->t_table;
	}
	h->t_table=new_table;
	h->t_mask=new_size-1;
	h->t_used=0;

	i=h->t_fill;
	h->t_fill=0;
	memset(new_table,0,sizeof(HashEntry)*new_size);

	for(p=old_table;i>0;p++)
	{
		if(p->e_key!=NULL)
		{
			i--;
			if(p->e_key==dummy)
			{
				assert(p->e_value==NULL);
				robject_release(dummy);
			}
			else
			{
				ht_simple_insert(h,p->e_key,p->e_hash,p->e_value);
			}
		}
	}
	if(!used_small_table)
	{
		ry_free(old_table);
	}

	return 0;
}




int hash_set_item(HashTable* h,Robject* key,Robject* value)
{
	ssize_t hash=robject_hash(key);
	if(hash==-1)
	{
		return -1;
	}
	ssize_t used=h->t_used;
	int ret;
	ret=ht_insert(h,key,hash,value);
	if(ret<0)
	{
		return  -1;
	}
	if(used<h->t_used &&  h->t_fill*3 >h->t_mask*2)
	{
		ret=ht_resize(h,(h->t_used>50000?2:4)*h->t_used);
	}
	return ret;
}

int hash_del_item(HashTable* h,Robject* key)
{
	ssize_t hash=robject_hash(key);
	if(hash==-1)
	{
		return -1;
	}
	HashEntry* p=ht_look_up(h,key,hash);
	assert(p!=NULL);

	if(p->e_key==NULL&&p->e_key==dummy)
	{
		return -2;
	}

	Robject* old_key=p->e_key;
	robject_addref(dummy);
	p->e_key=dummy;
	robject_release(old_key);
	assert(p->e_value);
	robject_release(p->e_value);
	p->e_value=0;
	return 0;
}
inline int hash_bool(HashTable* h)
{
	if(h->t_used==0)
	{
		return 0;
	}
	return 1;
}

int hash_print(HashTable* h,FILE* f,int flags)
{
	flags=flags&~PRINT_FLAGS_NEWLINE;
	ssize_t i=h->t_used;
	HashEntry* table=h->t_table;
	HashEntry* p=&table[0];
	if(i==0)
	{
		printf("{}");
		return 0;
	}
	if(ht_is_print(h))
	{
		printf("{...}");
		return 0;
	}
	else 
	{
		ht_set_print(h);
	}
	printf("{");

	int print_first=0;
	while(!print_first)
	{
		if(p->e_key==NULL||p->e_key==dummy)
		{
			continue;
			p++;
		}
		i--;
		robject_print(p->e_key,f,flags);
		printf("->");
		assert(p->e_value);
		robject_print(p->e_value,f,flags);
		print_first=1;
		p++;
	}
	while(i>0)
	{
		if(p->e_key==NULL||p->e_key==dummy)
		{
			p++;
			continue;
		}
		i--;
		printf(",");
		robject_print(p->e_key,f,flags);
		printf("->");
		assert(p->e_value);
		robject_print(p->e_value,f,flags);
		p++;
	}
	printf("}");

	ht_clr_print(h);
	return 0;
}







static Robject* ht_get_item(Robject* r,Robject* key)
{
	HashTable* h=R_TO_HASH(r);
	ssize_t hash=robject_hash(key);
	if(hash==-1)
	{
		/*hash error*/
		return NULL;
	}
	HashEntry* p=ht_look_up(h,key,hash);
	if(p==NULL)
	{
		/* look up error*/
		return NULL;
	}
	if(p->e_key==NULL||p->e_key==dummy)
	{
		except_key_err_format("key not map");
		return NULL;
	}
	assert(p->e_value);
	robject_addref(p->e_value);
	return p->e_value;

}	
static int ht_set_item(Robject* r,Robject* key,Robject* value)
{
	HashTable* h=R_TO_HASH(r);
	ssize_t hash=robject_hash(key);
	if(hash==-1)
	{
		return -1;
	}
	int ret=ht_insert(h,key,hash,value);
	return ret;
}

static int ht_bool(Robject* r)
{
	HashTable* h=R_TO_HASH(r);
	return hash_bool(h);
}
static Robject* ht_iter(Robject* r)
{
	TODO("HashTable Iterator");
	return NULL;
}
static int  ht_print(Robject* r,FILE* f,int flags)
{
	HashTable* h=R_TO_HASH(r);
	return hash_print(h,f,flags);
}
static void ht_free(Robject* r)
{
	HashTable* h=R_TO_HASH(r);
	hash_free(h);
}


struct expr_ops ht_expr_ops=
{
	.ro_get_item=ht_get_item,
	.ro_set_item=ht_set_item,
	.ro_bool=ht_bool,
};

struct object_ops hash_object_ops=
{
	.ro_free=ht_free,
};

struct type_object hash_type=
{
	.t_name="HashTable",
	.t_type=TYPE_HASH,
	.t_expr_funcs=&ht_expr_ops,
	.t_object_funcs=&hash_object_ops,
	//	.t_rich_cmp=0,
	.t_print=ht_print,
	.t_iter=ht_iter,
};












