#ifndef _REDY_RTYPE_ARRAY_H_
#define _REDY_RTYPE_ARRAY_H_ 
#include<object/robject.h>
#define SMALL_ARRAY_SIZE 8
#define ARRAY_FLAG_PRINT 0x1
struct  bt_array 
{
	INHERIT_ROBJECT;
	ssize_t a_cap;
	ssize_t a_size;
	int a_flags;
	struct robject** a_objects;
	struct robject* a_small_objects[SMALL_ARRAY_SIZE];
};

typedef struct bt_array BtArray;

#ifdef RTYPE_DEBUG 

static inline BtArray* R_TO_A(Robject* rt)
{
	assert(rt_type(rt)==RT_ARRAY);
	return (BtArray*) rt;
}
static inline Robject* A_TO_R(BtArray* bt)
{
	assert(rt_type((Robject*)bt)==RT_ARRAY);
	return (Robject*)bt;
}
#else 

#define R_TO_A(bt) ((BtArray*)bt)
#define A_TO_R(btl) ((Robject*)btl)

#endif 

/* constructor */
BtArray* btarray_create();
BtArray* btarray_create_size(ssize_t size);

/* destructor */
void btarray_free(BtArray* ba);

/* if return type is int mean:success(0) failed(-1) */
/* if return type is pointer mean:success(Not NULL) falied(NULL) */

/* interface */
int btarray_insert(BtArray* ba,ssize_t index,Robject* item);
int btarray_set_item(BtArray* ba,ssize_t index,Robject* item);
int btarray_push_back(BtArray* ba,Robject* item);
Robject* btarray_get_item(BtArray* ba,ssize_t index);
int btarray_remove(BtArray* ba ,ssize_t index);
BtArray* btarray_plus(BtArray* l,BtArray* r);
static inline ssize_t btarray_size(BtArray* ba) { return ba->a_size; }

static inline int btarray_bool(BtArray* ba)
{
	return ba->a_size!=0;
}
int btarray_print(BtArray* ba,FILE* f,int flags);


#endif 

	
