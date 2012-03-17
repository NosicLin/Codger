#ifndef _REDY_RTYPE_COMMON_H_
#define _REDY_RTYPE_COMMON_H_
#include"robject.h"

/*-------------------int part-----------------------*/
/*arithmetic * / % */
/* int * float=float*/
Robject* r_mul_int_float(Robject* left,Robject* right);

/*int * long =long*/
Robject* r_mul_int_long(Robject* left,Robject* right);

/*int/float=float*/
Robject* r_div_int_float(Robject* left,Robject* right);

/*int/long=long*/
Robject* r_div_int_long(Robject* left,Robject* right);

/*int%long=long*/
Robject* r_mod_int_long(Robject* left,Robject* right);


/*arithmetic + - */
/*int+float=float*/
Robject* r_plus_int_float(Robject* left,Robject* right);

/*int+long=long*/
Robject* r_plus_int_long(Robject* left,Robject* right);

/*int-float=flaot*/
Robject* r_minus_int_float(Robject* left,Robject* right);

/*int-long=long*/
Robject* r_minus_int_long(Robject* left,Robject* right);

/* bit_operator left shift and right shift */
/*int << long = long*/
Robject* r_lshift_int_long(Robject* left,Robject* right);
/*int >> long=long */
Robject* r_rshift_int_long(Robject* left,Robject* right);

/*compare operator*/
Robject* r_cmp_int_float(Robject* left,Robject* right);
Robject* r_cmp_int_long(Robject* left,Robject* right);

/*bit_operator & | ^ ~ */
/*int&long=long*/
Robject* r_and_int_long(Robject* left,Robject* right);
/*int|long=long*/
Robject* r_or_int_long(Robject* left,Robject* right);
/*int^long=long*/
Robject* r_xor_int_long(Robject* left,Robject* right);


/*------------------float parts--------------------*/

/*arithmetic * / % */

/* float * int =float */
Robject* r_mul_float_int(Robject* left, Robject* right);

/* float * long =long */
Robject* r_mul_float_long(Robject* left, Robject* right);

/* float / int =float */
Robject* r_div_float_int(Robject* left, Robject* right);

/* float / long =float*/
Robject* r_div_float_long(Robject* left, Robject* right);



/*arithmetic + - */
/* float + int =float */
Robject* r_plus_float_int(Robject* left, Robject* right);

/* float + long =float*/
Robject* r_plus_float_long(Robject* left, Robject* right);

/* float - int =float */
Robject* r_minus_float_int(Robject* left, Robject* right);

/* float - long =float*/
Robject* r_minus_float_long(Robject* left, Robject* right);

/* compare operator */
/* float cmp int =int */
Robject* r_cmp_float_int(Robject* left, Robject* right);
/* float cmp long=int */
Robject* r_cmp_float_long(Robject* left, Robject* right);



/*------------------long parts------------------------*/

/* arithmetic * / % */
/* long * float =float */
Robject* r_mul_long_float(Robject* left,Robject* right);

/* long * int = long */
Robject* r_mul_long_int(Robject* left,Robject* right);

/* long / float =float */
Robject* r_div_long_float(Robject* left,Robject* right);

/* long / int =long */
Robject* r_div_long_int(Robject* left,Robject* right);

/* long % int =long */
Robject* r_mod_long_int(Robject* left,Robject* right);


/*arithmetic + - */
/* long - float =float */
Robject* r_minus_long_float(Robject* left,Robject* right);

/* long - int = long */
Robject* r_minus_long_int(Robject* left,Robject* right);

/* long + float =float */
Robject* r_plus_long_float(Robject* left,Robject* right);

/* long + int =long */
Robject* r_plus_long_int(Robject* left,Robject* right);


/* shift operator << >> */

/* long <<  int = long */
Robject* r_lshift_long_int(Robject* left,Robject* right);

/* long >>  int = long */
Robject* r_rshift_long_int(Robject* left,Robject* right);

/* cmp operator */
Robject* r_cmp_long_int(Robject* left,Robject* right);
Robject* r_cmp_long_float(Robject* left,Robject* right);


/* bitwise operator  & | ^ */

/* long | int =long */
Robject* r_or_long_int(Robject* left,Robject* right);

/* long & int =long */
Robject* r_and_long_int(Robject* left,Robject* right);

/* long ^ int =long */
Robject* r_xor_long_int(Robject* left,Robject* right);
#endif 
