#include "lexical.h"
#include "lex_file.h"
#include <string.h>
#include "token.h"

struct state lex_state_err=
{
	"lex_state_err",
	0,
	0,
	0,
	0,
};
struct state* lex_state_err_array[]={&lex_state_err};
char input_map_other[ASCII_NUM]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

};

char* token_info[]=
{
	"unkown",
	"err",
	"eof",

	/*integer parts*/
	"nu_bin",
	"nu_oct",
	"nu_dec",
	"nu_hex",
	"nu_long",

	/*float parts*/
	"float",
	"exp_float",

	/*string parts*/
	"string",

	/*identifier parts*/
	"identifier",

	/*operator parts*/
	"comma",
	"period",
	"l_rb",
	"r_rb",
	"l_sb",
	"r_sb",
	"reverse",
	"not_equal",
	"bits_and",
	"bits_and_assign",
	"bit_or",
	"bit_or_assign",
	"bit_xor",
	"bit_xor_assign",
	"mul",
	"mul_assign",
	"mod",
	"mod_assign",
	"minus",
	"minus_assign",
	"plus",
	"plus_assign",
	"divide",
	"divide_assign",
	"assign",
	"equal",
	"right_shift",
	"right_shift_assign",
	"ge",
	"gt",
	"left_shift",
	"left_shift_assign",
	"le",
	"lt",
	
	/*annotate*/
	"annotate",

	/*white space*/
	"white_space",

	/*sentence break*/
	"semicolon",
	"newline",

	/*keyword*/
	"and",
	"as",
	"attr",
	"break",
	"catch",
	"class",
	"continue",
	"do",
	"elif",
	"else",
	"end",
	"finally",
	"for",
	"from",
	"func",
	"if",
	"import",
	"in",
	"inhrit",
	"not",
	"or",
	"print",
	"return",
	"then",
	"to",
	"try",
	"vfunc",
	"while",

};







/*lex_file interface*/
void lf_init(struct lex_file* lf,FILE* file)
{
	lf->l_file=file;
	lf->l_buf=(char*)malloc(LEX_FILE_DEFAULT_SIZE);
	lf->l_buf_cap=LEX_FILE_DEFAULT_SIZE;
	lf->l_buf_size=0;
	lf->l_begin=0;
	lf->l_mark=0;
	lf->l_read_pos=0;
};
struct lex_file* lf_create(char* file_name)
{
	FILE* file=fopen(file_name,"r");
	if(file==NULL)
	{
		return NULL;
	}
	struct lex_file* lf=(struct lex_file*)malloc(sizeof(*lf));
	lf_init(lf,file);
	return lf;
}
struct lex_file* lf_stream_create(FILE* file)
{
	if(file==NULL)
	{
		return NULL;
	}
	struct lex_file* lf=(struct lex_file*)malloc(sizeof(*lf));
	lf_init(lf,file);
	return lf;
};

void lf_destory(struct lex_file* lf)
{
	free(lf->l_buf);
	free(lf);
}
int lf_load_data(struct lex_file* lf)
{
	int readbyte;
	if(lf->l_buf_size==0)
	{
		readbyte=fread(lf->l_buf,sizeof(char),LEX_FILE_DEFAULT_SIZE,lf->l_file);
		lf->l_buf_size=readbyte;
		return readbyte;
	}

	int begin=lf->l_begin;
	int mark=lf->l_mark;
	int read_pos=lf->l_read_pos;
	int buf_cap=lf->l_buf_cap;

	int buf_used=read_pos-begin;
	int buf_free=buf_cap-buf_used;

	if(buf_free<LEX_FILE_DEFAULT_SIZE/2)
	{

		char* new_buf=(char*)malloc(lf->l_buf_cap*2);
		memcpy(new_buf,lf->l_buf+begin,buf_used);
		free(lf->l_buf);
		lf->l_buf=new_buf;
		lf->l_buf_cap=lf->l_buf_cap*2;

	}
	else
	{
		int i;
		char* buf=lf->l_buf;
		for(i=0;i<buf_used;i++)
		{
			buf[i]=buf[i+begin];
		}
	}

	lf->l_begin=0;
	lf->l_mark=mark-begin;
	lf->l_read_pos=read_pos-begin;

	readbyte=fread(lf->l_buf+buf_used,sizeof(char),lf->l_buf_cap-buf_used,lf->l_file);
	lf->l_buf_size=buf_used+readbyte;


	return readbyte;
}


struct keyword key_words[]=
{
	{"and",TOKEN_AND},
	{"as",TOKEN_AS},
	{"attr",TOKEN_ATTR},
	{"break",TOKEN_BREAK},
	{"catch",TOKEN_CATCH},
	{"class",TOKEN_CLASS},
	{"continue",TOKEN_CONTIUNE},
	{"do",TOKEN_DO},
	{"elif",TOKEN_ELIF},
	{"else",TOKEN_ELSE},
	{"end",TOKEN_END},
	{"finally",TOKEN_FINALLY},
	{"for",TOKEN_FOR},
	{"from",TOKEN_FROM},
	{"func",TOKEN_FUNC},
	{"if",TOKEN_IF},
	{"import",TOKEN_IMPORT},
	{"in",TOKEN_IN},
	{"inhrit",TOKEN_INHRIT},
	{"not",TOKEN_NOT},
	{"or",TOKEN_OR},
	{"print",TOKEN_PRINT},
	{"return",TOKEN_RETURN},
	{"then",TOKEN_THEN},
	{"to",TOKEN_TO},
	{"try",TOKEN_TRY},
	{"vfunc",TOKEN_VFUNC},
	{"while",TOKEN_WHILE},
};

int symbol_type(char* symbol)
{
	int begin=0;
	int end=KEYWORD_NUM-1;
	int middle;
	while(begin<=end)
	{
		middle=(begin+end)/2;
		int ret=strcmp(symbol,key_words[middle].k_name);
//		printf("cmp %s ,%s =%d\n",key_words[middle].k_name,symbol,ret);

		if(ret<0)
		{
			end=middle-1;
		}
		else if(ret >0)
		{
			begin=middle+1;

		}
		else
		{
			return key_words[middle].k_token;
		}
	}
	return TOKEN_ID;
}






