%option noyywrap
%option yylineno

%{
#include <string>
#include <iostream>
#include "parser.tab.hpp"

int yylex();
%}

%s COMMENT

%%

\n                  {}
[[:blank:]]+        {}

"[".*"]"			{}

PROCEDURE           { return PROCEDURE; }
IS                  { return IS; }
VAR                 { return VAR; }
BEGIN               { return _BEGIN; }
END                 { return END; }

PROGRAM             { return PROGRAM; }

IF                  { return IF; }
THEN                { return THEN; }
ELSE                { return ELSE; }
ENDIF               { return ENDIF; }

WHILE               { return WHILE; }
DO                  { return DO; }
ENDWHILE            { return ENDWHILE; }

REPEAT              { return REPEAT; }
UNTIL               { return UNTIL; }

READ                { return READ; }
WRITE               { return WRITE; }

[0-9]+              { yylval.num = std::stoll(yytext); return NUM; }
[_a-z]+             { yylval.str = new std::string(yytext); return IDENTIFIER; }
":="                { return ASSIGN; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MUL; }
"/"                 { return DIV; }
"%"                 { return MOD; }
"="                 { return EQ; }
"!="                { return NEQ; }
">"                 { return GREATER; }
"<"                 { return LESS; }
">="                { return GREQ; }
"<="                { return LEQ; }
"("                  { return LB; }
")"                  { return RB; }
","                  { return COMMA; }
";"                  { return SEMICOLON; }

%%