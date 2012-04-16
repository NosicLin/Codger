#ifndef _REDY_LEXICAL_SL_STATE_H_
#define _REDY_LEXICAL_SL_STATE_H_
#include "lexical.h"
/*string parts*/
extern struct state st_begin;
extern struct state st_string;
extern struct state st_esc;
extern struct state st_end;
/*identifier parts*/
extern struct state id_begin;
extern struct state id_identifier;
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


/*operator parts*/
extern struct state op_begin;
extern struct state op_comma;
extern struct state op_period;
extern struct state op_reverse;
extern struct state op_l_rb;
extern struct state op_r_rb;
extern struct state op_l_sb;
extern struct state op_r_sb;

extern struct state op_not_equal_begin;
extern struct state op_not_equal;
extern struct state op_bits_and;
extern struct state op_assign_bits_and;
extern struct state op_bits_or;
extern struct state op_assign_bits_or;
extern struct state op_bits_xor;
extern struct state op_assign_bits_xor;

extern struct state op_multiply;
extern struct state op_assign_multiply;
extern struct state op_mod;
extern struct state op_assign_mod;
extern struct state op_minus;
extern struct state op_assign_minus;
extern struct state op_plus;
extern struct state op_assign_plus;
extern struct state op_divide;
extern struct state op_assign_divide;
extern struct state op_assign;
extern struct state op_equal;

extern struct state op_greater_than;
extern struct state op_greater_equal;
extern struct state op_right_shift;
extern struct state op_assign_right_shift;

extern struct state op_less_than;
extern struct state op_less_equal;
extern struct state op_left_shift;
extern struct state op_assign_left_shift;

/*annotate parts*/
extern struct state an_begin;
extern struct state an_annotate;
extern struct state an_end;

/*white space (ws) parts*/
extern struct state ws_begin;
extern struct state ws_ws;

/*sentence break (sb)*/
extern struct state sb_begin;
extern struct state sb_semicolon;
extern struct state sb_newline;

/*merge parts*/
extern struct state me_begin;
extern struct state me_period; 

/*special charicter*/
extern struct state sp_dollar;
#endif /*_REDY_LEXICAL_SL_STATE_H_*/
