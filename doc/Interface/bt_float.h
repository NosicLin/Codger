/*constructor*/

/* if nonmemoy return null */ 
BtFloat* btfloat_create(float value);
BtFloat* btfloat_from_str(const char* str);

/* cast */
float btfloat_get_value(BtFloat* bf);
int btfloat_to_int(BtFloat* bf);
BtLong* btfloat_to_btlong(BtFloat* bf);

/* if float is to big to convert int return NULL */
BtInt* btfloat_to_btint(BtFloat* bf);

/* expr */
/*unary expr*/
BtFloat* btfloat_positive(BtFloat* bi);
BtFloat* btfloat_negative(BtFloat* bi);

/*arithmetic expr*/
BtFloat* btfloat_mul(BtFloat* x,BtFloat* y);
BtFloat* btfloat_div(BtFloat* x,BtFloat* y);
BtFloat* btfloat_mod(BtFloat* x,BtFloat* y);
BtFloat* btfloat_plus(BtFloat* x,BtFloat* y);
BtFloat* btfloat_minus(BtFloat* x,BtFloat* y);

/*compare expr*/
BtFloat* btfloat_lt(BtFloat* x,BtFloat* y);
BtFloat* btfloat_le(BtFloat* x,BtFloat* y);
BtFloat* btfloat_eq(BtFloat* x,BtFloat* y);
BtFloat* btfloat_ne(BtFloat* x,BtFloat* y);
BtFloat* btfloat_ge(BtFloat* x,BtFloat* y);
BtFloat* btfloat_gt(BtFloat* x,BtFloat* y);
int btfloat_cmp(BtFloat* x,BtFloat* y);

/*logic expr*/
int btfloat_bool(BtFloat* bi);

/* print */
int btfloat_print(BtFloat* bi,FILE* f,int flags);

