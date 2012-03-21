#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<splstr.h>
#define true 1
#define false 0

#define SIZE 20
#define test(func) \
	do{\
		printf("%-30s----",#func);\
		if(func){\
			printf("Ok\n");\
			correct_num++;\
		}\
		else{\
			printf("Failed\n"); \
			error_num++;\
		}\
	}while(0)
int test_round_log();
int test_realloc();
int test_push_front();
int test_push_back();
int test_insert_char();
int test_cmp();
int test_insert_str1();
int test_insert_str2(int pos);
int test_insert_str3();
int test_splstr_substr1();
int test_splstr_remove();


int main()
{
	srand((unsigned)time(NULL));
	int error_num=0;
	int correct_num=0;
	test(test_cmp());
	test(test_realloc());
	test(test_push_front());
	test(test_push_back());
	test(test_insert_char());
	test(test_insert_str1());
	test(test_insert_str2(3));
	test(test_insert_str2(0));
	test(test_insert_str3());
	test(test_splstr_substr1());
	test(test_splstr_remove());

	printf("correct_num=%d\n",correct_num);
	printf("error_num=%d\n",error_num);
	return 0;
}
int test_cmp()
{
	int i=-1;
	unsigned j=0;
	return i>=j;
}

int test_round_log()
{
	int i=1;

	int ret;
	while(i)
	{
		printf("input:");
		scanf("%d",&i);
		ret=round_log(i);
		printf("round_log(%d)=%d\n",i,ret);
	}
	return 1;
}

int test_realloc()
{
	return true;
}
int test_push_front()
{
	int width=26;
	int length=30;
	int i,j;
	splstr* str=splstr_alloc();
	char* s;
	splstr_init_str(str,"chenlin");
	s=str->str;
	//printf("str->length=%d,str->max_cap=%d,str->str=%s\n",str->length,str->max_cap,s);
	for(i=0;i<width;i++)
	{
		for(j=0;j<length;j++)
		{
			splstr_push_front(str,'a'+i);
			//printf("%c",'a'+i);
		}
	}

	s=str->str;
	//printf("\nstr->length=%d,str->max_cap=%d,str->str=%s\n",str->length,str->max_cap,s);
	if(str->length!=width*length+strlen("chenlin"))
	{
		return false;
	}
	for(i=width-1;i>=0;i--)
	{
		for(j=0;j<length;j++)
		{
			if(s[i*length+j]!=('a'+width-1-i))
			{
				//	printf("%c!=%c",s[i*length+j],'a'+width-1-i);
				return false;
			}
		}
	}
	if(strcmp("chenlin",s+width*length)!=0)
	{
		printf("failed 1\n");
		return false;
	}
	splstr_free(str);

	return true;
}






int test_push_back()
{
	const char* init="chenlin";
	int init_length=strlen(init);
	unsigned int width=26;
	unsigned int length=30;
	unsigned int i,j;
	splstr* str=splstr_alloc();
	char* s;
	splstr_init_str(str,init);
	for(i=0;i<width;i++)
	{
		for(j=0;j<length;j++)
		{
			splstr_push_back(str,'a'+i);
		}
	}
	s=str->str;
	if(str->length!=width*length+strlen(init))
	{
		printf("error 1\n");
		return false;
	}
	//printf("%s\n",s);
	if(strlen(s)!=str->length)
	{
		printf("strlen(str->str)=%d,str->length=%d\n",strlen(s),str->length);
		printf("error 2\n");
		return false;
	}
	for(i=0;i<strlen(init);++i)
	{
		if(s[i]!=init[i])
		{
			printf("error 3\n");
			return false;
		}
	}
	for(i=0;i<width;++i)
	{
		for(j=0;j<length;j++)
		{
			if(s[init_length+i*length+j]!='a'+i)
			{
				printf("error 4\n");
				return false;
			}
		}
	}
	splstr_free(str);
	return true;

}
int test_insert_char()
{
	const char* init="chenlin";
	int width=26;
	int length=30;
	int i,j;
	splstr* str=splstr_alloc();
	char* s;
	splstr_init_str(str,init);
	for(i=0;i<width;i++)
	{
		for(j=0;j<length;j++)
		{
			splstr_insert_char(str,3,'a'+i);
		}
	}
	s=str->str;
	if(str->length!=width*length+strlen(init))
	{
		printf("error 1\n");
		return false;
	}
	//printf("%s\n",s);
	if(strlen(s)!=str->length)
	{
		printf("strlen(str->str)=%d,str->length=%d\n",strlen(s),str->length);
		printf("error 2\n");
		return false;
	}
	for(i=0;i<3;i++)
	{
		if(s[i]!=init[i])
		{
			return false;
		}
	}
	for(i=width-1;i>=0;i--)
	{
		for(j=0;j<length;j++)
		{
			if(s[3+i*length+j]!=('a'+width-1-i))
			{
				//	printf("%c!=%c",s[i*length+j],'a'+width-1-i);
				return false;
			}
		}
	}
	for(i=0;i<4;i++)
	{
		if(s[3+width*length+i]!=init[i+3])
		{
			return false;
		}
	}

	splstr_free(str);
	return true;
}
int test_insert_str1()
{
	int major=5;
	int minor=6;
	int width=26;
	int array[26];
	char buf[100];
	int i,j,k;
	int length;
	char* s;
	
	splstr* str=splstr_alloc();
	splstr_init(str);
	for(i=0;i<width;i++)
	{
		array[i]=0;
	}

	
	for(i=0;i<width;++i)
	{
		for(j=0;j<major;++j)
		{
			for(k=0;k<minor;k++)
			{
				buf[k]='a'+i;
			}
			buf[minor]='\0';
			length=str->length;

			int pos=rand()%(length+1);

			splstr_insert_str(str,pos,buf);
		}
	}
	s=str->str;
	//printf("strlen(str->str)=%d,str->length=%d,real_size=%d,str->str=%s\n",strlen(s),str->length,major*minor*width,str->str);
	if(str->length!=major*minor*width)
	{
		printf("Error 1\n");
		return false;
	}
	if(strlen(s)!=str->length)
	{
		printf("Error 2\n");
		return false;
	}

	for(i=0;i<str->length;++i)
	{
		array[s[i]-'a']++;
	}
	for(i=0;i<width;++i)
	{
		if(array[i]!=minor*major)
		{
			printf("Error 3\n");
			return false;
		}
	}
	splstr_free(str);
	return true;

}

int test_insert_str2(int pos)
{
	int width=26;
	int length=6;
	char buf[100];
	char init[]="chenlin";
	int i,j;
	char* s;

	
	splstr* str=splstr_alloc();
	splstr_init_str(str,init);

	for(i=0;i<width;++i)
	{
		for(j=0;j<length;j++)
		{
			buf[j]='a'+i;
		}
			buf[length]='\0';
		splstr_insert_str(str,pos,buf);
	}
	s=str->str;
	for(i=0;i<pos;i++)
	{
		if(s[i]!=init[i])
		{
			printf("Error 1\n");
			return false;
		}
	}
	for(i=0;i<width;++i)
	{
		for(j=0;j<length;j++)
		{
			if(s[i*length+j+pos]!='a'+width-1-i)
			{
				printf("Error 2(%c,%c)\n",s[i*length+j+pos],'a'+width-1-i);
				return false;
			}
		}
	}
	//printf("(%s,%s)\n",init+pos,s+(width*length+pos));
	for(i=pos;i<strlen(init);++i)
	{
		if(init[i]!=s[width*length+i])
		{
			printf("Error 3(%c,%c)\n",init[pos],s[width*length+i]);
			return false;
		}
	}
	splstr_free(str);
	return true;
}


int test_insert_str3()
{
	int width=26;
	int length=6;
	char buf[100];
	int i,j;
	char* s;

	
	splstr* str=splstr_alloc();
	splstr_init(str);

	for(i=0;i<width;++i)
	{
		for(j=0;j<length;j++)
		{
			buf[j]='a'+i;
		}
			buf[length]='\0';
		splstr_insert_str(str,str->length,buf);
	}
	s=str->str;
	for(i=0;i<width;++i)
	{
		for(j=0;j<length;j++)
		{
			if(s[i*length+j]!='a'+i)
			{
				printf("Error 2(%c,%c)\n",s[i*length+j],'a'+i);
				return false;
			}
		}
	}
	//printf("(%s,%s)\n",init+pos,s+(width*length+pos));
	splstr_free(str);
	return true;
}
int test_splstr_substr1()
{
	unsigned int i,j,k;
	unsigned int width=26;
	unsigned int length=6;
	char buf[1023];
	splstr* a=NULL;
	splstr* b=NULL;
	splstr* c=NULL;
	splstr* d=NULL;
	splstr* e=NULL;
	char* p_a;
	char* p_b;
	char* p_d;
	char* p_e;
	for(k=0;k<width;k++)
	{
		a=splstr_alloc();
		b=splstr_alloc();
		c=splstr_alloc();
		splstr_init(a);
		splstr_init(b);
		splstr_init(c);

		for(i=0;i<width;++i)
		{
			for(j=0;j<length;j++)
			{
				buf[j]='a'+i;
			}
			buf[length]='\0';

			splstr_insert_str(a,a->length,buf);
			splstr_insert_str(b,b->length,buf);
			splstr_insert_str(c,c->length,buf);
		}
		splstr_substr(a,k*length,length);
		splstr_substr_range(b,k*length,k*length+length-1);

		d=splstr_create_substr(c,k*length,length);
		e=splstr_create_substr_range(c,k*length,k*length+length-1);

		if(a->length!=length)
		{
			printf("Error 1\n");
			return false;
		}
		if(b->length!=length)
		{
			printf("Error 2\n");
			return false;
		}
		if(d->length!=length)
		{
			printf("Error 3\n");
			return false;
		}
		if(e->length!=length)
		{
			printf("Error 4\n");
			return false;
		}

		p_a=a->str;
		p_b=b->str;
		p_d=d->str;
		p_e=e->str;
	//	printf("p_a=%s\n",p_a);
	//	printf("p_b=%s\n",p_b);
	//	printf("p_d=%s\n",p_d);
	//	printf("p_e=%s\n",p_e);
		for(i=0;i<length;++i)
		{
			if(p_a[i]!='a'+k)
			{
				printf("Error 5\n");
				return false;
			}
			if(p_b[i]!='a'+k)
			{
				printf("Error 6\n");
				return false;
			}
			if(p_d[i]!='a'+k)
			{
				printf("Error 7\n");
				return false;
			}
			if(p_e[i]!='a'+k)
			{
				printf("Error 8\n");
				return false;
			}
		}

		splstr_free(a);
		splstr_free(b);
		splstr_free(c);
		splstr_free(d);
		splstr_free(e);


	}
	return true;
}


int test_splstr_remove()
{
	unsigned int i,j,k;
	unsigned int width=26;
	unsigned int length=6;
	char buf[1023];
	splstr* a=NULL;
	splstr* b=NULL;
	char* p_a;
	char* p_b;
	unsigned int pos;
	for(k=0;k<width;k++)
	{
		a=splstr_alloc();
		b=splstr_alloc();
		splstr_init(a);
		splstr_init(b);
		for(i=0;i<width;++i)
		{
			for(j=0;j<length;j++)
			{
				buf[j]='a'+i;
			}
			buf[length]='\0';

			splstr_insert_str(a,a->length,buf);
			splstr_insert_str(b,b->length,buf);
		}
		splstr_remove_range(a,k*length,(k+1)*length-1);
		splstr_remove(b,k*length,length);
		if(a->length!=(width-1)*length)
		{
			printf("Error 1\n");
			return false;
		}
		if(b->length!=(width-1)*length)
		{
			printf("Error 2\n");
			return false;
		}
		p_a=a->str;
		p_b=b->str;
		//printf("p_a=%s\n",p_a);
		//printf("p_b=%s\n",p_b);
		for(i=0;i<width;++i)
		{
			if(i>k)
			{
				pos=i-1;
			}
			else
			{
				pos=i;

			}	
			if(i==k)
			{
				continue;
			}

			for(j=0;j<length;j++)
			{
				if(p_a[pos*length+j]!='a'+i)
				{
					printf("Error 3(pos=%d,%c,%c)\n",pos,p_a[pos*length+j],'a'+k);
					return false;
				}
				if(p_b[pos*length+j]!='a'+i)
				{
					printf("Error 4(pos=%d,%c,%c)\n",pos,p_b[pos*length+j],'a'+k);
					return false;
				}

			}
		}


		splstr_free(a);
		splstr_free(b);
	}
	return true;
}




