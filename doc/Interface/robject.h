/*robject interface*/

/* constructor */
Robject* robject_new(OBJECT_TYPE_NAME,RTypeObject*);
void robject_destroy(Robject* r); /*release resource,but not self*/
void robject_free(Robject* r); 	/* free self */ 

/*  normal func*/
rssize_t robject_refcnt(Robject* r);
void robject_incref(Robject* r);
void robject_decref(Robject* r);
const char* robject_name(Robject* r);
int robject_type(Robject* r);


/* expr interface:*/
/* if TypeObject  not implement the method 
 * it will raise  TypeErrorException 
 * and return NULL
 */
/*unary expr*/
Robject* robject_posivtive(Robject* r);
Robject* robject_negative(Robject* r);

/*arithmetic expr*/
Robject* robject_mul(Robject* x,Robject* y);
Robject* robject_mod(Robject* x,Robject* y);
Robject* robject_div(Robject* x,Robject* y);
Robject* robject_plus(Robject* x,Robject* y);
Robject* robject_minus(Robject* x,Robject* y);

/*bitwise expr*/
Robject* robject_lshift(Robject* x,Robject* y);
Robject* robject_rshift(Robject* x,Robject* y);
Robject* robject_and(Robject* x,Robject* y);
Robject* robject_or(Robject* x,Robject* y);
Robject* robject_xor(Robject* x,Robject* y);
Robject* robject_negated(Robject* r);

/*compare expr*/
int robject_lt(Robject* x,Robject* y);
int robject_le(Robject* x,Robject* y);
int robject_gt(Robject* x,Robject* y);
int robject_ge(Robject* x,Robject* y);

/* if TypeObject x not implement the eq and ne method 
 * we privide defalut action  by compare the object address
 * if addr(x)==addr(y) return true;
 * else return false;
 */
int robject_eq(Robject* x,Robject* y);
int robject_ne(Robject* x,Robject* y);

/*logic expr*/
/* if TypeObject r not implement bool method 
 * we privide defalut action by always return true
 */
int robject_bool(Robject* r);

/* set and get item */
Robject* robject_set_item(Robject* r,Robject* index,Robject* item);
Robject* robject_get_item(Robject* r,Robject* index);

/* iterator */
Robject* robject_iter(Robject* r);

/* print */
/* if TypeObject r not implement print method
 * we privide defalut action by output r address
 */
int  robject_print(Robject* r,FILE* f,int flags);

/* call */
Robject* robject_call(Robject* r);

/*low level compare*/
/* -2 CMP_NOT_SUPPORT
 * -1 error 
 * 0 false
 * 1 other 
 */
int robject_cmp(Robject* x,Robject* y,int op)
