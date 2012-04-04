
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
#include<rtype/rtype.h>
#include<rtype/bt_string.h>
#include<rtype/bt_int.c>
#include<rtype/bt_float.h>
#include<rtype/bt_long.h>
#define YYSTYPE  AstObject* 


/* Line 189 of yacc.c  */
#line 87 "grammar.tab.c"

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
     tCOMMA = 265,
     tPERIOD = 266,
     tL_RB = 267,
     tR_RB = 268,
     tL_SB = 269,
     tR_SB = 270,
     tASSIGN = 271,
     tAMUL = 272,
     tADIV = 273,
     tAMOD = 274,
     tAPLUS = 275,
     tAMINUS = 276,
     tALS = 277,
     tARS = 278,
     tAAND = 279,
     tAOR = 280,
     tAXOR = 281,
     tMUL = 282,
     tDIV = 283,
     tMOD = 284,
     tPLUS = 285,
     tMINUS = 286,
     tLS = 287,
     tRS = 288,
     tAND = 289,
     tOR = 290,
     tXOR = 291,
     tNegated = 292,
     tLT = 293,
     tLE = 294,
     tNE = 295,
     tEQ = 296,
     tGE = 297,
     tGT = 298,
     tSEMI = 299,
     tNEWLINE = 300,
     kAND = 301,
     kAS = 302,
     kAttr = 303,
     kBREAK = 304,
     kCATCH = 305,
     kCLASS = 306,
     kCONTINUE = 307,
     kDO = 308,
     kELIF = 309,
     kELSE = 310,
     kEND = 311,
     kFINALLY = 312,
     kFOR = 313,
     kFROM = 314,
     kFUNC = 315,
     kIF = 316,
     kIMPORT = 317,
     kIN = 318,
     kINHRIT = 319,
     kNOT = 320,
     kOR = 321,
     kPRINT = 322,
     kRETURN = 323,
     kTHEN = 324,
     kTO = 325,
     KTRY = 326,
     kVFUNC = 327,
     kWHILE = 328,
     kTRUE = 329,
     kFALSE = 330
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
#line 204 "grammar.tab.c"

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
#define YYFINAL  57
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   120

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNRULES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   330

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
      75
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    13,    15,    18,
      20,    22,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    49,    51,    53,    55,    59,    61,
      63,    66,    69,    72,    74,    78,    82,    86,    88,    92,
      96,    98,   102,   106,   108,   112,   114,   118,   120,   124,
     126,   130,   134,   138,   142,   144,   148,   152,   154,   157,
     159,   163,   165,   169,   171,   173,   177,   180,   186,   188,
     190,   192,   195,   199,   201,   204,   209,   214,   218,   220,
     222
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      77,     0,    -1,    78,    -1,    79,    -1,    79,    83,    -1,
      83,    -1,    -1,    81,    -1,    79,    81,    -1,    45,    -1,
      44,    -1,    83,    80,    -1,    82,    -1,    80,    -1,   100,
      -1,   101,    -1,   102,    -1,   103,    -1,   105,    -1,     5,
      -1,     6,    -1,     7,    -1,     8,    -1,    75,    -1,    74,
      -1,     9,    -1,    84,    -1,    12,    99,    13,    -1,    85,
      -1,    86,    -1,    30,    87,    -1,    31,    87,    -1,    37,
      87,    -1,    87,    -1,    88,    27,    87,    -1,    88,    28,
      87,    -1,    88,    29,    87,    -1,    88,    -1,    89,    30,
      88,    -1,    89,    31,    88,    -1,    89,    -1,    90,    32,
      89,    -1,    90,    33,    89,    -1,    90,    -1,    91,    34,
      90,    -1,    91,    -1,    92,    36,    91,    -1,    92,    -1,
      93,    35,    92,    -1,    93,    -1,    94,    38,    93,    -1,
      94,    39,    93,    -1,    94,    42,    93,    -1,    94,    43,
      93,    -1,    94,    -1,    95,    41,    94,    -1,    95,    40,
      94,    -1,    95,    -1,    65,    96,    -1,    96,    -1,    97,
      46,    96,    -1,    97,    -1,    98,    66,    97,    -1,    98,
      -1,    99,    -1,    85,    16,    99,    -1,    67,    99,    -1,
      73,    99,   104,    78,    56,    -1,    45,    -1,    53,    -1,
      44,    -1,   106,    56,    -1,   106,   109,    56,    -1,   107,
      -1,   106,   108,    -1,    61,    99,   110,    78,    -1,    54,
      99,   110,    78,    -1,    55,   110,    78,    -1,    45,    -1,
      69,    -1,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    38,    38,    40,    41,    49,    58,    65,    76,    89,
      89,    92,    93,    95,    97,   103,   109,   115,   121,   129,
     138,   147,   155,   163,   171,   180,   190,   191,   192,   195,
     196,   203,   210,   219,   222,   228,   234,   241,   242,   248,
     255,   256,   262,   270,   271,   278,   279,   286,   287,   295,
     296,   302,   308,   314,   322,   323,   329,   336,   337,   344,
     345,   352,   353,   360,   364,   367,   375,   382,   389,   390,
     391,   395,   396,   403,   410,   416,   423,   430,   438,   438,
     438
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tUNKOWN", "tERR", "tINTEGER", "tLONG",
  "tFLAOT", "tSTRING", "tID", "tCOMMA", "tPERIOD", "tL_RB", "tR_RB",
  "tL_SB", "tR_SB", "tASSIGN", "tAMUL", "tADIV", "tAMOD", "tAPLUS",
  "tAMINUS", "tALS", "tARS", "tAAND", "tAOR", "tAXOR", "tMUL", "tDIV",
  "tMOD", "tPLUS", "tMINUS", "tLS", "tRS", "tAND", "tOR", "tXOR",
  "tNegated", "tLT", "tLE", "tNE", "tEQ", "tGE", "tGT", "tSEMI",
  "tNEWLINE", "kAND", "kAS", "kAttr", "kBREAK", "kCATCH", "kCLASS",
  "kCONTINUE", "kDO", "kELIF", "kELSE", "kEND", "kFINALLY", "kFOR",
  "kFROM", "kFUNC", "kIF", "kIMPORT", "kIN", "kINHRIT", "kNOT", "kOR",
  "kPRINT", "kRETURN", "kTHEN", "kTO", "KTRY", "kVFUNC", "kWHILE", "kTRUE",
  "kFALSE", "$accept", "AstTree", "pretty_stmts", "stmts",
  "stmt_delimiter", "pretty_stmt", "pseudo_stmt", "stmt", "literal",
  "identifier", "primary_expr", "unary_expr", "multiply_expr",
  "additive_expr", "shift_expr", "bit_and_expr", "bit_xor_expr",
  "bit_or_expr", "relational_expr", "equal_expr", "logic_not_expr",
  "logic_and_expr", "logic_or_expr", "expr", "stmt_expr", "stmt_assign",
  "stmt_print", "stmt_while", "while_delimter", "stmt_if", "if_pre",
  "if_part", "elif_part", "else_part", "if_delimter", 0
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
     325,   326,   327,   328,   329,   330
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    81,    82,    83,    83,    83,    83,    83,    84,
      84,    84,    84,    84,    84,    85,    86,    86,    86,    87,
      87,    87,    87,    88,    88,    88,    88,    89,    89,    89,
      90,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    94,    94,    94,    95,    95,    95,    96,    96,    97,
      97,    98,    98,    99,   100,   101,   102,   103,   104,   104,
     104,   105,   105,   106,   106,   107,   108,   109,   110,   110,
     110
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     0,     1,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       2,     2,     2,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     2,     1,
       3,     1,     3,     1,     1,     3,     2,     5,     1,     1,
       1,     2,     3,     1,     2,     4,     4,     3,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,    19,    20,    21,    22,    25,     0,     0,     0,     0,
      10,     9,     0,     0,     0,     0,    24,    23,     0,     2,
       3,    13,     7,    12,     5,    26,    28,    29,    33,    37,
      40,    43,    45,    47,    49,    54,    57,    59,    61,    63,
      64,    14,    15,    16,    17,    18,     0,    73,    28,     0,
      30,    31,    32,     0,    58,    66,     0,     1,     8,     4,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,    74,     0,    27,    80,    78,    79,     6,
      70,    68,    69,     6,    65,    34,    35,    36,    38,    39,
      41,    42,    44,    46,    48,    50,    51,    52,    53,    56,
      55,    60,    62,     0,     6,    72,    75,     0,     6,    77,
      67,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    48,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    93,    45,
      46,    47,    83,    84,    89
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -80
static const yytype_int8 yypact[] =
{
       6,   -80,   -80,   -80,   -80,   -80,    17,    33,    33,    33,
     -80,   -80,    17,    17,    17,    17,   -80,   -80,     8,   -80,
       6,   -80,   -80,   -80,    41,   -80,     3,   -80,   -80,    49,
      71,    72,   -18,   -15,    -8,    45,    69,   -80,   -13,   -31,
     -80,   -80,   -80,   -80,   -80,   -80,    44,   -80,   -80,    31,
     -80,   -80,   -80,   -14,   -80,   -80,    21,   -80,   -80,    41,
     -80,    17,    33,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    17,    17,
      17,   -14,   -80,   -80,     2,   -80,   -80,   -80,   -80,     6,
     -80,   -80,   -80,     6,   -80,   -80,   -80,   -80,    49,    49,
      71,    71,    72,   -18,   -15,    -8,    -8,    -8,    -8,    45,
      45,   -80,   -13,   -14,     6,   -80,   -80,    13,     6,   -80,
     -80,   -80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -80,   -80,   -61,   -80,    -7,    26,   -80,    29,   -80,     0,
     -80,    -3,    46,    48,    34,    20,    -9,    22,    43,   -80,
     -10,    27,   -80,    -5,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -79
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      26,    49,   114,    54,    50,    51,    52,    53,    57,    55,
      56,     1,     2,     3,     4,     5,    69,    60,     6,    61,
      26,    70,     1,     2,     3,     4,     5,    71,   116,     6,
      86,    87,   117,    78,   118,    79,     7,     8,     1,     2,
       3,     4,     5,     9,    85,     6,    58,     7,     8,    59,
      10,    11,    60,   119,     9,    88,    94,   121,   115,    95,
      96,    97,   104,     7,     8,    90,    91,    12,   111,   120,
       9,    13,     0,    14,    92,   113,    62,    63,    64,    15,
      16,    17,    13,    72,    73,    10,    11,    74,    75,    26,
     103,    16,    17,    26,   105,   106,   107,   108,    80,    81,
      82,    65,    66,   102,    67,    68,   112,    16,    17,    76,
      77,    98,    99,     0,    26,   100,   101,     0,    26,   109,
     110
};

static const yytype_int8 yycheck[] =
{
       0,     6,    81,    13,     7,     8,     9,    12,     0,    14,
      15,     5,     6,     7,     8,     9,    34,    24,    12,    16,
      20,    36,     5,     6,     7,     8,     9,    35,    89,    12,
      44,    45,    93,    46,   113,    66,    30,    31,     5,     6,
       7,     8,     9,    37,    13,    12,    20,    30,    31,    20,
      44,    45,    59,   114,    37,    69,    61,   118,    56,    62,
      63,    64,    71,    30,    31,    44,    45,    61,    78,    56,
      37,    65,    -1,    67,    53,    80,    27,    28,    29,    73,
      74,    75,    65,    38,    39,    44,    45,    42,    43,    89,
      70,    74,    75,    93,    72,    73,    74,    75,    54,    55,
      56,    30,    31,    69,    32,    33,    79,    74,    75,    40,
      41,    65,    66,    -1,   114,    67,    68,    -1,   118,    76,
      77
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,     8,     9,    12,    30,    31,    37,
      44,    45,    61,    65,    67,    73,    74,    75,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   105,   106,   107,    85,    99,
      87,    87,    87,    99,    96,    99,    99,     0,    81,    83,
      80,    16,    27,    28,    29,    30,    31,    32,    33,    34,
      36,    35,    38,    39,    42,    43,    40,    41,    46,    66,
      54,    55,    56,   108,   109,    13,    44,    45,    69,   110,
      44,    45,    53,   104,    99,    87,    87,    87,    88,    88,
      89,    89,    90,    91,    92,    93,    93,    93,    93,    94,
      94,    96,    97,    99,   110,    56,    78,    78,   110,    78,
      56,    78
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
#line 38 "grammar.y"
    {parser_set_root((yyvsp[(1) - (1)]));;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 40 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 42 "grammar.y"
    {
		AstNodeStmts* stmts=AST_TO_STMTS((yyvsp[(1) - (2)]));
		assert((yyvsp[(2) - (2)]));
		AstNodeStmt* node=AST_TO_STMT((yyvsp[(2) - (2)]));
		ast_stmts_add(stmts,node);
		(yyval)=STMTS_TO_AST(stmts);
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 50 "grammar.y"
    {
		AstNodeStmts* stmts=ast_create_stmts();
		ast_addto_pending(STMTS_TO_AST(stmts));
		AstNodeStmt* node=AST_TO_STMT((yyvsp[(1) - (1)]));
		ast_stmts_add(stmts,node);
		(yyval)=STMTS_TO_AST(stmts);
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 58 "grammar.y"
    {
		AstNodeStmts* stmts=ast_create_stmts();
		ast_addto_pending(STMTS_TO_AST(stmts));
		(yyval)=STMTS_TO_AST(stmts);
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 66 "grammar.y"
    {
		AstNodeStmts* stmts=ast_create_stmts();
		ast_addto_pending(STMTS_TO_AST(stmts));
		if((yyvsp[(1) - (1)])!=NULL)
		{
			AstNodeStmt* node=AST_TO_STMT((yyvsp[(1) - (1)]));
			ast_stmts_add(stmts,node);
		}
		(yyval)=STMTS_TO_AST(stmts);
	 ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 77 "grammar.y"
    {
		AstNodeStmts* stmts=AST_TO_STMTS((yyvsp[(1) - (2)]));
		if((yyvsp[(2) - (2)])!=NULL)
		{
			AstNodeStmt* node=AST_TO_STMT((yyvsp[(2) - (2)]));
			ast_stmts_add(stmts,node);
		}
		(yyval)=STMTS_TO_AST(stmts);
		
	 ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 92 "grammar.y"
    {(yyval)=(yyvsp[(1) - (2)]);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 93 "grammar.y"
    {(yyval)=NULL;;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 95 "grammar.y"
    {(yyval)=NULL;;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 98 "grammar.y"
    {
		AstNodeStmt* node=ast_create_stmt((yyvsp[(1) - (1)]));
		ast_addto_pending(STMT_TO_AST(node));
		(yyval)=STMT_TO_AST(node);
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 104 "grammar.y"
    {
		AstNodeStmt* node=ast_create_stmt((yyvsp[(1) - (1)]));
		ast_addto_pending(STMT_TO_AST(node));
		(yyval)=STMT_TO_AST(node);
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 110 "grammar.y"
    { 
		AstNodeStmt* node=ast_create_stmt((yyvsp[(1) - (1)]));
		ast_addto_pending(STMT_TO_AST(node));
		(yyval)=STMT_TO_AST(node);
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 116 "grammar.y"
    {
		AstNodeStmt* node=ast_create_stmt((yyvsp[(1) - (1)]));
		ast_addto_pending(STMT_TO_AST(node));
		(yyval)=STMT_TO_AST(node);
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 122 "grammar.y"
    {
		AstNodeStmt* node=ast_create_stmt((yyvsp[(1) - (1)]));
		ast_addto_pending(STMT_TO_AST(node));
		(yyval)=STMT_TO_AST(node);
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 130 "grammar.y"
    {
		BtInt* bi=btint_from_str(yl_cur_string());
		AstNodeLiteral* t=ast_create_literal(I_TO_R(bi));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(I_TO_R(bi));
		(yyval)=LITERAL_TO_AST(t); 
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 139 "grammar.y"
    {
		BtLong* bl=btlong_from_str(yl_cur_string());
		AstNodeLiteral* t=ast_create_literal(L_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(L_TO_R(bl));
		(yyval)=LITERAL_TO_AST(t);
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 148 "grammar.y"
    {
		BtFloat* bf=btfloat_from_str(yl_cur_string());
		AstNodeLiteral* t=ast_create_literal(F_TO_R(bf));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(F_TO_R(bf));
		(yyval)=LITERAL_TO_AST(t);
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 156 "grammar.y"
    {
		BtString* bs=btstring_create(yl_cur_string());
		AstNodeLiteral* t=ast_create_literal(S_TO_R(bs));
		ast_addto_pending(LITERAL_TO_AST(t));
		robject_release(S_TO_R(bs));
		(yyval)=LITERAL_TO_AST(t);
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 164 "grammar.y"
    {
		BtBool* bl=btbool_create(0);
		AstNodeLiteral* node=ast_create_literal(B_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(node));
		robject_release(B_TO_R(bl));
		(yyval)=LITERAL_TO_AST(node);
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 172 "grammar.y"
    {
		BtBool* bl=btbool_create(1);
		AstNodeLiteral* node=ast_create_literal(B_TO_R(bl));
		ast_addto_pending(LITERAL_TO_AST(node));
		robject_release(B_TO_R(bl));
		(yyval)=LITERAL_TO_AST(node);
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 181 "grammar.y"
    {
		BtString* bs=btstring_create_no_esc(yl_cur_string());
		AstNodeVar* node=ast_create_var(bs);
		ast_addto_pending(VAR_TO_AST(node));
		robject_release(S_TO_R(bs));
		(yyval)=VAR_TO_AST(node);
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 190 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 191 "grammar.y"
    {(yyval)=(yyvsp[(2) - (3)]);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 192 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 195 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 197 "grammar.y"
    {  
		AstNodePositive* node=ast_create_positive((yyvsp[(2) - (2)]));
		AstObject* ab=POSITIVE_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 204 "grammar.y"
    { 
		AstNodeNegative* node=ast_create_negative((yyvsp[(2) - (2)]));
		AstObject* ab=NEGATIVE_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 211 "grammar.y"
    {  
		AstNodeNegated* node=ast_create_negated((yyvsp[(2) - (2)]));
		AstObject* ab=NEGATED_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 219 "grammar.y"
    {
			 (yyval)=(yyvsp[(1) - (1)]);
			;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 222 "grammar.y"
    {
			AstNodeMul* t=ast_create_mul((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
			AstObject* ab=MUL_TO_AST(t);
			ast_addto_pending(ab);
			(yyval)=ab;
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 228 "grammar.y"
    {
			AstNodeDiv* t=ast_create_div((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
			AstObject* ab=DIV_TO_AST(t);
			ast_addto_pending(ab);
			(yyval)=ab;
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 234 "grammar.y"
    {
			AstNodeDiv* t=ast_create_mod((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
			AstObject* ab=MOD_TO_AST(t);
			ast_addto_pending(ab);
			(yyval)=ab;
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 241 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 242 "grammar.y"
    {
		AstNodePlus* node=ast_create_plus((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=PLUS_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 248 "grammar.y"
    {
		AstNodeMinus* node=ast_create_minus((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=MINUS_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 255 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 256 "grammar.y"
    {   /*left shift*/
		AstNodeLShift* node=ast_create_lshift((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=LSHIFT_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 262 "grammar.y"
    {  /* right shift */
		AstNodeRShift* node=ast_create_rshift((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=RSHIFT_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 270 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 271 "grammar.y"
    {
		AstNodeAnd* node=ast_create_and((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=AND_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 278 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 279 "grammar.y"
    {
		AstNodeXor* node=ast_create_xor((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=XOR_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 286 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 287 "grammar.y"
    {
		AstNodeOr* node=ast_create_or((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=OR_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 295 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 296 "grammar.y"
    {
		AstNodeLt* node =ast_create_lt((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=LT_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 302 "grammar.y"
    {
		AstNodeLe* node=ast_create_le((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=LE_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 308 "grammar.y"
    {
		AstNodeGe* node=ast_create_ge((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=GE_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 314 "grammar.y"
    {
		AstNodeGt* node=ast_create_gt((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=GT_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 322 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 323 "grammar.y"
    {
		AstNodeEq* node=ast_create_eq((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=EQ_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 329 "grammar.y"
    {
		AstNodeNe* node=ast_create_ne((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=NE_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 336 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 337 "grammar.y"
    {
		AstNodeLogicNot* node=ast_create_logic_not((yyvsp[(2) - (2)]));
		AstObject* ab=LOGIC_NOT_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 344 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 345 "grammar.y"
    {
		AstNodeLogicAnd* node=ast_create_logic_and((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=LOGIC_AND_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 352 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 353 "grammar.y"
    {
		AstNodeLogicOr* node=ast_create_logic_or((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]));
		AstObject* ab=LOGIC_OR_TO_AST(node);
		ast_addto_pending(ab);
		(yyval)=ab;
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 360 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 364 "grammar.y"
    {(yyval)=(yyvsp[(1) - (1)]);;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 368 "grammar.y"
    {
		AstNodeAssign* node=ast_create_assign(AST_TO_VAR((yyvsp[(1) - (3)])),(yyvsp[(3) - (3)]));
		ast_addto_pending(ASSIGN_TO_AST(node));
		(yyval)=ASSIGN_TO_AST(node);
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 376 "grammar.y"
    {
		AstNodePrint* node=ast_create_print((yyvsp[(2) - (2)]));
		ast_addto_pending(PRINT_TO_AST(node));
		(yyval)=PRINT_TO_AST(node);
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 383 "grammar.y"
    {
		AstNodeWhile* node=ast_create_while((yyvsp[(2) - (5)]),(yyvsp[(4) - (5)]));
		ast_addto_pending(WHILE_TO_AST(node));
		(yyval)=WHILE_TO_AST(node);
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 395 "grammar.y"
    {(yyval)=(yyvsp[(1) - (2)]);;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 397 "grammar.y"
    {
		ast_if_add(AST_TO_IF((yyvsp[(1) - (3)])),AST_TO_IF_SUB((yyvsp[(2) - (3)])));
		(yyval)=(yyvsp[(1) - (3)]);
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 404 "grammar.y"
    {
		AstNodeIf* node=ast_create_if();
		ast_addto_pending(IF_TO_AST(node));
		ast_if_add(node,AST_TO_IF_SUB((yyvsp[(1) - (1)])));
		(yyval)=IF_TO_AST(node);
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 411 "grammar.y"
    {
		ast_if_add(AST_TO_IF((yyvsp[(1) - (2)])),AST_TO_IF_SUB((yyvsp[(2) - (2)])));
		(yyval)=(yyvsp[(1) - (2)]);
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 417 "grammar.y"
    {
		AstNodeIfSub* node=ast_create_if_sub((yyvsp[(2) - (4)]),(yyvsp[(4) - (4)]));
		ast_addto_pending(IF_SUB_TO_AST(node));
		(yyval)=IF_SUB_TO_AST(node);
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 424 "grammar.y"
    {
		AstNodeIfSub* node=ast_create_if_sub((yyvsp[(2) - (4)]),(yyvsp[(4) - (4)]));
		ast_addto_pending(IF_SUB_TO_AST(node));
		(yyval)=IF_SUB_TO_AST(node);
	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 431 "grammar.y"
    {
		AstNodeIfSub* node=ast_create_if_sub(NULL,(yyvsp[(3) - (3)]));
		ast_addto_pending(IF_SUB_TO_AST(node));
		(yyval)=IF_SUB_TO_AST(node);
	;}
    break;



/* Line 1455 of yacc.c  */
#line 2272 "grammar.tab.c"
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



