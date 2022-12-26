/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src\\parser\\parser.ypp"

    #include <stdio.h>
    #include <iostream>
    #include <fstream>
    #include <string>

    #include "../CodeGenerator.h"
    #include "../Memory.h"
    #include "../Variable.h"

    extern FILE* yyin;

    CodeGenerator* codeGenerator;
    Memory* memory;

    int yylex(void);
    void yyerror(std::string error);
    

#line 91 "src\\parser\\parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROCEDURE = 3,                  /* PROCEDURE  */
  YYSYMBOL_PROGRAM = 4,                    /* PROGRAM  */
  YYSYMBOL_IS = 5,                         /* IS  */
  YYSYMBOL_VAR = 6,                        /* VAR  */
  YYSYMBOL__BEGIN = 7,                     /* _BEGIN  */
  YYSYMBOL_END = 8,                        /* END  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_THEN = 10,                      /* THEN  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_ENDIF = 12,                     /* ENDIF  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_ENDWHILE = 15,                  /* ENDWHILE  */
  YYSYMBOL_REPEAT = 16,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 17,                     /* UNTIL  */
  YYSYMBOL_READ = 18,                      /* READ  */
  YYSYMBOL_WRITE = 19,                     /* WRITE  */
  YYSYMBOL_NUM = 20,                       /* NUM  */
  YYSYMBOL_IDENTIFIER = 21,                /* IDENTIFIER  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 23,                 /* SEMICOLON  */
  YYSYMBOL_LB = 24,                        /* LB  */
  YYSYMBOL_RB = 25,                        /* RB  */
  YYSYMBOL_ASSIGN = 26,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_MINUS = 28,                     /* MINUS  */
  YYSYMBOL_MUL = 29,                       /* MUL  */
  YYSYMBOL_DIV = 30,                       /* DIV  */
  YYSYMBOL_MOD = 31,                       /* MOD  */
  YYSYMBOL_EQ = 32,                        /* EQ  */
  YYSYMBOL_NEQ = 33,                       /* NEQ  */
  YYSYMBOL_GREATER = 34,                   /* GREATER  */
  YYSYMBOL_LESS = 35,                      /* LESS  */
  YYSYMBOL_GREQ = 36,                      /* GREQ  */
  YYSYMBOL_LEQ = 37,                       /* LEQ  */
  YYSYMBOL_TEST = 38,                      /* TEST  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_program_all = 40,               /* program_all  */
  YYSYMBOL_procedures = 41,                /* procedures  */
  YYSYMBOL_procedure = 42,                 /* procedure  */
  YYSYMBOL_main = 43,                      /* main  */
  YYSYMBOL_commands = 44,                  /* commands  */
  YYSYMBOL_command = 45,                   /* command  */
  YYSYMBOL_execute_proc_head = 46,         /* execute_proc_head  */
  YYSYMBOL_execute_proc_head_declarations = 47, /* execute_proc_head_declarations  */
  YYSYMBOL_execute_proc_head_declaration = 48, /* execute_proc_head_declaration  */
  YYSYMBOL_proc_head = 49,                 /* proc_head  */
  YYSYMBOL_proc_head_declarations = 50,    /* proc_head_declarations  */
  YYSYMBOL_proc_head_declaration = 51,     /* proc_head_declaration  */
  YYSYMBOL_declarations = 52,              /* declarations  */
  YYSYMBOL_declaration = 53,               /* declaration  */
  YYSYMBOL_expression = 54,                /* expression  */
  YYSYMBOL_condition = 55,                 /* condition  */
  YYSYMBOL_value = 56                      /* value  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   165

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  104

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    52,    52,    55,    56,    57,    60,    62,    66,    67,
      70,    71,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    85,    88,    89,    92,    95,    97,    98,    99,   102,
     105,   106,   109,   112,   113,   114,   115,   116,   117,   120,
     121,   122,   123,   124,   125,   128,   129
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROCEDURE", "PROGRAM",
  "IS", "VAR", "_BEGIN", "END", "IF", "THEN", "ELSE", "ENDIF", "WHILE",
  "DO", "ENDWHILE", "REPEAT", "UNTIL", "READ", "WRITE", "NUM",
  "IDENTIFIER", "COMMA", "SEMICOLON", "LB", "RB", "ASSIGN", "PLUS",
  "MINUS", "MUL", "DIV", "MOD", "EQ", "NEQ", "GREATER", "LESS", "GREQ",
  "LEQ", "TEST", "$accept", "program_all", "procedures", "procedure",
  "main", "commands", "command", "execute_proc_head",
  "execute_proc_head_declarations", "execute_proc_head_declaration",
  "proc_head", "proc_head_declarations", "proc_head_declaration",
  "declarations", "declaration", "expression", "condition", "value", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-31)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      19,   -17,    27,    55,   -31,    10,    34,   -31,    37,   -31,
     -31,    40,     9,    76,   -31,     1,   -31,    40,   144,    43,
     144,    40,   -31,    -4,    66,    66,   144,    50,    66,    30,
      44,   -31,   -31,   -31,    -2,   -31,    72,   -31,   144,   -31,
     -31,    45,   -24,    60,    12,    61,    69,    68,    66,   -31,
     -31,   144,    43,   -31,    86,   144,    66,    66,    66,    66,
      66,    66,   144,    66,   -31,   -31,   -31,    13,   -31,    73,
      39,   100,   -31,   -31,   111,   -31,   -31,   -31,   -31,   -31,
     -31,   122,    74,    68,   -31,   -31,    66,    66,    66,    66,
      66,   -31,   144,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   133,   -31
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     0,     5,     0,     0,     1,     0,     4,
       2,    26,     0,     0,    29,     0,    28,    26,    12,     0,
      12,     0,    25,     0,     0,     0,    12,     0,     0,     0,
       0,    11,    18,    32,     0,    31,     0,    27,    12,    45,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     7,
      10,    12,     0,     9,     0,    12,     0,     0,     0,     0,
       0,     0,    12,     0,    19,    20,    24,     0,    23,     0,
      33,     0,    30,     6,     0,    39,    40,    41,    42,    43,
      44,     0,     0,     0,    21,    13,     0,     0,     0,     0,
       0,     8,    12,    15,    16,    17,    22,    34,    35,    36,
      37,    38,     0,    14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,   -31,   -31,    95,   -31,   -19,   -30,   -31,   -31,    17,
     -31,    84,    82,   -31,    54,   -31,   -23,   -11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    10,    30,    31,    32,    67,    68,
       6,    15,    16,    34,    35,    69,    41,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      50,    36,    43,    38,     5,    51,    50,    44,    56,    57,
      58,    59,    60,    61,    50,    17,    18,    46,    21,    54,
      52,    24,     1,    21,    50,    25,    22,     7,    26,    63,
      27,    28,    71,    29,    11,    83,    74,    70,    84,    12,
      82,    50,    13,    81,    50,    75,    76,    77,    78,    79,
      80,    50,    49,    24,    47,    55,    48,    25,     1,     8,
      26,    14,    27,    28,    33,    29,    86,    87,    88,    89,
      90,    45,    50,   102,    62,    97,    98,    99,   100,   101,
      53,    24,    19,    20,    64,    25,    39,    40,    26,    66,
      27,    28,    65,    29,    73,    24,    85,    95,     9,    25,
      96,    23,    26,    37,    27,    28,    72,    29,    91,    24,
       0,     0,     0,    25,     0,     0,    26,     0,    27,    28,
      24,    29,    92,    93,    25,     0,     0,    26,     0,    27,
      28,    24,    29,     0,     0,    25,     0,    94,    26,     0,
      27,    28,    24,    29,     0,   103,    25,     0,     0,    26,
       0,    27,    28,    24,    29,     0,     0,    25,     0,     0,
      26,     0,    27,    28,     0,    29
};

static const yytype_int8 yycheck[] =
{
      30,    20,    25,     7,    21,     7,    36,    26,    32,    33,
      34,    35,    36,    37,    44,     6,     7,    28,    22,    38,
      22,     9,     3,    22,    54,    13,    25,     0,    16,    17,
      18,    19,    51,    21,    24,    22,    55,    48,    25,     5,
      63,    71,     5,    62,    74,    56,    57,    58,    59,    60,
      61,    81,     8,     9,    24,    10,    26,    13,     3,     4,
      16,    21,    18,    19,    21,    21,    27,    28,    29,    30,
      31,    21,   102,    92,    14,    86,    87,    88,    89,    90,
       8,     9,     6,     7,    23,    13,    20,    21,    16,    21,
      18,    19,    23,    21,     8,     9,    23,    23,     3,    13,
      83,    17,    16,    21,    18,    19,    52,    21,     8,     9,
      -1,    -1,    -1,    13,    -1,    -1,    16,    -1,    18,    19,
       9,    21,    11,    12,    13,    -1,    -1,    16,    -1,    18,
      19,     9,    21,    -1,    -1,    13,    -1,    15,    16,    -1,
      18,    19,     9,    21,    -1,    12,    13,    -1,    -1,    16,
      -1,    18,    19,     9,    21,    -1,    -1,    13,    -1,    -1,
      16,    -1,    18,    19,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    40,    41,    42,    21,    49,     0,     4,    42,
      43,    24,     5,     5,    21,    50,    51,     6,     7,     6,
       7,    22,    25,    50,     9,    13,    16,    18,    19,    21,
      44,    45,    46,    21,    52,    53,    44,    51,     7,    20,
      21,    55,    56,    55,    44,    21,    56,    24,    26,     8,
      45,     7,    22,     8,    44,    10,    32,    33,    34,    35,
      36,    37,    14,    17,    23,    23,    21,    47,    48,    54,
      56,    44,    53,     8,    44,    56,    56,    56,    56,    56,
      56,    44,    55,    22,    25,    23,    27,    28,    29,    30,
      31,     8,    11,    12,    15,    23,    48,    56,    56,    56,
      56,    56,    44,    12
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    42,    42,    43,    43,
      44,    44,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    46,    47,    47,    48,    49,    50,    50,    50,    51,
      52,    52,    53,    54,    54,    54,    54,    54,    54,    55,
      55,    55,    55,    55,    55,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     8,     6,     7,     5,
       2,     1,     0,     4,     7,     5,     5,     5,     1,     3,
       3,     4,     3,     1,     1,     4,     0,     3,     1,     1,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 6: /* procedure: PROCEDURE proc_head IS VAR proc_head_declarations _BEGIN commands END  */
#line 60 "src\\parser\\parser.ypp"
                                                                            { codeGenerator->generateProcedureEndCode(memory, memory->finishProcedure((yyvsp[-1].num)));
                                                                              memory->clearCurrentProcedure(); }
#line 1209 "src\\parser\\parser.tab.cpp"
    break;

  case 7: /* procedure: PROCEDURE proc_head IS _BEGIN commands END  */
#line 62 "src\\parser\\parser.ypp"
                                                                            { codeGenerator->generateProcedureEndCode(memory, memory->finishProcedure((yyvsp[-1].num)));
                                                                              memory->clearCurrentProcedure(); }
#line 1216 "src\\parser\\parser.tab.cpp"
    break;

  case 8: /* main: PROGRAM IS VAR declarations _BEGIN commands END  */
#line 66 "src\\parser\\parser.ypp"
                                                                            { codeGenerator->writeCode("HALT"); }
#line 1222 "src\\parser\\parser.tab.cpp"
    break;

  case 9: /* main: PROGRAM IS _BEGIN commands END  */
#line 67 "src\\parser\\parser.ypp"
                                                                            { codeGenerator->writeCode("HALT"); }
#line 1228 "src\\parser\\parser.tab.cpp"
    break;

  case 10: /* commands: commands command  */
#line 70 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = (yyvsp[-1].num) + (yyvsp[0].num); }
#line 1234 "src\\parser\\parser.tab.cpp"
    break;

  case 13: /* command: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 75 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->assignValueToVariable(memory, *(yyvsp[-3].str), (yyvsp[-1].num)) + (yyvsp[-1].num); }
#line 1240 "src\\parser\\parser.tab.cpp"
    break;

  case 14: /* command: IF condition THEN commands ELSE commands ENDIF  */
#line 76 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->ifElseCondition(memory, (yyvsp[-5].condit), (yyvsp[-3].num), (yyvsp[-1].num)) + (yyvsp[-3].num) + (yyvsp[-1].num); }
#line 1246 "src\\parser\\parser.tab.cpp"
    break;

  case 15: /* command: IF condition THEN commands ENDIF  */
#line 77 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->ifCondition(memory, (yyvsp[-3].condit), (yyvsp[-1].num)) + (yyvsp[-1].num); }
#line 1252 "src\\parser\\parser.tab.cpp"
    break;

  case 16: /* command: WHILE condition DO commands ENDWHILE  */
#line 78 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->whileLoop(memory, (yyvsp[-3].condit), (yyvsp[-1].num)) + (yyvsp[-1].num); }
#line 1258 "src\\parser\\parser.tab.cpp"
    break;

  case 17: /* command: REPEAT commands UNTIL condition SEMICOLON  */
#line 79 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->repeatUntilLoop(memory, (yyvsp[-1].condit), (yyvsp[-3].num)) + (yyvsp[-3].num); }
#line 1264 "src\\parser\\parser.tab.cpp"
    break;

  case 18: /* command: execute_proc_head  */
#line 80 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->executeProcedure(memory, *(yyvsp[0].str), memory->getProcedureExecutionVariables()); }
#line 1270 "src\\parser\\parser.tab.cpp"
    break;

  case 19: /* command: READ IDENTIFIER SEMICOLON  */
#line 81 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->readValue(memory, *(yyvsp[-1].str)); }
#line 1276 "src\\parser\\parser.tab.cpp"
    break;

  case 20: /* command: WRITE value SEMICOLON  */
#line 82 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->printOutValue(memory, (yyvsp[-1].var)); }
#line 1282 "src\\parser\\parser.tab.cpp"
    break;

  case 24: /* execute_proc_head_declaration: IDENTIFIER  */
#line 92 "src\\parser\\parser.ypp"
                                                                            { memory->prepareProcedureExecutionVariable(memory, *(yyvsp[0].str)); }
#line 1288 "src\\parser\\parser.tab.cpp"
    break;

  case 25: /* proc_head: IDENTIFIER LB proc_head_declarations RB  */
#line 95 "src\\parser\\parser.ypp"
                                                                            { memory->setIdentifierToCurrentProcedure(*(yyvsp[-3].str)); }
#line 1294 "src\\parser\\parser.tab.cpp"
    break;

  case 29: /* proc_head_declaration: IDENTIFIER  */
#line 102 "src\\parser\\parser.ypp"
                                                                            { memory->addVariableToProcedure(*(yyvsp[0].str)); }
#line 1300 "src\\parser\\parser.tab.cpp"
    break;

  case 32: /* declaration: IDENTIFIER  */
#line 109 "src\\parser\\parser.ypp"
                                                                            { memory->addVariableToMemory(*(yyvsp[0].str), 0); }
#line 1306 "src\\parser\\parser.tab.cpp"
    break;

  case 33: /* expression: value  */
#line 112 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->setValueToAccumulator(memory, (yyvsp[0].var)); }
#line 1312 "src\\parser\\parser.tab.cpp"
    break;

  case 34: /* expression: value PLUS value  */
#line 113 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->add(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1318 "src\\parser\\parser.tab.cpp"
    break;

  case 35: /* expression: value MINUS value  */
#line 114 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->sub(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1324 "src\\parser\\parser.tab.cpp"
    break;

  case 36: /* expression: value MUL value  */
#line 115 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->mul(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1330 "src\\parser\\parser.tab.cpp"
    break;

  case 37: /* expression: value DIV value  */
#line 116 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->div(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1336 "src\\parser\\parser.tab.cpp"
    break;

  case 38: /* expression: value MOD value  */
#line 117 "src\\parser\\parser.ypp"
                                                                            { (yyval.num) = codeGenerator->mod(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1342 "src\\parser\\parser.tab.cpp"
    break;

  case 39: /* condition: value EQ value  */
#line 120 "src\\parser\\parser.ypp"
                                                                            { (yyval.condit) = codeGenerator->equal(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1348 "src\\parser\\parser.tab.cpp"
    break;

  case 40: /* condition: value NEQ value  */
#line 121 "src\\parser\\parser.ypp"
                                                                            { (yyval.condit) = codeGenerator->nequal(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1354 "src\\parser\\parser.tab.cpp"
    break;

  case 41: /* condition: value GREATER value  */
#line 122 "src\\parser\\parser.ypp"
                                                                            { (yyval.condit) = codeGenerator->greater(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1360 "src\\parser\\parser.tab.cpp"
    break;

  case 42: /* condition: value LESS value  */
#line 123 "src\\parser\\parser.ypp"
                                                                            { (yyval.condit) = codeGenerator->less(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1366 "src\\parser\\parser.tab.cpp"
    break;

  case 43: /* condition: value GREQ value  */
#line 124 "src\\parser\\parser.ypp"
                                                                            { (yyval.condit) = codeGenerator->greq(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1372 "src\\parser\\parser.tab.cpp"
    break;

  case 44: /* condition: value LEQ value  */
#line 125 "src\\parser\\parser.ypp"
                                                                            { (yyval.condit) = codeGenerator->leq(memory, (yyvsp[-2].var), (yyvsp[0].var)); }
#line 1378 "src\\parser\\parser.tab.cpp"
    break;

  case 45: /* value: NUM  */
#line 128 "src\\parser\\parser.ypp"
                                                                            { (yyval.var) = memory->getValueHolder((yyvsp[0].num)); }
#line 1384 "src\\parser\\parser.tab.cpp"
    break;

  case 46: /* value: IDENTIFIER  */
#line 129 "src\\parser\\parser.ypp"
                                                                            { (yyval.var) = memory->getVariableFromMemory(*(yyvsp[0].str)); }
#line 1390 "src\\parser\\parser.tab.cpp"
    break;


#line 1394 "src\\parser\\parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 131 "src\\parser\\parser.ypp"


void yyerror(std::string error) {
    std::cout << error << std::endl;
    exit(1);
}

int parser_main(int argc, char** argv) {
    codeGenerator = new CodeGenerator(argc, argv);
    memory = new Memory();

    yyin = codeGenerator->getInput();

    try {
        yyparse();
    } catch(std::string error) {
        yyerror(error);
    }
    
    std::cout << codeGenerator->getCode() << std::endl;

    delete memory;
    delete codeGenerator;

    return 0;
}
