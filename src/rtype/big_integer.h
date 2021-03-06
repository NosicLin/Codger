#ifndef _REDY_RTYPE_BGINTEGER_H_
#define _REDY_RTYPE_BGINTEGER_H_
#include<stdlib.h>

typedef unsigned short b_unit;
typedef short sb_unit;
typedef unsigned long twob_unit;
typedef long stwob_unit;
struct big_integer
{
	int b_len;
	b_unit b_val[0];
};
typedef struct big_integer BGInteger;

/* implement in bg.c */

/*constructor and deconstructor*/
BGInteger* bg_create_from_int(int value);
BGInteger* bg_create_from_octstr(char* str);
BGInteger* bg_create_from_binstr(char* str);
BGInteger* bg_create_from_decstr(char* str);
BGInteger* bg_create_from_hexstr(char* str);

static inline void bg_free(BGInteger* bg)
{
	free(bg);
}

void bg_print_dec(BGInteger* bg);
void bg_print_bin(BGInteger* bg);

/*normal func*/

/*negative*/
BGInteger* bg_negative(BGInteger* bg);
void bg_self_negative(BGInteger* bg);

/* type cast*/
float bg_to_float(BGInteger* bg);

/* plus minus */
BGInteger* bg_plus(BGInteger* left, BGInteger* right);
BGInteger* bg_minus(BGInteger* left,BGInteger* right);

/*mul div mod */
BGInteger* bg_mul(BGInteger* left,BGInteger* right);
BGInteger* bg_div(BGInteger* left,BGInteger* right);
BGInteger* bg_mod(BGInteger* left,BGInteger* right);

/* left shift right shift*/
BGInteger* bg_lshift(BGInteger* left,BGInteger* right);
BGInteger* bg_rshift(BGInteger* left,BGInteger* right);

/* logic or and xor */
BGInteger* bg_and(BGInteger* left,BGInteger* right);
BGInteger* bg_or(BGInteger* left,BGInteger* right);
BGInteger* bg_xor(BGInteger* left,BGInteger* right);
BGInteger* bg_negated(BGInteger* bg);

/* old interface shouldn't use */
BGInteger* bg_invert(BGInteger* bg);

/* cmp used for gt , ge, eq,le ,lt*/
int bg_cmp(BGInteger* left,BGInteger* right);

/*used for and or not*/
int bg_booleaned(BGInteger* bg);

/* other func */
int bg_overflow_int(BGInteger* bg);
int bg_to_int(BGInteger* bg);

static inline int bg_is_zero(BGInteger* bg)
{
	return bg->b_len==0;
}
static inline int bg_is_negative(BGInteger* bg)
{
	return bg->b_len<0;
}
static inline int bg_size(BGInteger* bg)
{
	return bg->b_len;
}
static  inline int bg_abs_size(BGInteger* bg)
{
	return abs(bg->b_len);
}
static inline void bg_set_size(BGInteger* bg,int len)
{
	bg->b_len=len;
}

#endif 
