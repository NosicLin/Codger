
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "grammar.y"

#include<assert.h>
#include"yylex.h"
#include"ast_nodes.h"
#include"parser.h"
#include<object/gr_int.h>
#include<object/gr_float.h>
#include<object/gr_string.h>
#include<memory/gc.h>
#include<object/gr_consts.h>
#include<object/gr_class.h>
/* I don't want to use void* for default symbol type
 * but if not,i will give every symbol a type,
 * so awfull 
 * FIXME wish someday, someone tell me  how to give part of symbols 
 * a default type 
 */
#define YYSTYPE void*  


/* Line 189 of yacc.c  */
#line 94 "grammar.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tUNKOWN = 258,
     tERR = 259,
     tINTEGER = 260,
     tLONG = 261,
     tFLAOT = 262,
     tSTRING = 263,
     tID = 264,
     tDOLLAR = 265,
     tCOMMA = 266,
     tPERIOD = 267,
     tL_RB = 268,
     tR_RB = 269,
     tL_SB = 270,
     tR_SB = 271,
     tASSIGN = 272,
     tAMUL = 273,
     tADIV = 274,
     tAMOD = 275,
     tAPLUS = 276,
     tAMINUS = 277,
     tALS = 278,
     tARS = 279,
     tAAND = 280,
     tAOR = 281,
     tAXOR = 282,
     tMUL = 283,
     tDIV = 284,
     tMOD = 285,
     tPLUS = 286,
     tMINUS = 287,
     tLS = 288,
     tRS = 289,
     tAND = 290,
     tOR = 291,
     tXOR = 292,
     tNEGATED = 293,
     tLT = 294,
     tLE = 295,
     tNE = 296,
     tEQ = 297,
     tGE = 298,
     tGT = 299,
     tSEMI = 300,
     tNEWLINE = 301,
     kAND = 302,
     kAS = 303,
     kATTR = 304,
     kBREAK = 305,
     kCATCH = 306,
     kCLASS = 307,
     kCONTINUE = 308,
     kDO = 309,
     kELIF = 310,
     kELSE = 311,
     kEND = 312,
     kEXPORT = 313,
     kFINALLY = 314,
     kFOR = 315,
     kFROM = 316,
     kFUNC = 317,
     kIF = 318,
     kIMPORT = 319,
     kIN = 320,
     kINHRIT = 321,
     kNEW = 322,
     kNOT = 323,
     kOR = 324,
     kPRINT = 325,
     kPRIVATE = 326,
     kPROTECTED = 327,
     kPUBLIC = 328,
     kRETURN = 329,
     kSTATIC = 330,
     kTHEN = 331,
     kTO = 332,
     KTRY = 333,
     kVFUNC = 334,
     kWHILE = 335,
     kTRUE = 336,
     kFALSE = 337
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 218 "grammar.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   467

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  168
/* YYNRULES -- Number of states.  */
#define YYNSTATES  251

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   337

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    16,    19,    21,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    46,    48,    50,    52,    54,    56,    58,    60,
      62,    64,    66,    69,    71,    74,    76,    80,    84,    87,
      89,    91,    93,    95,    97,   101,   103,   105,   107,   109,
     111,   113,   118,   123,   127,   131,   133,   135,   138,   140,
     142,   144,   146,   150,   152,   154,   156,   158,   162,   164,
     166,   168,   172,   174,   176,   178,   182,   184,   188,   190,
     194,   196,   200,   202,   204,   206,   208,   210,   214,   216,
     218,   220,   223,   225,   229,   231,   235,   237,   239,   243,
     247,   249,   251,   253,   255,   257,   259,   261,   263,   265,
     267,   270,   275,   278,   281,   283,   289,   291,   293,   295,
     298,   304,   309,   315,   317,   319,   321,   329,   331,   333,
     335,   337,   339,   342,   344,   353,   361,   363,   365,   367,
     369,   373,   374,   376,   378,   380,   382,   386,   389,   397,
     403,   405,   406,   408,   410,   413,   417,   420,   422,   425,
     428,   432,   434,   436,   438,   440,   442,   445,   450
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      84,     0,    -1,    86,    -1,    87,    -1,    88,    -1,    88,
      87,    -1,    85,    88,    87,    -1,    85,    88,    -1,    85,
      -1,    -1,   121,    -1,   122,    -1,   123,    -1,   127,    -1,
     128,    -1,   130,    -1,   133,    -1,   135,    -1,   136,    -1,
     137,    -1,   146,    -1,   126,    -1,   125,    -1,    46,    -1,
      45,    -1,     5,    -1,     6,    -1,     7,    -1,     8,    -1,
      82,    -1,    81,    -1,     9,    -1,    10,     9,    -1,    93,
      -1,    93,    11,    -1,   120,    -1,    93,    11,   120,    -1,
      95,    92,    96,    -1,    95,    96,    -1,    15,    -1,    16,
      -1,    13,    -1,    14,    -1,    89,    -1,    13,   120,    14,
      -1,    90,    -1,    94,    -1,    91,    -1,   138,    -1,   139,
      -1,    99,    -1,   100,    95,   120,    96,    -1,   100,    97,
      92,    98,    -1,   100,    97,    98,    -1,   100,    12,    90,
      -1,   100,    -1,   100,    -1,   103,   102,    -1,    31,    -1,
      32,    -1,    38,    -1,   102,    -1,   104,   105,   102,    -1,
      28,    -1,    29,    -1,    30,    -1,   104,    -1,   106,   107,
     104,    -1,    31,    -1,    32,    -1,   106,    -1,   108,   109,
     106,    -1,    33,    -1,    34,    -1,   108,    -1,   110,    35,
     108,    -1,   110,    -1,   111,    37,   110,    -1,   111,    -1,
     112,    36,   111,    -1,   112,    -1,   113,   114,   112,    -1,
      39,    -1,    40,    -1,    43,    -1,    44,    -1,   113,    -1,
     115,   116,   113,    -1,    42,    -1,    41,    -1,   115,    -1,
      68,   117,    -1,   117,    -1,   118,    47,   117,    -1,   118,
      -1,   119,    69,   118,    -1,   119,    -1,   120,    -1,   101,
      17,   120,    -1,   101,   124,   120,    -1,    18,    -1,    19,
      -1,    20,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    27,    -1,    26,    -1,    64,    90,    -1,
      58,    90,    48,    90,    -1,    58,    90,    -1,    70,    92,
      -1,    70,    -1,    80,   120,   129,    86,    57,    -1,    46,
      -1,    54,    -1,    45,    -1,   131,    57,    -1,   131,    56,
     132,    86,    57,    -1,    63,   120,   132,    86,    -1,   131,
      55,   120,   132,    86,    -1,    46,    -1,    76,    -1,    45,
      -1,    60,   101,    65,   120,   134,    86,    57,    -1,    46,
      -1,    54,    -1,    45,    -1,    50,    -1,    53,    -1,    74,
     120,    -1,    74,    -1,    62,    90,    97,   141,    98,   140,
      86,    57,    -1,    62,    97,   141,    98,   140,    86,    57,
      -1,    46,    -1,    11,    -1,    54,    -1,   142,    -1,   141,
      11,   142,    -1,    -1,   143,    -1,   144,    -1,   145,    -1,
      90,    -1,    90,    17,   120,    -1,    28,    90,    -1,    52,
      90,    66,    90,    88,   147,    57,    -1,    52,    90,    88,
     147,    57,    -1,   148,    -1,    -1,   149,    -1,    88,    -1,
      88,   149,    -1,   148,    88,   149,    -1,   148,    88,    -1,
     151,    -1,   150,   151,    -1,    75,   151,    -1,    75,   150,
     151,    -1,    73,    -1,    72,    -1,    71,    -1,   152,    -1,
     153,    -1,    49,    90,    -1,    49,    90,    17,   120,    -1,
      62,    90,    97,   141,    98,   140,    86,    57,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    48,    48,    50,    58,    65,    73,    78,    81,    83,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   105,   105,   108,   116,   119,   127,   138,
     144,   151,   161,   174,   175,   178,   185,   193,   200,   211,
     212,   213,   214,   216,   217,   218,   219,   220,   221,   222,
     225,   226,   234,   243,   254,   263,   265,   266,   274,   275,
     276,   279,   280,   289,   290,   291,   294,   295,   304,   305,
     308,   309,   318,   319,   323,   324,   332,   333,   342,   343,
     354,   355,   365,   366,   367,   368,   372,   373,   382,   383,
     388,   389,   398,   399,   408,   409,   419,   421,   430,   444,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     472,   481,   489,   498,   505,   515,   524,   524,   524,   527,
     528,   538,   549,   560,   560,   560,   563,   572,   572,   572,
     574,   581,   588,   595,   606,   616,   628,   628,   628,   631,
     638,   644,   651,   652,   653,   656,   663,   672,   681,   689,
     699,   701,   709,   717,   723,   730,   735,   738,   748,   758,
     767,   778,   779,   780,   783,   784,   787,   795,   804
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tUNKOWN", "tERR", "tINTEGER", "tLONG",
  "tFLAOT", "tSTRING", "tID", "tDOLLAR", "tCOMMA", "tPERIOD", "tL_RB",
  "tR_RB", "tL_SB", "tR_SB", "tASSIGN", "tAMUL", "tADIV", "tAMOD",
  "tAPLUS", "tAMINUS", "tALS", "tARS", "tAAND", "tAOR", "tAXOR", "tMUL",
  "tDIV", "tMOD", "tPLUS", "tMINUS", "tLS", "tRS", "tAND", "tOR", "tXOR",
  "tNEGATED", "tLT", "tLE", "tNE", "tEQ", "tGE", "tGT", "tSEMI",
  "tNEWLINE", "kAND", "kAS", "kATTR", "kBREAK", "kCATCH", "kCLASS",
  "kCONTINUE", "kDO", "kELIF", "kELSE", "kEND", "kEXPORT", "kFINALLY",
  "kFOR", "kFROM", "kFUNC", "kIF", "kIMPORT", "kIN", "kINHRIT", "kNEW",
  "kNOT", "kOR", "kPRINT", "kPRIVATE", "kPROTECTED", "kPUBLIC", "kRETURN",
  "kSTATIC", "kTHEN", "kTO", "KTRY", "kVFUNC", "kWHILE", "kTRUE", "kFALSE",
  "$accept", "AstTree", "stmts", "block", "stmt", "stmt_delimiter",
  "literal", "identifier", "upper_id", "expr_list", "expr_list_pre",
  "array", "l_sb", "r_sb", "l_rb", "r_rb", "primary_expr", "postfix_expr",
  "symbols", "unary_expr", "unary_operator", "multiply_expr",
  "multiply_operator", "additive_expr", "additive_operator", "shift_expr",
  "shift_operator", "bit_and_expr", "bit_xor_expr", "bit_or_expr",
  "relational_expr", "relational_operator", "equal_expr", "equal_operator",
  "logic_not_expr", "logic_and_expr", "logic_or_expr", "expr", "stmt_expr",
  "stmt_assign", "stmt_oper_assign", "oper_assing_operator", "stmt_import",
  "stmt_export", "stmt_print", "stmt_while", "while_delimter", "stmt_if",
  "if_pre", "if_delimter", "stmt_for", "for_delimter", "stmt_break",
  "stmt_continue", "stmt_return", "func_declare", "lambda_delare",
  "func_delimeter", "args_list", "arg", "simply_arg", "default_arg",
  "many_args", "class_declare", "class_block", "class_stmts",
  "class_stmt_decorate", "access_control", "class_stmt", "attr_stmt",
  "method_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    85,    85,    85,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    88,    88,    89,    89,    89,    89,    89,
      89,    90,    91,    92,    92,    93,    93,    94,    94,    95,
      96,    97,    98,    99,    99,    99,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   101,   102,   102,   103,   103,
     103,   104,   104,   105,   105,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     113,   113,   114,   114,   114,   114,   115,   115,   116,   116,
     117,   117,   118,   118,   119,   119,   120,   121,   122,   123,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   126,   126,   127,   127,   128,   129,   129,   129,   130,
     130,   131,   131,   132,   132,   132,   133,   134,   134,   134,
     135,   136,   137,   137,   138,   139,   140,   140,   140,   141,
     141,   141,   142,   142,   142,   143,   144,   145,   146,   146,
     147,   147,   148,   148,   148,   148,   148,   149,   149,   149,
     149,   150,   150,   150,   151,   151,   152,   152,   153
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     3,     2,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     3,     3,     2,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     4,     4,     3,     3,     1,     1,     2,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     2,     1,     3,     1,     3,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     4,     2,     2,     1,     5,     1,     1,     1,     2,
       5,     4,     5,     1,     1,     1,     7,     1,     1,     1,
       1,     1,     2,     1,     8,     7,     1,     1,     1,     1,
       3,     0,     1,     1,     1,     1,     3,     2,     7,     5,
       1,     0,     1,     1,     2,     3,     2,     1,     2,     2,
       3,     1,     1,     1,     1,     1,     2,     4,     8
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       9,    25,    26,    27,    28,    31,     0,     0,    39,    58,
      59,    60,    24,    23,   130,     0,   131,     0,     0,     0,
       0,     0,     0,   114,   133,     0,    30,    29,     0,     8,
       2,     3,     4,    43,    45,    47,    46,     0,    50,    56,
       0,    61,     0,    66,    70,    74,    76,    78,    80,    86,
      90,    92,    94,    96,    97,    10,    11,    12,    22,    21,
      13,    14,    15,     0,    16,    17,    18,    19,    48,    49,
      20,    32,    56,     0,     0,   112,    55,     0,    41,     0,
     141,     0,   110,    91,   113,    33,    35,   132,     0,     1,
       7,     5,    40,     0,    38,     0,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   106,   107,   109,   108,     0,
      57,    63,    64,    65,     0,    68,    69,     0,    72,    73,
       0,     0,     0,     0,    82,    83,    84,    85,     0,    89,
      88,     0,     0,     0,     0,     0,   119,    44,     0,   151,
       0,     0,   141,     0,   145,     0,   139,   142,   143,   144,
     125,   123,   124,     9,    34,   118,   116,   117,     9,     6,
      37,    54,     0,    42,     0,    53,    98,    99,    62,    67,
      71,    75,    77,    79,    81,    87,    93,    95,     0,     9,
       0,     0,     0,   163,   162,   161,     0,   153,     0,   150,
     152,     0,   157,   164,   165,   111,     0,     0,   147,     0,
       0,     0,   121,    36,     0,    51,    52,     9,     0,   151,
     166,     0,     0,   159,   154,   149,   156,   158,   129,   127,
     128,     9,     0,   146,   140,   137,   136,   138,     9,   115,
     122,   120,     0,     0,   141,   160,   155,     0,     9,     0,
     148,   167,     0,   126,     0,   135,     0,   134,     9,     0,
     168
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    84,
      85,    36,    37,    94,    97,   165,    38,    72,    40,    41,
      42,    43,   114,    44,   117,    45,   120,    46,    47,    48,
      49,   128,    50,   131,    51,    52,    53,    54,    55,    56,
      57,   109,    58,    59,    60,    61,   158,    62,    63,   153,
      64,   221,    65,    66,    67,    68,    69,   228,   145,   146,
     147,   148,   149,    70,   188,   189,   190,   191,   192,   193,
     194
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -192
static const yytype_int16 yypact[] =
{
     204,  -192,  -192,  -192,  -192,  -192,     5,   374,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,    19,  -192,    19,   134,    76,
     374,    19,   374,   374,   374,   374,  -192,  -192,    54,    50,
    -192,  -192,   282,  -192,  -192,  -192,  -192,   293,  -192,   396,
     440,  -192,    36,    49,   123,   141,    29,    34,    52,   129,
     125,  -192,    59,    45,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,    64,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,   133,   102,   -10,    77,   133,    68,  -192,   115,
      63,   -16,  -192,  -192,  -192,   146,  -192,  -192,    -6,  -192,
     282,  -192,  -192,   120,  -192,    19,   374,   363,   374,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,   374,
    -192,  -192,  -192,  -192,    36,  -192,  -192,    36,  -192,  -192,
      36,    36,    36,    36,  -192,  -192,  -192,  -192,    36,  -192,
    -192,    36,   374,   374,   374,   -16,  -192,  -192,    19,    89,
      19,   374,    63,    19,   135,    23,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,   204,   374,  -192,  -192,  -192,   204,  -192,
    -192,  -192,   120,  -192,   145,  -192,  -192,  -192,  -192,    49,
     123,   141,    29,    34,    52,   129,  -192,    59,   -16,   204,
      50,    19,    19,  -192,  -192,  -192,    37,    51,   106,    50,
    -192,    14,  -192,  -192,  -192,  -192,    57,    23,  -192,   374,
      63,    11,  -192,  -192,   119,  -192,  -192,   204,   121,    89,
     160,   115,    14,  -192,  -192,  -192,    51,  -192,  -192,  -192,
    -192,   204,    11,  -192,  -192,  -192,  -192,  -192,   204,  -192,
    -192,  -192,   124,   374,    63,  -192,  -192,   126,   204,   127,
    -192,  -192,    23,  -192,   130,  -192,    11,  -192,   204,   131,
    -192
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,  -141,    -9,   -24,  -192,   -11,  -192,   -22,
    -192,  -192,   -14,   -80,   -18,  -138,  -192,     0,   162,   -31,
    -192,    65,  -192,    66,  -192,    69,  -192,    70,    71,    72,
      60,  -192,  -192,  -192,   -20,    73,  -192,    -4,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -108,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -191,  -133,    -3,
    -192,  -192,  -192,  -192,    -8,  -192,  -163,    12,  -139,  -192,
    -192
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -56
static const yytype_int16 yytable[] =
{
      39,    80,    83,    73,    74,    90,    75,   201,    79,   197,
      82,   110,   202,   160,    71,    93,    81,   204,    76,    86,
      87,    88,   225,    91,   214,    96,   206,   179,     5,   150,
     151,   238,    39,    86,   200,    12,    13,   163,   208,   155,
     156,     1,     2,     3,     4,     5,     6,   213,   157,     7,
     139,     8,   217,   236,    89,   248,   138,   226,    96,   222,
     152,   142,    96,   181,   121,   227,   230,     9,    10,   144,
     207,   122,     5,   235,    11,   164,   182,   111,   112,   113,
     237,   159,   205,   168,   161,     5,   181,   239,   123,    78,
      39,   143,   162,    86,   166,    12,    13,   244,    19,   182,
     181,   242,   218,   219,   246,   167,   132,   249,   183,   184,
     185,   220,   176,   182,   133,   187,   137,    26,    27,   134,
     135,   136,   183,   184,   185,   140,   186,   180,    78,   195,
     178,   144,   198,   141,    12,    13,    92,   196,   181,     1,
       2,     3,     4,     5,     6,    95,    78,     7,     8,     8,
     203,   182,   199,    39,   115,   116,   209,   154,    39,   163,
     183,   184,   185,   215,   186,   216,   129,   130,   124,   125,
     210,   211,   126,   127,   118,   119,   229,   233,   231,    39,
      77,   240,   169,   243,   245,   187,   170,   247,   250,   144,
     171,   175,   172,   234,   173,   223,    19,   224,   212,     0,
     174,   232,     0,     0,     0,     0,   177,    39,     0,     1,
       2,     3,     4,     5,     6,    26,    27,     7,     0,     8,
       0,    39,     0,   144,     0,     0,     0,     0,    39,   241,
       0,     0,     0,     0,     0,     9,    10,     0,    39,     0,
       0,     0,    11,     0,     0,     0,     0,     0,    39,    12,
      13,     0,     0,     0,    14,     0,    15,    16,     0,     0,
       0,     0,    17,     0,    18,     0,    19,    20,    21,     0,
       0,     0,    22,     0,    23,     0,     0,     0,    24,     0,
       0,     0,     0,     0,    25,    26,    27,     1,     2,     3,
       4,     5,     6,     0,     0,     7,     0,     8,     1,     2,
       3,     4,     5,     6,     0,     0,     7,     0,     8,    92,
       0,     0,     0,     9,    10,     0,     0,     0,     0,     0,
      11,     0,     0,     0,     9,    10,     0,     0,     0,     0,
       0,    11,    14,     0,    15,    16,     0,     0,     0,     0,
      17,     0,    18,     0,    19,    20,    21,     0,     0,     0,
      22,     0,    23,     0,     0,    19,    24,     0,     0,     0,
       0,    22,    25,    26,    27,     0,     0,     0,     1,     2,
       3,     4,     5,     6,    26,    27,     7,   163,     8,     1,
       2,     3,     4,     5,     6,     0,     0,     7,     0,     8,
       0,     0,     0,     0,     9,    10,     0,     0,     0,     0,
       0,    11,     0,     0,     0,     9,    10,     0,    95,    78,
       0,     8,    11,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,   -55,   -55,     0,    19,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,    22,     0,    26,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,    27,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108
};

static const yytype_int16 yycheck[] =
{
       0,    19,    22,     7,    15,    29,    17,   145,    19,   142,
      21,    42,   153,    93,     9,    37,    20,   158,    18,    23,
      24,    25,    11,    32,   187,    39,   164,   135,     9,    45,
      46,   222,    32,    37,    11,    45,    46,    14,   179,    45,
      46,     5,     6,     7,     8,     9,    10,   186,    54,    13,
      74,    15,   191,   216,     0,   246,    66,    46,    72,   197,
      76,    79,    76,    49,    35,    54,   207,    31,    32,    80,
     178,    37,     9,   212,    38,    97,    62,    28,    29,    30,
     221,    90,   162,   114,    95,     9,    49,   228,    36,    13,
      90,    28,    96,    97,    98,    45,    46,   238,    62,    62,
      49,   234,    45,    46,   242,   109,    47,   248,    71,    72,
      73,    54,   132,    62,    69,   139,    14,    81,    82,    55,
      56,    57,    71,    72,    73,    48,    75,   138,    13,   140,
     134,   142,   143,    65,    45,    46,    16,   141,    49,     5,
       6,     7,     8,     9,    10,    12,    13,    13,    15,    15,
     154,    62,    17,   153,    31,    32,   180,    11,   158,    14,
      71,    72,    73,    57,    75,   189,    41,    42,    39,    40,
     181,   182,    43,    44,    33,    34,    57,    17,    57,   179,
      18,    57,   117,    57,    57,   209,   120,    57,    57,   200,
     121,   131,   122,   211,   123,   199,    62,   200,   186,    -1,
     128,   209,    -1,    -1,    -1,    -1,   133,   207,    -1,     5,
       6,     7,     8,     9,    10,    81,    82,    13,    -1,    15,
      -1,   221,    -1,   234,    -1,    -1,    -1,    -1,   228,   233,
      -1,    -1,    -1,    -1,    -1,    31,    32,    -1,   238,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,   248,    45,
      46,    -1,    -1,    -1,    50,    -1,    52,    53,    -1,    -1,
      -1,    -1,    58,    -1,    60,    -1,    62,    63,    64,    -1,
      -1,    -1,    68,    -1,    70,    -1,    -1,    -1,    74,    -1,
      -1,    -1,    -1,    -1,    80,    81,    82,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    -1,    15,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    -1,    15,    16,
      -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,
      -1,    38,    50,    -1,    52,    53,    -1,    -1,    -1,    -1,
      58,    -1,    60,    -1,    62,    63,    64,    -1,    -1,    -1,
      68,    -1,    70,    -1,    -1,    62,    74,    -1,    -1,    -1,
      -1,    68,    80,    81,    82,    -1,    -1,    -1,     5,     6,
       7,     8,     9,    10,    81,    82,    13,    14,    15,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    -1,    15,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    -1,    31,    32,    -1,    12,    13,
      -1,    15,    38,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,     8,     9,    10,    13,    15,    31,
      32,    38,    45,    46,    50,    52,    53,    58,    60,    62,
      63,    64,    68,    70,    74,    80,    81,    82,    84,    85,
      86,    87,    88,    89,    90,    91,    94,    95,    99,   100,
     101,   102,   103,   104,   106,   108,   110,   111,   112,   113,
     115,   117,   118,   119,   120,   121,   122,   123,   125,   126,
     127,   128,   130,   131,   133,   135,   136,   137,   138,   139,
     146,     9,   100,   120,    90,    90,   100,   101,    13,    90,
      97,   120,    90,   117,    92,    93,   120,   120,   120,     0,
      88,    87,    16,    92,    96,    12,    95,    97,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,   124,
     102,    28,    29,    30,   105,    31,    32,   107,    33,    34,
     109,    35,    37,    36,    39,    40,    43,    44,   114,    41,
      42,   116,    47,    69,    55,    56,    57,    14,    66,    88,
      48,    65,    97,    28,    90,   141,   142,   143,   144,   145,
      45,    46,    76,   132,    11,    45,    46,    54,   129,    87,
      96,    90,   120,    14,    92,    98,   120,   120,   102,   104,
     106,   108,   110,   111,   112,   113,   117,   118,   120,   132,
      90,    49,    62,    71,    72,    73,    75,    88,   147,   148,
     149,   150,   151,   152,   153,    90,   120,   141,    90,    17,
      11,    98,    86,   120,    86,    96,    98,   132,    86,    88,
      90,    90,   150,   151,   149,    57,    88,   151,    45,    46,
      54,   134,    98,   120,   142,    11,    46,    54,   140,    57,
      86,    57,   147,    17,    97,   151,   149,    86,   140,    86,
      57,   120,   141,    57,    86,    57,    98,    57,   140,    86,
      57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 48 "grammar.y"
    {parser_set_root((yyvsp[(1) - (1)]));;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 51 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (1)]));
		(yyval)=node;
		
	;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 59 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 66 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 74 "grammar.y"
    {
		AstNode_Add((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		(yyval)=(yyvsp[(1) - (3)]);
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 78 "grammar.y"
    {(yyval)=(yyvsp[(1) - (2)]);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 81 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 83 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 90 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 91 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 92 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 93 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 94 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 95 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 96 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 97 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 98 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 99 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 100 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 101 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 102 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 109 "grammar.y"
    {
		GrInt* gi=GrInt_GcNewFromStrFlag(yl_cur_string(),GRGC_HEAP_STATIC);
		if(gi==NULL) return AST_MEM_FAILED;
		AstObject* node=AstLiteral_New(I_TO_GR(gi));
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 117 "grammar.y"
    {
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 120 "grammar.y"
    {
		GrFloat* gf=GrFloat_GcNewFromStrFlag(yl_cur_string(),GRGC_HEAP_STATIC);
		if(gf==NULL) return AST_MEM_FAILED;
		AstObject* node=AstLiteral_New(F_TO_GR(gf));
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 128 "grammar.y"
    {
		GrString* gs=GrGc_AllocStatic(GrString,&Gr_Type_String);
		if(gs==NULL) return AST_MEM_FAILED;
		if(GrString_InitEscWithQuote(gs,yl_cur_string())<0)
			return AST_MEM_FAILED;
		
		AstObject* node=AstLiteral_New(S_TO_GR(gs));
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 139 "grammar.y"
    {
		AstObject* node=AstLiteral_New(Gr_False);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 145 "grammar.y"
    {
		AstObject* node=AstLiteral_New(Gr_True);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 152 "grammar.y"
    {
		GrString* gs=GrString_GcNewFlag(yl_cur_string(),GRGC_HEAP_STATIC);
		if(gs==NULL) return AST_MEM_FAILED;
		
		AstObject* node=AstVar_New(gs);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 162 "grammar.y"
    {
		GrString* gs=GrString_GcNewFlag(yl_cur_string(),GRGC_HEAP_STATIC);
		if(gs==NULL) return AST_MEM_FAILED;
		
		AstObject* node=AstUpperVar_New(gs);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 174 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 175 "grammar.y"
    {(yyval)=(yyvsp[(1) - (2)]);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 179 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Normal);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (1)]));
		(yyval)=node;
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 186 "grammar.y"
    {
		AstNode_Add((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		(yyval)=(yyvsp[(1) - (3)]);
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 194 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Array);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (3)]));
		(yyval)=node;
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 201 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Array);
		if(node==NULL) return AST_MEM_FAILED;
		AstObject* expr=AstNode_New(&Ast_Type_Normal);
		if(expr==NULL) return AST_MEM_FAILED;
		
		AstNode_Add(node,expr);
		(yyval)=node;
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 211 "grammar.y"
    {yl_ignore_newline();;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 212 "grammar.y"
    {yl_restore_newline();;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 213 "grammar.y"
    {yl_ignore_newline();;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 214 "grammar.y"
    {yl_restore_newline();;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 216 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 217 "grammar.y"
    {(yyval)=(yyvsp[(2) - (3)]);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 218 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 219 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 220 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 221 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 222 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 225 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 227 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Square);
		if(node==NULL) return -1;
		AstNode_Add(node,(yyvsp[(1) - (4)]));
		AstNode_Add(node,(yyvsp[(3) - (4)]));
		(yyval)=node;
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 235 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Call);
		if(node==NULL) return -1;
		AstNode_Add(node,(yyvsp[(1) - (4)]));
		AstNode_Add(node,(yyvsp[(3) - (4)]));
		(yyval)=node;
		
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 244 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Call);
		if(node==NULL) return -1;
		AstObject* expr_list=AstNode_New(&Ast_Type_Normal);
		if(expr_list==NULL) return -1;
		
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,expr_list);
		(yyval)=node;
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 255 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Period);
		if(node==NULL) return -1;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 263 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 265 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 267 "grammar.y"
    {  
		AstObject* node=AstNode_New((yyvsp[(1) - (2)]));
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 274 "grammar.y"
    {(yyval)=&Ast_Type_Positive;;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 275 "grammar.y"
    {(yyval)=&Ast_Type_Negative;;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 276 "grammar.y"
    {(yyval)=&Ast_Type_Negated;;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 279 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 281 "grammar.y"
    {
		AstObject* node=AstNode_New((yyvsp[(2) - (3)]));
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 289 "grammar.y"
    {(yyval)=&Ast_Type_Mul;;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 290 "grammar.y"
    {(yyval)=&Ast_Type_Div;;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 291 "grammar.y"
    {(yyval)=&Ast_Type_Mod;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 294 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 296 "grammar.y"
    {
		AstObject* node=AstNode_New((yyvsp[(2) - (3)]));
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 304 "grammar.y"
    {(yyval)=&Ast_Type_Plus;;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 305 "grammar.y"
    {(yyval)=&Ast_Type_Minus;;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 308 "grammar.y"
    {;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 310 "grammar.y"
    {
		AstObject* node=AstNode_New((yyvsp[(2) - (3)]));
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 318 "grammar.y"
    {(yyval)=&Ast_Type_LShift;;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 319 "grammar.y"
    {(yyval)=&Ast_Type_RShift;;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 323 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 324 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_And);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 332 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 334 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Xor);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 342 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 344 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Or);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 354 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 356 "grammar.y"
    {
		AstObject* node=AstNode_New((yyvsp[(2) - (3)]));
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 365 "grammar.y"
    {(yyval)=&Ast_Type_Lt;;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 366 "grammar.y"
    {(yyval)=&Ast_Type_Le;;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 367 "grammar.y"
    {(yyval)=&Ast_Type_Ge;;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 368 "grammar.y"
    {(yyval)=&Ast_Type_Gt;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 372 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 374 "grammar.y"
    {
		AstObject* node=AstNode_New((yyvsp[(2) - (3)]));
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 382 "grammar.y"
    {(yyval)=&Ast_Type_Eq;;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 383 "grammar.y"
    {(yyval)=&Ast_Type_Ne;;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 388 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 390 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Logic_Not);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
		
	;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 398 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 400 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Logic_And);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 408 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 410 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Logic_Or);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 419 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 422 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Expr);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (1)]));
		(yyval)=node;
	;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 431 "grammar.y"
    {
		if(!AstObject_CanAssign((yyvsp[(1) - (3)])))
		{
			yyerror("Left Can't Assign");
			return  -1;
		}
		AstObject* node=AstNode_New(&Ast_Type_Assign);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 445 "grammar.y"
    {
		if(!AstObject_CanOperAssign((yyvsp[(1) - (3)])))
		{
			yyerror("Left Can't Assign");
			return -1;
		}
		AstObject* node=AstNode_New((yyvsp[(2) - (3)]));
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 458 "grammar.y"
    {(yyval)=&Ast_Type_Mul_Assign;;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 459 "grammar.y"
    {(yyval)=&Ast_Type_Div_Assign;;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 460 "grammar.y"
    {(yyval)=&Ast_Type_Mod_Assign;;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 461 "grammar.y"
    {(yyval)=&Ast_Type_Plus_Assign;;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 462 "grammar.y"
    {(yyval)=&Ast_Type_Minus_Assign;;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 463 "grammar.y"
    {(yyval)=&Ast_Type_LShift_Assign;;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 464 "grammar.y"
    {(yyval)=&Ast_Type_RShift_Assign;;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 465 "grammar.y"
    {(yyval)=&Ast_Type_And_Assign;;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 466 "grammar.y"
    {(yyval)=&Ast_Type_Xor_Assign;;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 467 "grammar.y"
    {(yyval)=&Ast_Type_Or_Assign;;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 473 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Import);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 482 "grammar.y"
    {
 		AstObject* node=AstNode_New(&Ast_Type_Export_As);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (4)]));
		AstNode_Add(node,(yyvsp[(4) - (4)]));
		(yyval)=node;
	;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 490 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Export);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 499 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Print);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 506 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Print);
		if(node==NULL) return AST_MEM_FAILED;
		AstObject* expr_list=AstNode_New(&Ast_Type_Normal);
		if(expr_list==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,expr_list);
		(yyval)=node;
	;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 516 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_While);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (5)]));
		AstNode_Add(node,(yyvsp[(4) - (5)]));
		(yyval)=node;
	;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 527 "grammar.y"
    {(yyval)=(yyvsp[(1) - (2)]);;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 529 "grammar.y"
    {
		AstObject* sub_node=AstNode_New(&Ast_Type_Else);
		if(sub_node==NULL) return AST_MEM_FAILED;
		AstNode_Add(sub_node,(yyvsp[(4) - (5)]));
		AstNode_Add((yyvsp[(1) - (5)]),sub_node);
		(yyval)=(yyvsp[(1) - (5)]);
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 539 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_If);
		if(node==NULL) return AST_MEM_FAILED;
		AstObject* sub_node=AstNode_New(&Ast_Type_If_Elif);
		if(sub_node==NULL) return AST_MEM_FAILED;
		AstNode_Add(sub_node,(yyvsp[(2) - (4)]));
		AstNode_Add(sub_node,(yyvsp[(4) - (4)]));
		AstNode_Add(node,sub_node);
		(yyval)=node;
	;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 550 "grammar.y"
    {
		AstObject* sub_node=AstNode_New(&Ast_Type_If_Elif);
		if(sub_node==NULL) return AST_MEM_FAILED;
		AstNode_Add(sub_node,(yyvsp[(3) - (5)]));
		AstNode_Add(sub_node,(yyvsp[(5) - (5)]));
		AstNode_Add((yyvsp[(1) - (5)]),sub_node);
		(yyval)=(yyvsp[(1) - (5)]);
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 564 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_For);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (7)]));
		AstNode_Add(node,(yyvsp[(4) - (7)]));
		AstNode_Add(node,(yyvsp[(6) - (7)]));		
		(yyval)=node;
	;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 575 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Break);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 582 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Continue);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 589 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Return);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 596 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Return);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 607 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Func);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (8)]));
		AstNode_Add(node,(yyvsp[(4) - (8)]));
		AstNode_Add(node,(yyvsp[(7) - (8)]));
		(yyval)=node;
	;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 617 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Func);
		if(node==NULL) return AST_MEM_FAILED;
		AstObject* name=AstVar_New(GR_TO_S(Gr_Const_String_lambda));
		if(name==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,name);
		AstNode_Add(node,(yyvsp[(3) - (7)]));
		AstNode_Add(node,(yyvsp[(6) - (7)]));
		(yyval)=node;
	;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 632 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Normal);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (1)]));
		(yyval)=node;
	;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 639 "grammar.y"
    {
		AstNode_Add((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		(yyval)=(yyvsp[(1) - (3)]);
	;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 644 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Normal);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 651 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 652 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 653 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 657 "grammar.y"
    {
		AstObject* node=AstArg_New(ARG_SIMPLY,((AstVar*)((yyvsp[(1) - (1)])))->v_value);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 664 "grammar.y"
    {
		AstObject* node=AstArg_New(ARG_DEFAULT_VALUE,((AstVar*)((yyvsp[(1) - (3)])))->v_value);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(3) - (3)]));
		(yyval)=node;
	;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 673 "grammar.y"
    {
		AstObject* node=AstArg_New(ARG_MANY,((AstVar*)((yyvsp[(2) - (2)])))->v_value);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 682 "grammar.y"
    {
		AstObject* node=AstClass_New((yyvsp[(4) - (7)]));
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (7)]));
		AstNode_Add(node,(yyvsp[(6) - (7)]));
		(yyval)=node;
	;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 690 "grammar.y"
    {
		AstObject* node=AstClass_New(NULL);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (5)]));
		AstNode_Add(node,(yyvsp[(4) - (5)]));
		(yyval)=node;
	;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 699 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 701 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 710 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(1) - (1)]));
		(yyval)=node;
	;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 718 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		(yyval)=node;
	;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 724 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Stmts);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 731 "grammar.y"
    {
		AstNode_Add((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		(yyval)=(yyvsp[(1) - (3)]);
	;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 735 "grammar.y"
    {(yyval)=(yyvsp[(1) - (2)]);;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 739 "grammar.y"
    {
		AstObject* node=AstClassStmt_New();

		if(node==NULL) return AST_MEM_FAILED;

		AstClassStmt_SetFlag(AST_TO_CLASS_STMT(node),GR_CLASS_PROTECTED);
		AstNode_Add(node,(yyvsp[(1) - (1)]));
		(yyval)=node;
	;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 749 "grammar.y"
    {
		AstObject* node=AstClassStmt_New();
		if(node==NULL) return AST_MEM_FAILED;

		AstClassStmt_SetFlag(AST_TO_CLASS_STMT(node),(long)(yyvsp[(1) - (2)]));
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 759 "grammar.y"
    {
		AstObject* node=AstClassStmt_New();
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		AstClassStmt_SetFlag(AST_TO_CLASS_STMT(node),GR_CLASS_STATIC);
		AstClassStmt_SetFlag(AST_TO_CLASS_STMT(node),GR_CLASS_PROTECTED);
		(yyval)=node;
	;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 768 "grammar.y"
    {
		AstObject* node=AstClassStmt_New();
		if(node==NULL) return AST_MEM_FAILED;

		AstClassStmt_SetFlag(AST_TO_CLASS_STMT(node),GR_CLASS_STATIC);
		AstClassStmt_SetFlag(AST_TO_CLASS_STMT(node),(long)(yyvsp[(1) - (3)]));
		AstNode_Add(node,(yyvsp[(2) - (3)]));
		(yyval)=node;
	;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 778 "grammar.y"
    {(yyval)=(void*)GR_CLASS_PUBLIC;;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 779 "grammar.y"
    {(yyval)=(void*)GR_CLASS_PROTECTED;;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 780 "grammar.y"
    {(yyval)=(void*)GR_CLASS_PRIVATE;;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 783 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 784 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 788 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Attr);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (2)]));
		(yyval)=node;
	;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 796 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Attr_Default);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (4)]));
		AstNode_Add(node,(yyvsp[(4) - (4)]));
		(yyval)=node;
	;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 805 "grammar.y"
    {
		AstObject* node=AstNode_New(&Ast_Type_Method);
		if(node==NULL) return AST_MEM_FAILED;
		AstNode_Add(node,(yyvsp[(2) - (8)]));
		AstNode_Add(node,(yyvsp[(4) - (8)]));
		AstNode_Add(node,(yyvsp[(7) - (8)]));
		(yyval)=node;
	;}
    break;



/* Line 1455 of yacc.c  */
#line 3212 "grammar.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



