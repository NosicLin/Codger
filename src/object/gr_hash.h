#ifndef _CODGER_OBJECT_HASH_OBJECT_H_
#define _CODGER_OBJECT_HASH_OBJECT_H_
#include"gr_object.h"
#define GR_HASH_MIN_SIZE 8

struct gr_hash_entry
{
	ssize_t e_code;
	GrObject* e_key;
	GrObject* e_value;
};
typedef struct gr_hash_entry GrHashEntry;

struct gr_hash;

typedef GrHashEntry* (*GrHashLookUpFunc)(struct gr_hash*,
						GrObject* key,ssize_t code);

struct gr_hash
{
	INHERIT_GROBJECT;
	ssize_t h_fill;   /* key_nu and dummy_nu */
	ssize_t h_used;   /* key_nu */
	ssize_t h_mask;
	struct gr_hash_entry* h_table;
	long h_flags;
	GrHashLookUpFunc h_look_up;
};

typedef struct gr_hash GrHash;


extern GrTypeInfo Gr_Type_Hash;

extern GrObject* Gr_Hash_Dummy;
/* all hash table used gc module for memory alloc, so can't free memory
 * by your self, this is also explain why I don't provide GrHash_Free,
 * if your want to used hash table for another used,not interative with 
 * codger, your can alloc memory from GrMemory module or c lib, and 
 * initialize it with GrHash_Init() interface, when your don't used it 
 * call GrHash_Destruct() interface ,and free it to where it come from 
 */

GrHash* GrHash_GcNew();
GrHash* GrHash_GcNewFlag(long);
int GrHash_Init();

int GrHash_Map(GrHash* h,GrObject* key,GrObject* value);
int GrHash_MapWithNewKey(GrHash* h,GrObject* key,GrObject* value);
GrObject* GrHash_Lookup(GrHash* h,GrObject* key);
GrObject* GrHash_LookupName(GrHash* h,GrObject* key);
GrHashEntry* GrHash_GetEntry(GrHash* h,GrObject* key);

int GrHash_Del(GrHash* h,GrObject* key);
int GrHash_Print(GrHash* h,FILE* f);
int GrHash_Bool(GrHash* h);

int GrHash_Verify(GrObject* h);

static inline int GrHashEntry_Valid(GrHashEntry* h)
{
	return ((h->e_key!=NULL)&&(h->e_key!=Gr_Hash_Dummy));
}

#ifdef GR_HASH_DEBUG
static inline GrObject* HASH_TO_R(GrHash* h)
{
	return (GrObject*)h;
}
static inline GrHash* R_TO_HASH(GrObject* h)
{
	assert(GrHash_Verify(h));
	return (GrHash*)h;
}
#else 
#define HASH_TO_R(x) ((GrObject*)x)
#define R_TO_HASH(x) ((GrHash*)x)
#endif /*GR_HASH_DEBUG*/

#endif /*_CODGER_OBJECT_HASH_OBJECT_H_*/



