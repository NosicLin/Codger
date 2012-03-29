#ifndef _REDY_RTYPE_ARRAY_H_
#define _REDY_RTYPE_ARRAY_H_ 
#include"robject.h"

struct  bt_array 
{
	struct robject a_base;
	int a_cap;
	int a_size;
	struct robject** a_objects;
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
BtArray* bt_array_malloc(int cap);
BtArray* bt_array_create();

/* destructor */
void bt_array_free(BtArray* ba);

/* interface */
void bt_array_insert(BtArray* ba,int index,Robject* item);
void bt_array_set_item(BtArray* ba,int index,Robject* item);
void bt_array_push_back(BtArray* ba,Robject* item);
Robject* bt_array_get_item(BtArray* ba,int index);
void bt_array_remove(BtArray* ba ,int index);
BtArray* bt_array_merge(BtArray* l,BtArray* r);


#endif 

	
