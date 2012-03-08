#include"big_integer.h"
#include<utility_c/marocs.h>
#include<string.h>
#include<stdlib.h>
#define DEFALUT_BIG_INTEGER_LENGTH 3 
#define BGLONG_SHIFT 15
#define BGLONG_BASE ((b_unit)1<<BGLONG_SHIFT)
#define BGLONG_MASK ((b_unit)(BGLONG_BASE-1))

#define SHIFT BGLONG_SHIFT
#define BASE BGLONG_BASE
#define MASK BGLONG_MASK 

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

static void bg_negative(BGInteger* bg)
{
	bg->b_len*=-1;
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
	BUG_ON(pos>=bg->b_len*SHIFT,"Error Pos");
	int pre=pos/BGLONG_SHIFT;
	int sub=pos%BGLONG_SHIFT;
	return (bg->b_val[pre]&(1<<sub))!=0;
}
static inline void bg_set_bit(BGInteger* bg,long pos,int value)
{
	BUG_ON(pos>=bg->b_len*SHIFT,"Error Pos");
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

static BGInteger* bg_create_zero()
{
	BGInteger* ret=bg_malloc(1);
	ret->b_len=0;
	return ret;
}


BGInteger* bg_create_from_int(int value)
{
	BGInteger* ret=bg_malloc(DEFALUT_BIG_INTEGER_LENGTH);
	if(value<0)
	{
		bg_negative(ret);
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
BGInteger* bg_create_from_hexstr(char* str)
{

	int len=strlen(str);
	BGInteger* ret=bg_malloc(len*4/SHIFT+1);
	int c_bit=0;
	int c_i;
	while(len--)
	{
		int c_val=str[len]<='9'?str[len]-'0':str[len]-'a'+10;
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
	char* str=(char*)malloc(len+1);
	memcpy(str,decstr,len+1);
	char* str2=(char*)malloc(len+1);

	BGInteger* ret=bg_malloc(len*4/SHIFT+1);

	char* cal_str=str;
	char* re_str=str2;

	int c_bit=0;
	while(cal_str[0])
	{
		int i=0;
		int c_remainder=0;
		while(cal_str[i])
		{
			int c_val=cal_str[i]-'0'+c_remainder*10;
			re_str[i]=(c_val/2)+'0';
			c_remainder=c_val%2;
			i++;
		}
		bg_set_bit(ret,c_bit++,c_remainder);
		re_str[i]='\0';
		if(re_str[0]=='0') re_str++;
		char* temp=cal_str;
		cal_str=re_str;
		re_str=temp;
	}
	free(str2);
	free(str);
	bg_format_len(ret);
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
		bg_negative(ret);
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
			bg_negative(ret);
		}
		else
		{
			/*l<0,r>=0
			 * ret=-(abs(r)-abs(r))
			 */
			ret=abs_minus(l,r);
			bg_negative(ret);
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
			bg_negative(ret);
		}
		else
		{
			/* l<0,r>=0
			 * l-r=-abs(l)-abs(r)=-(abs(l)+abs(r));
			 */
			ret=abs_plus(l,r);
			bg_negative(ret);
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
	int sign=l->b_len*r->b_len<0?-1:1;
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
	if(sign==-1)
	{
		bg_negative(ret);
	}
	bg_format_len(ret);
	return ret;
}
BGInteger* bg_mul(BGInteger* l,BGInteger* r)
{
	BGInteger* ret=abs_mul(l,r);
	if(l->b_len*r->b_len<0)
	{
		bg_negative(ret);
	}
	return ret;
}

/*
 * @r!=0;
 * 2<=r->len<=l->r->len;
 */
static BGInteger* abs_divrem(BGInteger* l,BGInteger* r,BGInteger** prem)
{
	BUG_ON(l->b_len<r->b_len||r->b_len<2,"Error Length");
	BGInteger *x,*y,*rem;
	int n,i,t;
	b_unit yt, yt_1 ,xi,xi_1,xi_2,q,r,x_val,y_val,carry,xtop;
	twob_unit xx;

	int n=l->b_len;
	int t=r->b_len;

	x=bg_malloc(n+1);
	y=bg_malloc(t);

	int d=SHIFT-bg_bit_in_unit(r->b_val[t-1]);
	carry=units_lshift(y->b_val,r->b_val,t,d);
	assert(carry==0);
	carry=units_lshift(x->b_val,l->b_val,n,d);


	if(carry!=0||x->b_val[n-1]>=y->b_val[t-1])
	{
		x->b_val[n]=carry;
		n++;
	}


	int k=n-t;
	big_integer* ret=bg_malloc(k);

	x_val=x->b_val;
	y_val=y->b_val;

	yt=y_val[t-1];
	yt_1=y_val[t-2];

	for(c_x=x_val+k,c_r=ret->b_val+k; c_x-- > x_val)
	{
		xi=c_x[t];
		xi_1=c_x[t-1];
		xi_2=c_x[t-2];

		xx=x_i<<SHIFT|xi_1;
		
		q=(b_unit)(vv/yt);
		r=(b_unit)(vv-(twob_unit)yt*q);

		while((twob_unit)yt_1*q>(((twob_unit)r<<SHIFT)|xi_2))
		{
			--q;
			r+=yt;
			if(r>=BASE)
			{
				break;
			}
		}

		sb_unit brorrow=0;
		stwob_unit z;
		for(i=0;i<t;i++)
		{
			z=(sb_unit)c_x[i]+brorrow-(stwob_unit)q*(stwob_unit)y_val[i];
			c_x[i]=(digit)z&MASK;
			brorrow=(sb_unit)z>>SHIFT;
		}
		if(xi+brorrow<0)
		{
			carry=0;
			for(i=0;i<t;++i)
			{
				carry+=c_x[i]+y_val[i];
				c_x[i]=carry&MASK;
				carry>>=SHIFT;
			}
			--q;
		}

		*--ak=q;
	}
	carry=i_rshift(y,x,t,d);
	bg_free(x);
	bg_format_len(y);
	*prem=y;
	bg_format_len(ret);
	return ret;
}




BGInteger* bg_div(BGInteger* l,BGInteger* r);
BGInteger* bg_mod(BGInteger* l,BGInteger* r);

BGInteger* bg_lshift(BGInteger* l,BGInteger* r);
BGInteger* bg_rshift(BGInteger* l,BGInteger* r);


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

	while(!bg_get_bit(bg,--t_len));


	do
	{
		printf("%d",bg_get_bit(bg,t_len));
	}while(t_len--);
}



