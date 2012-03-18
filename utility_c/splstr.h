#ifndef _UTILITY_SPLSTR_H_
#define _UTILITY_SPLSTR_H_
#define SPLSTR_DEBUG

typedef struct tag_splstr
{
	char* str;
	unsigned int length;
	unsigned int max_cap;
}splstr;
typedef splstr splstr_t;
/* insert char at front , back ,and  middle*/

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

void splstr_push_front(splstr* s_str,char c);
void splstr_push_back(splstr* s_str,char c);
void splstr_insert_char(splstr* s_str,unsigned int pos,char c);

/*insert strings*/
void splstr_insert_str(splstr* s_str,unsigned int pos,const char* str);
void splstr_insert_splstr(splstr* s_str,unsigned int pos,splstr* str);

/*remove strings*/
void splstr_remove_range(splstr* s_str,unsigned int begin,unsigned int end);
void splstr_remove(splstr* s_str,unsigned int pos,unsigned int size);
void splstr_keep_front(splstr* s_str,unsigned int size);
void splstr_drop_tail(splstr* s_str,unsigned int size);

/*splstr assignment and copy*/
void splstr_copy(splstr* d_str,splstr* s_str);
void splstr_assign(splstr* d_str,const char* s_str);

/*substring */
void splstr_substr(splstr* s_str,unsigned int begin,unsigned int size);
void splstr_substr_range(splstr* s_str,unsigned int begin,unsigned int end);
splstr* splstr_create_substr(splstr* s_str,unsigned int begin,unsigned int size);
splstr* splstr_create_substr_range(splstr* s_str,unsigned int begin,unsigned int end);

/*length*/
int splstr_length(splstr* s_str);

/*memory alloc and free*/
splstr* splstr_alloc();
void splstr_free(splstr* s_str);

/*init and destory*/
void splstr_init(splstr* s_str);
void splstr_init_str(splstr* s_str,const char* str);
void splstr_destory(splstr* s_str);

/*debug interface*/
#ifdef SPLSTR_DEBUG
unsigned int round_log(unsigned size);
void splstr_realloc(splstr* s_str,unsigned int size);
#endif /*SPLSTR_DEBUG*/
#ifdef __cplusplus
}
#endif /*__cplusplus*/
 
#endif /*_UTILITY_SPLSTR_H_*/
