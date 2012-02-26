#ifndef _REDY_LEXICAL_SL_STATE_H_
#define _REDY_LEXICAL_SL_STATE_H_
#include "lexical.h"

/* integer parts*/
extern struct state ist_long;
extern struct state ist_dec;
extern struct state ist_oct;
extern struct state ist_bin;
extern struct state ist_hex;
extern struct state ist_hex_begin;
extern struct state ist_bin_begin;
extern struct state ist_oct_begin;
extern struct state ist_int_prefix;
extern struct state ist_begin;

/* float parts*/
extern struct state ft_begin;
extern struct state ft_frac_begin;
extern struct state ft_int_part;
extern struct state ft_fraction;
extern struct state ft_exp_begin;
extern struct state ft_exp_sign;
extern struct state ft_exponent;


/*number parts*/
/*number merge float and integer*/
extern struct state nu_begin;
extern struct state nu_zero;
extern struct state nu_oct;
extern struct state nu_number;

#endif /*_REDY_LEXICAL_SL_STATE_H_*/
