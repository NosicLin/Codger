#include"rtype.h"
#include<utility_c/marocs.h>

/*-----------------int part----------------------------*/
Robject* r_mul_int_float(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_FLOAT,"ERR Right Type(%s)",right->r_name);

	int l_val=R_TO_I(left)->i_value;
	float r_val=R_TO_F(right)->f_value;

	float mul_ret=(float)l_val* r_val;
	
	BtFloat*  r_ret=bt_float_create(mul_ret);
	return F_TO_R(r_ret);
}

Robject* r_mul_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	BGInteger* r_val=R_TO_L(right)->l_value;

	BGInteger* mul_ret=bg_mul(l_val,r_val);
	BtLong* ret=bt_long_create(mul_ret); 

	bg_free(l_val);
	return L_TO_R(ret);
}

Robject* r_div_int_float(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_FLOAT,"ERR Right Type(%s)",right->r_name);
	if(bt_float_is_zero(R_TO_F(right)))
	{
		rt_raise_div_zero(left);
		robject_addref(robject_null);
		return robject_null;
	}

	int l_val=R_TO_I(left)->i_value;
	float r_val=R_TO_F(right)->f_value;

	float div_ret=(float)l_val/ r_val;
	BtFloat*  r_ret=bt_float_create(div_ret);
	return F_TO_R(r_ret);
}

Robject* r_div_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	if(bt_long_is_zero(R_TO_L(right)))
	{
		rt_raise_div_zero(left);
		robject_addref(robject_null);
		return robject_null;
	}
	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	BGInteger* r_val=R_TO_L(right)->l_value;
	BGInteger* div_ret=bg_div(l_val,r_val);

	BtLong* ret=bt_long_create(div_ret); 
	bg_free(l_val);
	return L_TO_R(ret);
}
	
Robject* r_mod_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	if(bt_long_is_zero(R_TO_L(right)))
	{
		rt_raise_div_zero(left);
		robject_addref(robject_null);
		return robject_null;
	}
	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	BGInteger* r_val=R_TO_L(right)->l_value;

	BGInteger* mod_ret=bg_mod(l_val,r_val);
	BtLong* ret=bt_long_create(mod_ret); 
	bg_free(l_val);
	return L_TO_R(ret);
}

Robject* r_plus_int_float(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_FLOAT,"ERR Right Type(%s)",right->r_name);

	int l_val=R_TO_I(left)->i_value;
	float r_val=R_TO_F(right)->f_value;

	float plus_ret=(float)l_val+r_val;
	BtFloat*  r_ret=bt_float_create(plus_ret);
	return F_TO_R(r_ret);
}

Robject* r_plus_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	BGInteger* r_val=R_TO_L(right)->l_value;

	BGInteger* plus_ret=bg_plus(l_val,r_val);
	BtLong* ret=bt_long_create(plus_ret); 
	bg_free(l_val);
	return L_TO_R(ret);
}


Robject* r_minus_int_float(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_FLOAT,"ERR Right Type(%s)",right->r_name);

	int l_val=R_TO_I(left)->i_value;
	float r_val=R_TO_F(right)->f_value;

	float minus_ret=(float)l_val-r_val;
	BtFloat*  r_ret=bt_float_create(minus_ret);
	return F_TO_R(r_ret);
}

Robject* r_minus_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	BGInteger* r_val=R_TO_L(right)->l_value;


	BGInteger* minus_ret=bg_minus(l_val,r_val);
	BtLong* ret=bt_long_create(minus_ret); 
	bg_free(l_val);
	return L_TO_R(ret);
}

Robject* r_lshift_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	BGInteger* r_val=R_TO_L(right)->l_value;
	if(bg_overflow_int(r_val))
	{
		rt_raise_overflow(right);
		robject_addref(robject_null);
		return robject_null;
	}
	if(bg_is_negative(r_val))
	{
		rt_raise_value_error("Negative Shift Count");
		robject_addref(robject_null);
		return robject_null;
	}


	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	
	BGInteger* lshift_ret=bg_lshift(l_val,r_val);
	BtLong* ret=bt_long_create(lshift_ret); 
	bg_free(l_val);

	return L_TO_R(ret);
}


Robject* r_rshift_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	BGInteger* r_val=R_TO_L(right)->l_value;
	if(bg_overflow_int(r_val))
	{
		rt_raise_overflow(right);
		robject_addref(robject_null);
		return robject_null;
	}
	if(bg_is_negative(r_val))
	{
		rt_raise_value_error("Negative Shift Count");
		robject_addref(robject_null);
		return robject_null;
	}

	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	
	BGInteger* rshift_ret=bg_rshift(l_val,r_val);
	BtLong* ret=bt_long_create(rshift_ret); 
	bg_free(l_val);

	return L_TO_R(ret);
}

Robject* r_cmp_int_float(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_FLOAT,"ERR Right Type(%s)",right->r_name);

	int l_val=R_TO_I(left)->i_value;
	float r_val=R_TO_F(right)->f_value;

	float cmp_ret=(float)l_val-r_val;
	BtInt*  r_ret=0;
	if(cmp_ret<0)
	{
		r_ret=bt_int_create(-1);
	}
	else if (cmp_ret==0)
	{
		r_ret=bt_int_create(0);
	}
	else 
	{
		r_ret=bt_int_create(1);
	}
	return I_TO_R(r_ret);
}

Robject* r_cmp_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	BGInteger* r_val=R_TO_L(right)->l_value;
	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	
	int cmp_ret=bg_cmp(l_val,r_val);

	BtInt* ret=bt_int_create(cmp_ret); 
	bg_free(l_val);
	return I_TO_R(ret);
}

Robject* r_and_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	BGInteger* r_val=R_TO_L(right)->l_value;
	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	
	BGInteger* and_ret=bg_and(l_val,r_val);
	BtLong* ret=bt_long_create(and_ret); 
	bg_free(l_val);
	return L_TO_R(ret);
}

Robject* r_or_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	BGInteger* r_val=R_TO_L(right)->l_value;
	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	
	BGInteger* or_ret=bg_or(l_val,r_val);
	BtLong* ret=bt_long_create(or_ret); 
	bg_free(l_val);
	return L_TO_R(ret);
}

Robject* r_xor_int_long(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_INT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);


	BGInteger* l_val=bg_create_from_int(R_TO_I(left)->i_value);
	BGInteger* r_val=R_TO_L(right)->l_value;
	
	BGInteger* xor_ret=bg_xor(l_val,r_val);
	BtLong* ret=bt_long_create(xor_ret); 
	bg_free(l_val);
	return L_TO_R(ret);
}



/*------------------float parts------------------------*/

Robject* r_mul_float_int(Robject* left, Robject* right)
{
	return r_mul_int_float(right,left);
}

Robject* r_mul_float_long(Robject* left, Robject* right)
{
	BUG_ON(left->r_type!=RT_FLOAT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);
	float l_val=R_TO_F(left)->f_value;
	float r_val=bg_to_float(R_TO_L(right)->l_value);

	float mul_ret=l_val* r_val;
	BtFloat*  r_ret=bt_float_create(mul_ret);
	return F_TO_R(r_ret);
}

Robject* r_div_float_int(Robject* left, Robject* right)
{
	BUG_ON(left->r_type!=RT_FLOAT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);
	if(bt_int_is_zero(R_TO_I(right)))
	{
		rt_raise_div_zero(left);
		robject_addref(robject_null);
		return robject_null;
	}

	float l_val=R_TO_F(left)->f_value;
	int r_val=R_TO_I(right)->i_value;
	float div_ret=l_val/r_val;
	BtFloat*  r_ret=bt_float_create(div_ret);
	return F_TO_R(r_ret);
}

Robject* r_div_float_long(Robject* left, Robject* right)
{

	BUG_ON(left->r_type!=RT_FLOAT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	if(bt_long_is_zero(R_TO_L(right)))
	{
		rt_raise_div_zero(left);
		robject_addref(robject_null);
		return robject_null;
	}
	float l_val=R_TO_F(left)->f_value;
	float r_val=bg_to_float(R_TO_L(right)->l_value);

	float div_ret=l_val/r_val;
	BtFloat*  r_ret=bt_float_create(div_ret);
	return F_TO_R(r_ret);
}
Robject* r_plus_float_int(Robject* left, Robject* right)
{
	return r_plus_int_float(right,left);
}

Robject* r_plus_float_long(Robject* left, Robject* right)
{
	BUG_ON(left->r_type!=RT_FLOAT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	float l_val=R_TO_F(left)->f_value;
	float r_val=bg_to_float(R_TO_L(right)->l_value);
	float plus_ret=l_val+ r_val;
	BtFloat*  r_ret=bt_float_create(plus_ret);
	return F_TO_R(r_ret);
}
Robject* r_minus_float_int(Robject* left, Robject* right)
{
	BUG_ON(left->r_type!=RT_FLOAT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);

	float l_val=R_TO_F(left)->f_value;
	int r_val=R_TO_I(right)->i_value;
	float minus_ret=l_val-r_val;

	BtFloat*  r_ret=bt_float_create(minus_ret);
	return F_TO_R(r_ret);
}

Robject* r_minus_float_long(Robject* left, Robject* right)
{
	BUG_ON(left->r_type!=RT_FLOAT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	float l_val=R_TO_F(left)->f_value;
	float r_val=bg_to_float(R_TO_L(right)->l_value);
	float minus_ret=l_val- r_val;
	BtFloat*  r_ret=bt_float_create(minus_ret);
	return F_TO_R(r_ret);
}


Robject* r_cmp_float_int(Robject* left, Robject* right)
{
	BUG_ON(left->r_type!=RT_FLOAT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);

	float l_val=R_TO_F(left)->f_value;
	int r_val=R_TO_I(right)->i_value;
	float value=l_val-r_val;

	BtInt* ret=0;
	if(value<0)
	{
		ret=bt_int_create(-1);
	}
	else if(value>0)
	{
		ret=bt_int_create(1);
	}
	else
	{
		ret=bt_int_create(0);
	}
	return I_TO_R(ret);
}

Robject* r_cmp_float_long(Robject* left, Robject* right)
{
	BUG_ON(left->r_type!=RT_FLOAT,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_LONG,"ERR Right Type(%s)",right->r_name);

	float l_val=R_TO_F(left)->f_value;
	float r_val=bg_to_float(R_TO_L(right)->l_value);
	float value=l_val-r_val;

	BtInt* ret=0;
	if(value<0)
	{
		ret=bt_int_create(-1);
	}
	else if(value>0)
	{
		ret=bt_int_create(1);
	}
	else
	{
		ret=bt_int_create(0);
	}
	return I_TO_R(ret);
}




/*----------------long parts ---------------------*/
Robject* r_mul_long_float(Robject* left,Robject* right)
{
	return r_mul_float_long(right,left);
}

Robject* r_mul_long_int(Robject* left,Robject* right)
{
	return r_mul_int_long(right,left);
}

Robject* r_div_long_float(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_FLOAT,"ERR Right Type(%s)",right->r_name);
	if(bt_float_is_zero(R_TO_F(right)))
	{
		rt_raise_div_zero(left);
		robject_addref(robject_null);
		return robject_null;
	}
	float l_val=bg_to_float(R_TO_L(left)->l_value);
	float r_val=R_TO_F(right)->f_value;
	float div_ret=l_val/r_val;
	BtFloat* ret=bt_float_create(div_ret);

	return F_TO_R(ret);
}
		

Robject* r_div_long_int(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);
	if(bt_int_is_zero(R_TO_I(right)))
	{
		rt_raise_div_zero(left);
		robject_addref(robject_null);
		return robject_null;
	}
	BGInteger* l_val=R_TO_L(left)->l_value;
	BGInteger* r_val=bg_create_from_int(R_TO_I(right)->i_value);
	BGInteger* div_ret=bg_div(l_val,r_val);
	bg_free(r_val);
	BtLong* ret=bt_long_create(div_ret);

	return L_TO_R(ret);
}




Robject* r_mod_long_int(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);
	if(bt_int_is_zero(R_TO_I(right)))
	{
		rt_raise_div_zero(left);
		robject_addref(robject_null);
		return robject_null;
	}
	BGInteger* l_val=R_TO_L(left)->l_value;
	BGInteger* r_val=bg_create_from_int(R_TO_I(right)->i_value);
	BGInteger* div_ret=bg_mod(l_val,r_val);
	bg_free(r_val);
	BtLong* ret=bt_long_create(div_ret);

	return L_TO_R(ret);
}
Robject* r_minus_long_float(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_FLOAT,"ERR Right Type(%s)",right->r_name);

	float l_val=bg_to_float(R_TO_L(left)->l_value);
	float r_val=R_TO_F(right)->f_value;
	float minus_ret=l_val-r_val;
	BtFloat* ret=bt_float_create(minus_ret);

	return F_TO_R(ret);
}
Robject* r_minus_long_int(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);

	BGInteger* l_val=R_TO_L(left)->l_value;
	BGInteger* r_val=bg_create_from_int(R_TO_I(right)->i_value);

	BGInteger* minus_ret=bg_minus(l_val,r_val);
	bg_free(r_val);
	BtLong* ret=bt_long_create(minus_ret);

	return L_TO_R(ret);
}
Robject* r_plus_long_float(Robject* left,Robject* right)
{
	return r_plus_float_long(right,left);
}
Robject* r_plus_long_int(Robject* left,Robject* right)
{
	return r_plus_int_long(right,left);
}

Robject* r_lshift_long_int(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);
	if(R_TO_I(right)->i_value<0)
	{
		rt_raise_value_error("Negative Shift Count");
		robject_addref(robject_null);
		return robject_null;
	}


	BGInteger* l_val=R_TO_L(left)->l_value;
	BGInteger* r_val=bg_create_from_int(R_TO_I(right)->i_value);

	BGInteger* lshift_ret=bg_lshift(l_val,r_val);
	bg_free(r_val);
	BtLong* ret=bt_long_create(lshift_ret);
	return L_TO_R(ret);
}
Robject* r_rshift_long_int(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);
	if(R_TO_I(right)->i_value<0)
	{
		rt_raise_value_error("Negative Shift Count");
		robject_addref(robject_null);
		return robject_null;
	}

	BGInteger* l_val=R_TO_L(left)->l_value;
	BGInteger* r_val=bg_create_from_int(R_TO_I(right)->i_value);

	BGInteger* rshift_ret=bg_rshift(l_val,r_val);
	bg_free(r_val);

	BtLong* ret=bt_long_create(rshift_ret);
	return L_TO_R(ret);
}

Robject* r_cmp_long_int(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_INT,"ERR Right Type(%s)",right->r_name);
	if(R_TO_I(right)->i_value<0)
	{
		rt_raise_value_error("Negative Shift Count");
		robject_addref(robject_null);
		return robject_null;
	}

	BGInteger* l_val=R_TO_L(left)->l_value;
	BGInteger* r_val=bg_create_from_int(R_TO_I(right)->i_value);
	int cmp_ret=bg_cmp(l_val,r_val);

	BtInt* ret=bt_int_create(cmp_ret);
	bg_free(r_val);
	return I_TO_R(ret);
}

Robject* r_cmp_long_float(Robject* left,Robject* right)
{
	BUG_ON(left->r_type!=RT_LONG,"ERR Left Type(%s)",left->r_name);
	BUG_ON(right->r_type!=RT_FLOAT,"ERR Right Type(%s)",right->r_name);

	float l_val=bg_to_float(R_TO_L(left)->l_value);
	float r_val=R_TO_F(right)->f_value;
	float cmp_ret=l_val-r_val;

	BtInt* ret=0;

	if(cmp_ret<0)
	{
		ret=bt_int_create(-1);
	}
	else if(cmp_ret>0)
	{
		ret=bt_int_create(1);
	}
	else
	{
		ret=bt_int_create(0);
	}
	return I_TO_R(ret);
}

Robject* r_or_long_int(Robject* left,Robject* right)
{
	return r_or_int_long(right,left);
}

Robject* r_and_long_int(Robject* left,Robject* right)
{
	return r_and_int_long(right,left);
}

Robject* r_xor_long_int(Robject* left,Robject* right)
{
	return r_xor_int_long(right,left);
}
