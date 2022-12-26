/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 19 "src\\parser\\parser.ypp"

#include "../Variable.h"
#include "../CodeGenerator.h"

#line 54 "src\\parser\\parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROCEDURE = 258,               /* PROCEDURE  */
    PROGRAM = 259,                 /* PROGRAM  */
    IS = 260,                      /* IS  */
    VAR = 261,                     /* VAR  */
    _BEGIN = 262,                  /* _BEGIN  */
    END = 263,                     /* END  */
    IF = 264,                      /* IF  */
    THEN = 265,                    /* THEN  */
    ELSE = 266,                    /* ELSE  */
    ENDIF = 267,                   /* ENDIF  */
    WHILE = 268,                   /* WHILE  */
    DO = 269,                      /* DO  */
    ENDWHILE = 270,                /* ENDWHILE  */
    REPEAT = 271,                  /* REPEAT  */
    UNTIL = 272,                   /* UNTIL  */
    READ = 273,                    /* READ  */
    WRITE = 274,                   /* WRITE  */
    NUM = 275,                     /* NUM  */
    IDENTIFIER = 276,              /* IDENTIFIER  */
    COMMA = 277,                   /* COMMA  */
    SEMICOLON = 278,               /* SEMICOLON  */
    LB = 279,                      /* LB  */
    RB = 280,                      /* RB  */
    ASSIGN = 281,                  /* ASSIGN  */
    PLUS = 282,                    /* PLUS  */
    MINUS = 283,                   /* MINUS  */
    MUL = 284,                     /* MUL  */
    DIV = 285,                     /* DIV  */
    MOD = 286,                     /* MOD  */
    EQ = 287,                      /* EQ  */
    NEQ = 288,                     /* NEQ  */
    GREATER = 289,                 /* GREATER  */
    LESS = 290,                    /* LESS  */
    GREQ = 291,                    /* GREQ  */
    LEQ = 292,                     /* LEQ  */
    TEST = 293                     /* TEST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "src\\parser\\parser.ypp"

    unsigned int num;
    std::string* str;
    Variable* var;
    Cond* condit;

#line 116 "src\\parser\\parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_PARSER_TAB_HPP_INCLUDED  */
