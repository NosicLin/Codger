#ifndef _CODGER_OBJECT_HASH_OBJECT_H_
#define _CODGER_OBJECT_HASH_OBJECT_H_
#include"robject.h"
#define HASH_TABLE_SMALL_TABLE 8
struct hash_entry
{
	ssize_t e_hash;
	Robject* e_key;
	Robject* e_value;
};
typedef struct hash_entry HashEntry;
struct hash_table 
{
	INHERIT_ROBJECT;
	ssize_t t_fill;
	ssize_t t_used;
	ssize_t t_mask;
	struct hash_entry* t_table;
	struct hash_entry t_small_table[HASH_TABLE_SMALL_TABLE];
	int t_flags;
};
typedef struct hash_table HashTable;

/* sucess return HashTable 
 * else return 0
 */
HashTable* hash_new();
int hash_init(HashTable* h); /*TODO*/
void hash_free(HashTable* h);

void hash_clear_cache();
/* return 0 sucess 
 * failed return -1
 */
int hash_set_item(HashTable* h,Robject* key,Robject* value);

/* sucess return h(key)->value
 * if not map(key) return NULL
 * if error return NULL
 */
Robject* hash_get_item(HashTable* h,Robject* key);

/* sucess return entry(key)
 * if not map key , return p, p is not NULL, but p->key is NUL 
 * if error return NULL
 */
HashEntry* hash_get_entry(HashTable* h,Robject* key);

/* sucess return 0
 * error return -1
 * not find return -2
 */
int hash_del_item(HashTable* h,Robject* key);
int hash_print(HashTable* h,FILE* f,int flags);
int hash_bool(HashTable* h);
#ifdef ROBJECT_CAST_DEBUG
static inline Robject* HASH_TO_R(HashTable* h)
{
	assert(robject_type((Robject*)h)==TYPE_HASH);
	return (Robject*)h;
}
static inline HashTable* R_TO_HASH(Robject* r)
{
	assert(robject_type(r)==TYPE_HASH);
	return (HashTable*)r;
}
#else 
#define HASH_TO_R(h) ((Robject*)h)
#define R_TO_HASH(r) ((HashTable*)r)
#endif /*ROBJECT_CAST_DEBUG*/


/* new interface */
static inline int hash_map(HashTable* h,Robject* key,Robject* value)
{
	return hash_set_item(h,key,value);
}
static inline HashEntry* hash_lookup_entry(HashTable* h,Robject* key)
{
	return hash_get_entry(h,key);
}
static inline Robject* hash_lookup(HashTable* h ,Robject* key)
{
	return hash_get_item(h,key);
}

/* if hashtable is mapped key ,return key->value
 * if unmap key, hashtable will map(key,defalut) and defalut will return;
 * if return NULL, some error happened
 */
Robject* hash_lookup_map(HashTable* h,Robject* key,Robject* value);
static inline int hash_unmap(HashTable* h,Robject* key)
{
	return hash_del_item(h,key);
}


/* FIXME may be some day,the follow is useful*/
/* used for module_object,in normal hashmap,for example
 * k1=2,k2=2l, k1 and k2 will map in the same slot which we don't want
 * so used type_map will check the type of key, if type(key1)!=type(key2),
 * they will map differen't in slot. 
 * */
int hash_type_map(HashTable* h,Robject* key,Robject* value);
Robject* hash_type_lookup(HashTable* h,Robject* key);
HashEntry* hash_type_lookup_entry(HashTable* h,Robject* key);
int hash_type_unmap(HashTable* h,Robject* key);
Robject* hash_type_lookup_map(HashTable* h,Robject* key,Robject* defalut);

#endif /*_CODGER_OBJECT_HASH_OBJECT_H_*/


