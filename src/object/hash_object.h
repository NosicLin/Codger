#ifndef _REDY_OBJECT_HASH_OBJECT_H_
#define _REDY_OBJECT_HASH_OBJECT_H_
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
};
typedef struct hash_table HashTable;

/* sucess return HashTable 
 * else return 0
 */
HashTable* hash_new();
void hash_free(HashTable* h);

/* return 0 sucess 
 * failed return -1
 */
int hash_set_item(HashTable* h,Robject* key,Robject* value);

/* sucess return h(key)
 * else return NULL
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


#define HASH_TO_R(h) ((Robject*)h)
#define R_TO_HASH(r) ((HashTable*)r)

#endif /*_REDY_OBJECT_HASH_OBJECT_H_*/


