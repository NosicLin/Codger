#include"marocs.h"
#include"splstr.h"
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#define DEFAULT_SIZE 32

#ifdef SPLSTR_DEBUG
unsigned int round_log(unsigned size)
#else
static unsigned int round_log(unsigned size)
#endif /*SPLSTR_DEBUG*/
{
	unsigned int i=DEFAULT_SIZE;
	while(i<size)
	{
		i<<=1;
	}
	return i;
}


#ifdef SPLSTR_DEBUG 
void splstr_realloc(splstr* s_str,unsigned int size)
#else
static void splstr_realloc(splstr* s_str,unsigned int size)
#endif /*SPLSTR_DEBUG*/
{
	char* new_str;
	char* old_str=s_str->str;
	unsigned int length=s_str->length;
	size=round_log(size);
	if(size<s_str->length)
	{
		WARN("Realloc Lose Data,Refuse");
		return;
	}
	new_str=(char*)malloc(size);
	memcpy(new_str,old_str,length+1);
	free(old_str);
	s_str->max_cap=size;
	s_str->str=new_str;
}



/* insert char at front , back ,and  middle*/
void splstr_push_front(splstr* s_str,char c)
{
	splstr_insert_char(s_str,0,c);
}
void splstr_push_back(splstr* s_str,char c)
{
	splstr_insert_char(s_str,s_str->length,c);
}
void splstr_insert_char(splstr* s_str,unsigned int pos,char c)
{
	char* str;
	unsigned int i;
	unsigned int length=s_str->length;
	int size;

	if(pos>length)
	{
		WARN("Pos Out Of Range");
		pos=length;
	}
	if(length+1==s_str->max_cap)
	{
		splstr_realloc(s_str,s_str->max_cap+1);
	}
	str=s_str->str;
	size=length-pos;
	for(i=0;i<=size;i++)
	{
		str[pos+size-i+1]=str[pos+size-i];
	}
	str[pos]=c;
	s_str->length++;
}

/*insert strings*/
void splstr_insert_str(splstr* d_str,unsigned int pos,const char* s_str)
{
	unsigned int s_length=strlen(s_str);
	char* str;
	unsigned int i;
	unsigned int d_length=d_str->length;
	unsigned size;
	if(pos>d_length)
	{
		WARN("Pos Out Of Range");
		pos=d_length;
	}
	if(d_length+s_length+1>d_str->max_cap)
	{
		splstr_realloc(d_str,d_length+s_length+1);
	}
	str=d_str->str;
	size=d_length-pos;
	for(i=0;i<=size;i++)
	{
		str[pos+size-i+s_length]=str[pos+size-i];
	}
	memcpy(str+pos,s_str,s_length);
	d_str->length+=s_length;
}





void splstr_insert_splstr(splstr* d_str,unsigned pos,splstr* s_str)
{
	splstr_insert_str(d_str,pos,s_str->str);
}

/*remove strings*/
void splstr_remove_range(splstr* s_str,unsigned int begin,unsigned int end)
{
	if(end<begin)
	{
		WARN("Error Range");
		return ;
	}
	return splstr_remove(s_str,begin,end-begin+1);
}
void splstr_remove(splstr* s_str,unsigned int pos,unsigned int size)
{
	unsigned int s_length=s_str->length;
	char* str=s_str->str;
	unsigned int i;
	if(pos>=s_length)
	{
		WARN("Pos Out Of Range");
		return ;
	}
	if(pos+size>s_length)
	{
		size=s_length-pos;
	}
	for(i=pos+size;i<=s_length;i++)
	{
		str[i-size]=str[i];
	}
	s_str->length-=size;
}


void splstr_keep_front(splstr* s_str,unsigned int size)
{
	if(size>s_str->length)
	{
		WARN("Size Out Of Range");
		return ;
	}
	s_str->length=size;
	s_str->str[size]='\0';
}

void splstr_drop_tail(splstr* s_str,unsigned int size)
{
	if(size>s_str->length)
	{
		size=s_str->length;
	}
	s_str->length-=size;
	s_str->str[s_str->length]='\0';
}

/*splstr assignment and copy*/
void splstr_copy(splstr* d_str,splstr* s_str)
{
	splstr_assign(d_str,s_str->str);
}
void splstr_assign(splstr* d_str,const char* s_str)
{
	unsigned int s_length=strlen(s_str);
	char* str;
	if(s_length+1>d_str->max_cap)
	{
		splstr_realloc(d_str,s_length+1);
	}
	str=d_str->str;
	memcpy(str,s_str,s_length+1);
	d_str->length=s_length;
}

/*substring */
void splstr_substr(splstr* s_str,unsigned int begin,unsigned int size)
{
	unsigned int i;
	char* str=s_str->str;
	unsigned int length=s_str->length;
	if(begin>=length)
	{
		WARN("Parameter Out Of Range");
		s_str->str[0]='\0';
		s_str->length=0;
		return;
	}

	if(begin+size>length)
	{
		size=length-begin;
	}

	for(i=0;i<size;i++)
	{
		str[i]=str[i+begin];
	}
	str[size]='\0';
	s_str->length=size;
}
void splstr_substr_range(splstr* s_str,unsigned int begin,unsigned int end)
{
	if(end<begin)
	{
		WARN("Error Range");
		splstr_substr(s_str,0,0);
		return ;
	}
	splstr_substr(s_str,begin,end-begin+1);
}
splstr* splstr_create_substr(splstr* s_str,unsigned int begin,unsigned int size)
{
	unsigned int length=s_str->length;
	splstr* result=splstr_alloc();
	splstr_init(result);
	if(begin>=length)
	{
		WARN("Parameter Out Of Range");
		return result;
	}

	if(begin+size>length)
	{
		size=length-begin;
	}
	if(size+1>result->length)
	{
		splstr_realloc(result,size+1);
	}

	memcpy(result->str,s_str->str+begin,size);
	result->length=size;
	result->str[size]='\0';
	return result;
}

splstr* splstr_create_substr_range(splstr* s_str,unsigned int begin,unsigned int end)
{
	splstr* result=NULL;
	if(end<begin)
	{
		result=splstr_alloc();
		WARN("Error Range");
		splstr_init(result);
		return result;
	}
	return splstr_create_substr(s_str,begin,end-begin+1);
}


/*length*/
int splstr_length(splstr* s_str)
{
	return s_str->length;
}

/*memory alloc and free*/
splstr* splstr_alloc()
{
	return (splstr*) malloc(sizeof(splstr));
}
void splstr_free(splstr* s_str)
{
	splstr_destory(s_str);
	free(s_str);
}

/*init and destory*/
void splstr_init(splstr* s_str)
{
	s_str->max_cap=DEFAULT_SIZE;
	s_str->length=0;
	s_str->str=(char*)malloc(DEFAULT_SIZE);
	s_str->str[0]='\0';
}

void splstr_init_str(splstr* s_str,const char* str)
{
	unsigned length=strlen(str);
	unsigned max_cap=round_log(length);
	s_str->max_cap=max_cap;
	s_str->length=length;
	s_str->str=(char*)malloc(max_cap);
	memcpy(s_str->str,str,length+1);
}


void splstr_destory(splstr* s_str)
{
	free(s_str->str);
	s_str->length=0;
	s_str->max_cap=0;
	s_str->str=NULL;
}


