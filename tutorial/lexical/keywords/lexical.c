#include "lexical.h"
#include "token.h"
#include"string.h"
#include"stdio.h"


char* token_info[]=
{
	"variable",
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






