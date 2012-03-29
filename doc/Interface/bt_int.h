/* base type int interface*/
/* all the func not raise execption*/
/*constructor*/

BtInt* btint_create(int value);
BtInt* btint_from_str(const char* str);

/* cast */
int btint_get_value(BtInt* i);
BtLong* btint_to_btlong(BtInt* i);
BtFloat* btint_to_btfloat(BtInt* i);

/* expr */
/*unary expr*/
BtInt* btint_positive(BtInt* bi);
BtInt* btint_negative(BtInt* bi);
BtInt* btint_negated(BtInt* bi);

/*arithmetic expr*/
BtInt* btint_mul(BtInt* x,BtInt* y);
BtInt* btint_div(BtInt* x,BtInt* y);
BtInt* btint_mod(BtInt* x,BtInt* y);
BtInt* btint_plus(BtInt* x,BtInt* y);
BtInt* btint_minus(BtInt* x,BtInt* y);

/*bitwise expr*/
BtInt* btint_lshift(BtInt* x,BtInt* y);
BtInt* btint_rshift(BtInt* x,BtInt* y);
BtInt* btint_or(BtInt* x,BtInt* y);
BtInt* btint_xor(BtInt* x,BtInt* y);
BtInt* btint_and(BtInt* x,BtInt* y);

/*compare expr*/
BtInt* btint_lt(BtInt* x,BtInt* y);
BtInt* btint_le(BtInt* x,BtInt* y);
BtInt* btint_eq(BtInt* x,BtInt* y);
BtInt* btint_ne(BtInt* x,BtInt* y);
BtInt* btint_ge(BtInt* x,BtInt* y);
BtInt* btint_gt(BtInt* x,BtInt* y);
int btint_cmp(BtInt* x,BtInt* y,int op);

/*logic expr*/
int btint_bool(BtInt* bi);

/*hash code*/
rssize_t btint_hash(BtInt* bi);

/* print */
int btint_print(BtInt* bi,FILE* f,int flags);

