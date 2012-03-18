#include"big_integer.h"
#include<utility_c/marocs.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#define DEFALUT_BIG_INTEGER_LENGTH 3 
#define BGLONG_SHIFT 15
#define BGLONG_BASE ((b_unit)(1<<BGLONG_SHIFT))
#define BGLONG_MASK ((b_unit)(BGLONG_BASE-1))

#define SHIFT BGLONG_SHIFT
#define BASE BGLONG_BASE
#define MASK BGLONG_MASK 

#define BIG_INTEGER_DEBUG 0

#if BIG_INTEGER_DEBUG  
static void units_print(b_unit* u,int size)
{
	assert(size>0);
	int i,j;
	for(i=size-1;i>=0;i--)
	{
		for(j=SHIFT-1;j>=0;j--)
		{
			if(u[i]&(1<<j))
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		printf(" ");
	}
}
#endif 

int bg_booleaned(BGInteger* bg)
{
	if(bg->b_len==0)
	{
		return 0;
	}
	else 
	{
		return 1;

	}
}
int bg_cmp(BGInteger* left,BGInteger* right)
{
	int l_len=left->b_len;
	int r_len=right->b_len;
	if(l_len<r_len)
	{
		return -1;
	}
	else if (l_len>r_len)
	{
		return 1;
	}
	else 
	{
		int sign=0;
		int cmp_ret=0;
		int len=l_len;
		if (l_len<0)
		{
			sign=1;
			len=l_len*-1;
		}
		while(len--)
		{
			if(left->b_val[len]>right->b_val[len])
			{
				cmp_ret=1;
				break;
			}
			else if(left->b_val[len]<right->b_val[len])
			{
				cmp_ret=-1;
				break;
			}
		}
		if(sign)
		{
			cmp_ret*=-1;
		}
		return cmp_ret;
	}
}


static inline int bg_bit_in_unit(b_unit u)
{
	int i=SHIFT;
	while(i--)
	{
		if(u&(1<<i))
		{
			break;
		}
	}
	return i+1;
}

/* if r is too large to convert to int  return -1*/
static int bg_to_abs_int(BGInteger* r)
{
	int r_len=abs(r->b_len);
	int ret=0;
	b_unit* r_val=r->b_val;
	if(r_len>=4)
	{
		return -1;
	}
	if(r_len==3)
	{
		if(bg_bit_in_unit(r_val[2])>=2)
		{
			return  -1;
		}
		else
		{
			ret|=r_val[2]<<(SHIFT*2);
		}
	}
	if(r_len>=2)
	{
		ret|=r_val[1]<<SHIFT;
	}
	if(r_len>=1)
	{
		ret|=r_val[0];
	}
	return ret;
}
int bg_to_int(BGInteger* bg)
{
	int value=bg_to_abs_int(bg);
	/*overflow  int */
	if(value==-1)
	{
		return 0;
	}
	if(bg->b_len<0)
	{
		value*=-1;
	}
	return value;
}

int bg_overflow_int(BGInteger* bg)
{
	int value=bg_to_abs_int(bg);
	if(value==-1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*FIXME 
 * bg_to_float need to rewrite,it will lose precision 
 * this is only used for temp
 */
float bg_to_float(BGInteger* bg)
{
	int sign=0;
	if(bg->b_len<0)
	{
		sign=1;
	}

	int len=abs(bg->b_len);
	float value=0;
	while(len--)
	{
		value=value*BASE+bg->b_val[len]; /*will lose precision*/
	}
	if(sign)
	{
		value*=-1;
	}
	return value;
}

static void  bg_format_len(BGInteger* bg)
{
	int len=abs(bg->b_len);
	while(len&&(!bg->b_val[len-1]))
		len--;
	
	if(bg->b_len<0)
	{
		bg->b_len=len*-1;
	}
	else
	{
		bg->b_len=len;
	}
}

static inline char int_to_char(int value)
{
	BUG_ON(value<0||value>9,"Error Value(%d)",value);
	return '0'+value;
}

static inline int  bg_get_bit(BGInteger* bg,long pos)
{
	BUG_ON(pos>=abs(bg->b_len)*SHIFT,"Error Pos");
	int pre=pos/BGLONG_SHIFT;
	int sub=pos%BGLONG_SHIFT;
	return (bg->b_val[pre]&(1<<sub))!=0;
}
static inline void bg_set_bit(BGInteger* bg,long pos,int value)
{
	BUG_ON(pos>=abs(bg->b_len)*SHIFT,"Error Pos");
	int pre=pos/BGLONG_SHIFT;
	int sub=pos%BGLONG_SHIFT;
	if(value)
	{
		bg->b_val[pre]|=(1<<sub);
	}
	else
	{
		bg->b_val[pre]&=~(1<<sub);
	}
}


static inline BGInteger* bg_malloc(int len)
{
	int t_len=len*sizeof(b_unit)+sizeof(BGInteger);
	BGInteger* ret=(BGInteger*)malloc(t_len);
	memset(ret,0,t_len);
	ret->b_len=len;
	return ret;
}

static BGInteger* bg_clone(BGInteger* bg)
{
	BGInteger* ret=bg_malloc(abs(bg->b_len));
	ret->b_len=bg->b_len;
	memcpy(ret->b_val,bg->b_val,abs(bg->b_len)*sizeof(b_unit));
	return ret;
}

static BGInteger* bg_create_zero()
{
	BGInteger* ret=bg_malloc(1);
	ret->b_len=0;
	return ret;
}

void bg_self_negative(BGInteger* bg)
{
	bg->b_len*=-1;
}

static inline void self_negative(BGInteger* bg)
{
	bg_self_negative(bg);
}

BGInteger* bg_create_from_int(int value)
{
	BGInteger* ret=bg_malloc(DEFALUT_BIG_INTEGER_LENGTH);
	if(value<0)
	{
		self_negative(ret);
		value=-value;
	}
	int i;
	for(i=0;i<DEFALUT_BIG_INTEGER_LENGTH;i++)
	{
		ret->b_val[i]=value&MASK;
		value>>=SHIFT;
	}
	bg_format_len(ret);
	return ret;
}


/*prefix and postfix must remove before call
 * for example oct a=0O474511l
 * @str=474511
 *
 */
BGInteger* bg_create_from_octstr(char* str)
{

	int len=strlen(str);
	BGInteger* ret=bg_malloc(len*3/SHIFT+1);
	int  c_bit=0;
	int c_i;
	while(len--)
	{
		int c_val=str[len]-'0';

		c_i=0;
		while(c_val)
		{
			bg_set_bit(ret,c_bit+c_i,c_val%2);
			c_i++;
			c_val/=2;
		}

		c_bit+=3;
	}
	bg_format_len(ret);
	return ret;
}

/*prefix and postfix must remove before call
 * for example bin a=0B0101100l
 * @str=0101100
 */
BGInteger* bg_create_from_binstr(char* str)
{
	int len=strlen(str);
	BGInteger* ret=bg_malloc(len/SHIFT+1);
	int c_bit=0;
	while(len--)
	{
		int c_val=str[len]-'0';
		bg_set_bit(ret,c_bit,c_val);
		c_bit++;
	}
	bg_format_len(ret);
	return ret;
}

/*prefix and postfix must remove before call
 * for example hex a=0x103afl
 * @str=103af
 */
static int char_to_int(char c)
{
	int ret=0;
	if('0'<=c && c<='9')
	{
		ret=c-'0';
	}
	else if('a'<=c && c<='f')
	{
		ret= c-'a'+10;
	}
	else if('A'<=c && c<='F')
	{
		ret=c-'A'+10;
	}
	else 
	{
		/* invalid char */
		BUG("Error Char(%c)",c);
		ret=0;
	}
	return ret; 
}
BGInteger* bg_create_from_hexstr(char* str)
{

	int len=strlen(str);
	BGInteger* ret=bg_malloc(len*4/SHIFT+1);
	int c_bit=0;
	int c_i;
	while(len--)
	{
		int c_val=char_to_int(str[len]);
		c_i=0;
		while(c_val)
		{
			bg_set_bit(ret,c_bit+c_i,c_val%2);
			c_i++;
			c_val/=2;
		}
		c_bit+=4;
	}
	bg_format_len(ret);
	return ret;
}
/* divide by 2 
 * until quotient==0
 *
 * prefix and postfix must remove before call
 * for example dec=14784410l
 * @str=14784410 
 */
BGInteger* bg_create_from_decstr(char* decstr)
{

	int len=strlen(decstr);

	char* str2=(char*)malloc(len+1);	
	char* cal_str=str2;
	memcpy(cal_str,decstr,len+1);

	int t_len=len*4/SHIFT+1;
	BGInteger* ret=bg_malloc(t_len);

	int c_bit=0;
	while(cal_str[0])
	{
		int i=0;
		int c_remainder=0;
		while(cal_str[i])
		{
			int c_val=cal_str[i]-'0'+c_remainder*10;
			cal_str[i]=c_val/BASE+'0';
			c_remainder=c_val%BASE;
			i++;
		}
		ret->b_val[c_bit++]=(b_unit)c_remainder;
		cal_str[i]='\0';
		while(*cal_str=='0') cal_str++;
	}
	free(str2);
	bg_format_len(ret);
	return ret;
}
	
BGInteger* bg_negative(BGInteger* bg)
{
	BGInteger* ret=bg_clone(bg);
	bg_self_negative(ret);
	return ret;
}

static BGInteger* abs_plus(BGInteger* l,BGInteger* r)
{
	int l_len=abs(l->b_len);
	int r_len=abs(r->b_len);
	if(l_len<r_len)
	{
		BGInteger* tempb=l;
		l=r;
		r=tempb;
		int tempi=l_len;
		l_len=r_len;
		r_len=tempi;
	}
	b_unit* l_val=l->b_val;
	b_unit* r_val=r->b_val;

	BGInteger* ret=bg_malloc(l_len+1);
	b_unit* t_val=ret->b_val;

	b_unit carry=0;
	int i;
	for(i=0;i<r_len;i++)
	{
		carry=l_val[i]+r_val[i]+carry;
		t_val[i]=carry&MASK;
		carry>>=SHIFT;
	}
	for(;i<l_len;i++)
	{
		carry=l_val[i]+carry;
		t_val[i]=carry&MASK;
		carry>>=SHIFT;
	}
	t_val[i]=carry;
	bg_format_len(ret);
	return ret;
}

static BGInteger* abs_minus(BGInteger* l,BGInteger* r)
{
	int l_len=abs(l->b_len);
	int r_len=abs(r->b_len);
	int sign=1;
	if(l_len<r_len)
	{
		BGInteger* tempb=l;
		l=r;
		r=tempb;
		int tempi=l_len;
		l_len=r_len;
		r_len=tempi;
		sign=-1;
	}
	else if(l_len==r_len)
	{
		while(l_len&&(l->b_val[l_len-1]==r->b_val[l_len-1])) l_len--;
		if(l_len==0)
		{
		   return bg_create_zero();
		}
		r_len=l_len;
		if(l->b_val[l_len-1]<r->b_val[r_len-1])
		{
			BGInteger* tempb=l;
			l=r;
			r=tempb;
			sign=-1;
		}
	}


	b_unit* l_val=l->b_val;
	b_unit* r_val=r->b_val;

	BGInteger* ret=bg_malloc(l_len);
	b_unit* t_val=ret->b_val;

	int i;
	b_unit borrow=0;
	for(i=0;i<r_len;i++)
	{
		borrow=l_val[i]-r_val[i]-borrow;
		t_val[i]=borrow&MASK;
		borrow=(borrow>>SHIFT)&1;
	}
	for(;i<l_len;i++)
	{
		borrow=l_val[i]-borrow;
		t_val[i]=borrow&MASK;
		borrow=(borrow>>SHIFT)&1;
	}
	if(sign==-1)
	{
		self_negative(ret);
	}

	bg_format_len(ret);
	return ret;
}
BGInteger* bg_plus(BGInteger* l,BGInteger* r)
{
	BGInteger* ret=0;
	if(l->b_len<0)
	{
		if(r->b_len<0)
		{
			/* l<0, r<0 
			 * ret=-(abs(l)+abs(r))
			 */
			ret=abs_plus(l,r);
			self_negative(ret);
		}
		else
		{
			/*l<0,r>=0
			 * ret=-(abs(r)-abs(r))
			 */
			ret=abs_minus(l,r);
			self_negative(ret);
		}
	}
	else
	{
		if(r->b_len<0)
		{
			/* l>=0,r<0
			 * ret=abs(l)-abs(r)
			 */
			ret=abs_minus(l,r);
		}
		else
		{
			/* l>=0,r>=0
			 * ret=abs(l)+abs(r)
			 */
			ret=abs_plus(l,r);
		}
	}
	return ret;
}


BGInteger* bg_minus(BGInteger* l,BGInteger* r)
{
	BGInteger* ret=0;
	if(l->b_len<0)
	{
		if(r->b_len<0)
		{
			/* l<0 ,r<0
			 * l-r=-abs(l)-(-abs(r))=-(abs(l)-abs(r));
			 */
			ret=abs_minus(l,r);
			self_negative(ret);
		}
		else
		{
			/* l<0,r>=0
			 * l-r=-abs(l)-abs(r)=-(abs(l)+abs(r));
			 */
			ret=abs_plus(l,r);
			self_negative(ret);
		}
	}
	else
	{
		if(r->b_len<0)
		{
			/* l>=0 ,r <0
			 * l-r=abs(l)-(-abs(r))=abs(l)+abs(r);
			 */
			ret=abs_plus(l,r);

		}
		else
		{
			/* l>=0, r>=0
			 * l-r=abs(l)-abs(r)
			 */
			ret=abs_minus(l,r);

		}

	}
	return ret;
}



static BGInteger* abs_mul(BGInteger* l,BGInteger* r)
{
	
	int l_len=abs(l->b_len);
	int r_len=abs(r->b_len);
	if(l_len==0||r_len==0)
	{
		return bg_create_zero();
	}
	int t_len=l_len+r_len;
	BGInteger* ret=bg_malloc(t_len);

	b_unit* l_val=l->b_val;
	b_unit* r_val=r->b_val;
	b_unit* t_val=ret->b_val;

	int i,j;
	for(i=0;i<r_len;i++)
	{
		b_unit c=0;
		for(j=0;j<l_len;j++)
		{
			twob_unit val=t_val[i+j]+l_val[j]*r_val[i]+c;
			t_val[i+j]=val&MASK;
			c=val>>SHIFT;
		}
		t_val[i+l_len]=c;
	}

	bg_format_len(ret);
	return ret;
}
BGInteger* bg_mul(BGInteger* l,BGInteger* r)
{
	BGInteger* ret=abs_mul(l,r);
	if(l->b_len*r->b_len<0)
	{
		self_negative(ret);
	}
	return ret;
}

/*@condition shift_value<SHIFT*/
static b_unit units_lshift(b_unit* d,b_unit* s,int size, int shift_value)
{
//	printf("size=%d\n",size);
	assert(size>=0&&shift_value<SHIFT);
	twob_unit t=0;
	int i;
	for(i=0;i<size;i++)
	{
		d[i]=(s[i]<<shift_value|t)&MASK;
		t=(s[i]>>(SHIFT-shift_value))&MASK;
	}
	return t;
}

/*@condition shift_value<SHIFT*/
static b_unit units_rshift(b_unit* d, b_unit* s ,int size,int shift_value)
{
	assert(size>=0&&shift_value<SHIFT);

	b_unit t=0;
	while(size--)
	{
		d[size]=(s[size]>>shift_value|t)&MASK;
		t=(s[size]<<(SHIFT-shift_value))&MASK;
	}
	return t;
}

/*
 * @r!=0;
 * 2<=r->len<=l->r->len;
 */

static int  abs_divrem(BGInteger* left,BGInteger* right,BGInteger** pdiv,BGInteger** prem)
{
	int l_len=abs(left->b_len);
	int r_len=abs(right->b_len);

	BUG_ON(l_len<r_len||r_len<2,"Error Length");

	BGInteger* x=bg_malloc(l_len+1);
	BGInteger* y=bg_malloc(r_len);

	int x_len=l_len;
	int y_len=r_len;

	b_unit* x_val=x->b_val;
	b_unit* y_val=y->b_val;

	/*
	   printf("left:dec=");
	   bg_print_dec(left);
	   printf("\nright:dec=");
	   bg_print_dec(right);
	   printf("\n");
	   */

	int d=bg_bit_in_unit(right->b_val[r_len-1]);
	int m=SHIFT-d;

	/*
	   printf("shift=%d\n",1<<m);
	   */

	int carry;
	carry=units_lshift(y_val,right->b_val,r_len,m);
	assert(carry==0);
	carry=units_lshift(x_val,left->b_val,l_len,m);

	if(carry!=0||x_val[x_len-1]>=y_val[y_len-1])
	{
		x_val[x_len]=carry;
		x_len++;
	}

	/*
	   printf("left:dec=");
	   bg_print_dec(x);
	   printf("\nleft:bin=");
	   bg_print_bin(x);
	   printf("\nright:dec=");
	   bg_print_dec(y);
	   printf("\nright:bin=");
	   bg_print_bin(y);
	   printf("\n");
	   */

	int k=x_len-y_len;
	BGInteger* qa =bg_malloc(k);
	b_unit* c_qa=qa->b_val+k-1;


	int i;
	b_unit y_t=y_val[y_len-1];
	b_unit y_t_1=y_val[y_len-2];
	b_unit q,r;

	for(i=x_len-1;i>=y_len;i--)
	{
		b_unit x_i=x_val[i];
		b_unit x_i_1=x_val[i-1];
		b_unit x_i_2=x_val[i-2];

		twob_unit xx=x_i<<SHIFT|x_i_1;
		assert(x_i<=y_t);
		if(x_i==y_t)
		{
			q=BASE-1;
			r=(b_unit)(xx-(twob_unit)q*y_t);
		}
		else
		{
			q=(b_unit)(xx/y_t);
			r=(b_unit)(xx-(twob_unit)q*y_t);
		}
		while((twob_unit)q*y_t_1>((twob_unit)r<<SHIFT)+x_i_2)
		{
			q--;
			r+=y_t;
			if(r>=BASE)
				break;
		}

//		printf("q=%d,r=%d\n",q,r);

		twob_unit y_mul=0;
		b_unit borrow=0;
		int j;
		for(j=0;j<y_len;j++)
		{
			y_mul=(twob_unit)y_val[j]*q+y_mul+borrow;
			borrow=x_val[i-y_len+j]-(b_unit)(y_mul&MASK);
			x_val[i-y_len+j]=borrow&MASK;
			y_mul>>=SHIFT;
			borrow>>=SHIFT;
		}
		y_mul+=borrow;

		b_unit carry=0;

		/*
		   printf("x_i=%d,y_mul=%d\n",x_i,y_mul);
		   printf("x_i-y_mul=%d(%d)\n",x_i-y_mul,(sb_unit)(x_i-y_mul)<0);
		   */

		assert(x_i-y_mul==-1||x_i-y_mul==0);
		if((sb_unit)(x_i-y_mul)<0)
		{
			q--;
			for(j=0;j<y_len;j++)
			{
				carry=x_val[i-y_len+j]+y_val[j]+carry;
				x_val[i-y_len+j]=carry&MASK;
				carry>>=SHIFT;
			}
			assert(carry==1);
		}
		/*
		   printf("x:dec=");
		   bg_print_dec(x);
		   printf("\nx:bin=");
		   bg_print_bin(x);
		   printf("\n");
		   */

		x_val[i]=0;
		*c_qa--=q;

	}
	/*
	   printf("\n");
	   printf("\n");
	   bg_print_dec(x);
	   printf("\n");
	   printf("d=%d\n",d);
	   */

	units_rshift(y_val,x_val,y_len,m);

	bg_format_len(y);
	bg_format_len(qa);

	*prem=y;
	*pdiv=qa;

	/*
	   printf("qa:dec=");
	   bg_print_dec(qa);
	   printf("\nqa:bin=");
	   bg_print_bin(qa);
	   printf("\n");
	   */



	bg_free(x);

	return 1;
}
static int abs_divrem1(BGInteger* left,BGInteger* right,BGInteger** pdiv,BGInteger** prem)
{
	int x_len=abs(left->b_len);
	int y_len=abs(right->b_len);

	assert(y_len==1);

	BGInteger* x=bg_malloc(x_len+1);
	BGInteger* y=bg_malloc(y_len);


	b_unit* x_val=x->b_val;
	b_unit* y_val=y->b_val;

	memcpy(x_val,left->b_val,x_len*sizeof(*x_val));
	memcpy(y_val,right->b_val,y_len*sizeof(*y_val));

	if(x->b_val[x_len-1]>=y->b_val[y_len-1])
	{
		x_len++;
	}
	int k_len=x_len-y_len;
	BGInteger* qa=bg_malloc(k_len);
	b_unit* c_qa=qa->b_val+k_len-1;

	int i;
	b_unit q;
	b_unit r;
	b_unit yt=y_val[y_len-1];

	for(i=x_len-1;i>=y_len;i--)
	{
		b_unit x_i=x_val[i];
		b_unit x_i_1=x_val[i-1];
		twob_unit xx=x_i<<SHIFT|x_i_1;
		q=xx/yt;
		r=xx-(twob_unit)yt*q;

		*c_qa--=q;
		x_val[i-1]=r;
	}
	memcpy(y_val,x_val,y_len*sizeof(*y_val));

	bg_format_len(qa);
	bg_format_len(y);

	bg_free(x);

	*pdiv=qa;
	*prem=y;
	return 1;
}
static int abs_cmp(BGInteger* l,BGInteger* r)
{
	int l_len=abs(l->b_len);
	int r_len=abs(r->b_len);
	if(l_len<r_len)
	{
		return -1;
	}

	else if(l_len>r_len)
	{
		return 1;
	}
	else
	{
		int i=l_len;
		while(i--)
		{
			if(l->b_val[i]<r->b_val[i])
			{
				return -1;
			}
			else if (l->b_val[i]>r->b_val[i])
			{
				return 1;
			}
		}
	}
	return 0;
}




int  i_divrem(BGInteger* l,BGInteger* r,BGInteger** pdiv,BGInteger** prem)
{

	BGInteger* div;
	BGInteger* rem;
	int l_len=abs(l->b_len);
	int r_len=abs(r->b_len);

	if(r_len==0)
	{
		WARN("BG divide By Zero");
		return -1;
	}
	if(l_len<r_len||abs_cmp(l,r)<0)
	{
		div=bg_create_zero();
		rem=bg_clone(l);
		*pdiv=div;
		*prem=rem;
		return 1;
	}

	if(abs(r->b_len)==1)
	{
		abs_divrem1(l,r,&div,&rem);
	}
	else
	{
		abs_divrem(l,r,&div,&rem);
	}

	if((l->b_len<0) != (r->b_len<0))
	{
		self_negative(div);
	}
	if(l->b_len<0&&rem->b_len!=0)
	{
		self_negative(rem);

	}
	*pdiv=div;
	*prem=rem;
	return 1;
}
int  i_divmod(BGInteger* l,BGInteger* r,BGInteger** pdiv,BGInteger** pmod)
{
	BGInteger* div;
	BGInteger* rem;

	if(i_divrem(l,r,&div,&rem)<0)
	{
		return -1;
	}

	if((rem->b_len<0&&r->b_len>0)||(rem->b_len>0&&r->b_len<0))
	{
		BGInteger* real_rem=bg_plus(rem,r);

		BGInteger* b1=bg_create_from_int(1);
		BGInteger* real_div=bg_minus(div,b1);

		bg_free(rem);
		bg_free(div);
		bg_free(b1);

		*pdiv=real_div;
		*pmod=real_rem;
	}
	else
	{
		*pdiv=div;
		*pmod=rem;
	}
	return 1;
}

BGInteger* bg_div(BGInteger* l,BGInteger* r)
{
	BGInteger* div;
	BGInteger* mod;
	if(i_divmod(l,r,&div,&mod)<0)
	{
		return NULL;
	}
	bg_free(mod);
	return div;
}




BGInteger* bg_mod(BGInteger* l,BGInteger* r)
{
	BGInteger* div;
	BGInteger* mod;
	if(i_divmod(l,r,&div,&mod)<0)
	{
		return NULL;
	}
	bg_free(div);
	return mod;
}





/* translate original code to complement */
static void units_invert_complement(b_unit* d,b_unit* s,int size)
{
	b_unit carry=1;
	int i;
	for(i=0;i<size;i++)
	{
		carry=(~s[i]&MASK)+carry;
		d[i]=carry&MASK;
		carry>>=SHIFT;
	}

	assert(carry==0);
}
/* translate complement to original */
static void units_invert_origin(b_unit* d,b_unit* s,int size)
{
	b_unit carry=1;
	int i;
	for(i=0;i<size;i++)
	{
		carry=s[i]-carry;
		d[i]=(~carry)&MASK;
		carry>>=SHIFT;
	}
	assert(carry==0);
}




/*@condition r>0
 * r->b_len=1
 */

static inline BGInteger* abs_lshift(BGInteger* l,int shift_value)
{

	int l_len=abs(l->b_len);
	b_unit* l_val=l->b_val;

	int t_len=l_len+shift_value/SHIFT+1;
	BGInteger*  ret=bg_malloc(t_len);
	b_unit carry;
	carry=units_lshift(ret->b_val+shift_value/SHIFT,l_val,l_len,shift_value%SHIFT);
	ret->b_val[shift_value/SHIFT+l_len]=carry;

	bg_format_len(ret);
	return ret;
}
/*@condition r>0
 * r->b_len=1 or 0
 */
BGInteger* bg_lshift(BGInteger* l,BGInteger* r)
{
	if(r->b_len<0)
	{
		WARN("Negative Shift Value");
		return NULL;
	}
	if(r->b_len==0)
	{
		return bg_clone(l);
	}
	int shift_value=bg_to_abs_int(r);

	//printf("sv=%d\n",shift_value);
	if(shift_value<0)
	{
		WARN("Shift Value Is Too BIG");
		return NULL;
	}
	BGInteger* ret=abs_lshift(l,shift_value);
	if(l->b_len<0)
	{
		self_negative(ret);
	}
	return ret;
}


/*@condition r>=0
*/
static BGInteger* i_rshift(BGInteger* l,int shift_value)
{
	int l_len=abs(l->b_len);
	assert(shift_value>=0);
	BGInteger* ret=0;

	/* bits(l) < shift_value*/ 
	if(l_len*SHIFT<=shift_value)
	{
		if(l->b_len<0)
		{
			return bg_create_from_int(-1);
		}
		else
		{
			return bg_create_zero();
		}
	}

	int sign=l->b_len<0?1:0;

	ret=bg_malloc(l_len-shift_value/SHIFT);

	int shift_pre=shift_value/SHIFT;
	int shift_pos=shift_value%SHIFT;

	int size=l_len-shift_pre;
	int d=shift_pos;


	b_unit* ivt_l=malloc(sizeof(*ivt_l)*l_len);

	/* if l is negative , translate to complement */
	if(sign)
	{
		units_invert_complement(ivt_l,l->b_val,l_len);
	}
	else
	{
		memcpy(ivt_l,l->b_val,l_len*sizeof(*ivt_l));
	}

	b_unit* src=ivt_l+shift_pre;
	b_unit c_src;
	b_unit oflow=0;
	if(sign)
	{
		/* if left is negative, fill high bits 1 */
		oflow=(1<<d)-1;
	}
	oflow=(oflow<<(SHIFT-d))&MASK;
	int i=size;

	/* Right SHIFT */
	while(i--)
	{
		c_src=src[i];
		src[i]=oflow|((c_src&MASK)>>d);
		oflow=(c_src<<(SHIFT-d))&MASK;
	}

	if(sign)
	{
		/* translate complement to original */
		units_invert_origin(ret->b_val,src,size);
		self_negative(ret);
	}
	else
	{
		memcpy(ret->b_val,src,sizeof(*src)*size);
	}

	free(ivt_l);
	bg_format_len(ret);

	return ret;
}

/*@condition r>=0
*/
BGInteger* bg_rshift(BGInteger* l,BGInteger* r)
{
	int l_len=l->b_len;
	int r_len=r->b_len;

	if(l_len==0)
	{
		return bg_create_zero();
	}
	if(r_len==0)
	{
		return bg_clone(l);
	}
	if(r_len<0)
	{
		BUG("Shift With Negative Value");
		return NULL;
	}

	int shift_value=bg_to_abs_int(r);

	/* bits(r)>31, is to big, so return NULL*/
	if(shift_value<0)
	{
		WARN("RSHIFT Right Is Too Big");
		return NULL;
	}
	BGInteger* ret=i_rshift(l,shift_value);
	return ret;
}
static b_unit i_bitwise(b_unit l,b_unit r,char op)
{
	if(op=='^')
	{
		return l^r;
	}
	else  if(op=='|')
	{
		return l|r;
	}
	else if(op=='&')
	{
		return l&r;
	}
	assert(0); /*never reached here*/
	return 0;
}


static BGInteger* i_bits_op(BGInteger* l,BGInteger* r,char op)
{
	/*keep longer value left*/
	if(abs(l->b_len)<abs(r->b_len))
	{
		BGInteger* temp=l;
		l=r;
		r=temp;
	}
	int l_len=abs(l->b_len);
	int r_len=abs(r->b_len);

	/*0^0=0; 0|0=0; 0&0=0*/
	if(l_len==0&&r_len==0)
	{
		return bg_create_zero();
	}
	int l_sign=l->b_len<0?1:0;
	int r_sign=r->b_len<0?1:0;

	BGInteger* ret=bg_malloc(l_len);

	b_unit* l_val=l->b_val;
	b_unit* r_val=r->b_val;
	b_unit* t_val=ret->b_val;

	b_unit l_carry=1;
	b_unit r_carry=1;
	int i=0;

	b_unit c_l,c_r;

	for(i=0;i<r_len;i++)
	{
		c_l=l_val[i];
		c_r=r_val[i];

		if(l_sign==1)
		{

			l_carry=((~c_l)&MASK)+l_carry;
			c_l=l_carry&MASK;
			l_carry>>=SHIFT;
		}
		if(r_sign==1)
		{
			r_carry=((~c_r)&MASK)+r_carry;
			c_r=r_carry&MASK;
			r_carry>>=SHIFT;
		}
		t_val[i]=i_bitwise(c_l,c_r,op)&MASK;
	}

	for(;i<l_len;i++)
	{
		c_l=l_val[i];
		c_r=0;
		if(l_sign==1)
		{

			l_carry=((~c_l)&MASK)+l_carry;
			c_l=l_carry&MASK;
			l_carry>>=SHIFT;
		}
		if(r_sign==1)
		{
			r_carry=((~c_r)&MASK)+r_carry;
			c_r=r_carry&MASK;
			r_carry>>=SHIFT;
		}
		t_val[i]=i_bitwise(c_l,c_r,op)&MASK;
	}

	int need_invert=0;

	if(op=='&')
	{
		if((l_sign&r_sign)&1) need_invert=1;
	}
	else if(op=='^')
	{
		if((r_sign^l_sign)&1) need_invert=1;
	}
	else if(op=='|')
	{
		if((r_sign|l_sign)&1) need_invert=1;
	}
	if(need_invert)
	{
		//printf("need_invert \n");
		b_unit  r_carry=1;

		for(i=0;i<l_len;i++)
		{
			r_carry=t_val[i]-r_carry;

			t_val[i]=(~r_carry)&MASK;
			r_carry>>=SHIFT;
		}
		self_negative(ret);
	}
	bg_format_len(ret);
	return ret;

}

BGInteger* bg_or(BGInteger* l,BGInteger* r)
{
	return i_bits_op(l,r,'|');
}
BGInteger* bg_xor(BGInteger* l,BGInteger* r)
{
	return i_bits_op(l,r,'^');
}
BGInteger* bg_and(BGInteger* l,BGInteger* r)
{
	return i_bits_op(l,r,'&');
}

/* negated x=-(x+1) */
BGInteger* bg_negated(BGInteger* bg)
{
	BGInteger* one=bg_create_from_int(1);
	BGInteger* ret= bg_plus(bg,one);
	bg_self_negative(ret);
	bg_free(one);
	return ret;
}

/* old interface shouldn't use */
BGInteger* bg_invert(BGInteger* bg)
{
	return bg_negated(bg);
}





void bg_print_dec(BGInteger* bg)
{
	if(bg->b_len==0)
	{
		printf("0");
		return;
	}

	if(bg->b_len<0)
	{
		printf("-");
	}

	int len=abs(bg->b_len);
	char* r_str=(char*)malloc(len*SHIFT/3+2);

	b_unit* val=(b_unit*)malloc(sizeof(*val)*len);
	memcpy(val,bg->b_val,sizeof(*val)*len);
	int c_i=0;
	while(len)
	{
		int remander=0;
		int j=len;
		while(j--)
		{
			int t_v=remander*(1<<SHIFT)+val[j];
			remander=t_v%10;
			val[j]=t_v/10;
		}
		r_str[c_i++]='0'+remander;
		while(len&&!val[len-1]) len--;
	}
	while(c_i--) printf("%c",r_str[c_i]);
	free(val);
	free(r_str);
}

void bg_print_bin(BGInteger* bg)
{
	int t_len=SHIFT*abs(bg->b_len);
	if(bg->b_len<0)
	{
		printf("-");
	}
	printf("0b");

	if(bg->b_len==0)
	{
		printf("0");
		return ;
	}

	while(t_len--&&!bg_get_bit(bg,t_len));
	if(t_len<0)
	{
		printf("0");
		return ;
	}
	do
	{
		printf("%d",bg_get_bit(bg,t_len));
		if(t_len%15==0&&t_len!=0) printf(" ");
	}while(t_len--);
}

