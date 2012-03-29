/* base type long interface*/
/* all the func not raise execption*/
/*constructor*/

BtLong* btlong_from_int(int value);
BtLong* btlong_from_str(const char* str);

/* cast */
/* if long is to large to convert to int return NULL*/
BtInt* btlong_to_btint(BtLong* l);
/* if long is to large to convert to float return NULL*/
BtFloat* btlong_to_btfloat(BtLong* l);

/* expr */
/*unary expr*/
BtLong* btlong_positive(BtLong* bl);
BtLong* btlong_negative(BtLong* bl);
BtLong* btlong_negated(BtLong* bl);

/*arithmetic expr*/
BtLong* btlong_mul(BtLong* x,BtLong* y);
BtLong* btlong_div(BtLong* x,BtLong* y);
BtLong* btlong_mod(BtLong* x,BtLong* y);
BtLong* btlong_plus(BtLong* x,BtLong* y);
BtLong* btlong_minus(BtLong* x,BtLong* y);

/*bitwise expr*/
BtLong* btlong_lshift(BtLong* x,int y);
BtLong* btlong_rshift(BtLong* x,int y);
BtLong* btlong_or(BtLong* x,BtLong* y);
BtLong* btlong_xor(BtLong* x,BtLong* y);
BtLong* btlong_and(BtLong* x,BtLong* y);

/*compare expr*/
BtLong* btlong_lt(BtLong* x,BtLong* y);
BtLong* btlong_le(BtLong* x,BtLong* y);
BtLong* btlong_eq(BtLong* x,BtLong* y);
BtLong* btlong_ne(BtLong* x,BtLong* y);
BtLong* btlong_ge(BtLong* x,BtLong* y);
BtLong* btlong_gt(BtLong* x,BtLong* y);
int btlong_cmp(BtLong* x,BtLong* y,int op);

/*logic expr*/
int btlong_bool(BtLong* bl);

/*hash code*/
rssize_t btlong_hash(BtLong* bl);

/* print */
int btlong_print(BtLong* bi,FILE* f,int flags);

