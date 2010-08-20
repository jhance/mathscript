%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"

%}

%start S_COMMENT M_COMMENT
%%

<INITIAL>[0-9]+     yylval.int_val = atoi(yytext); return T_INTEGER;
<INITIAL>True       yylval.int_val = 1; return T_INTEGER;
<INITIAL>False      yylval.int_val = 0; return T_INTEGER;
<INITIAL>Print      return T_PRINT;
<INITIAL>If         return T_IF;
<INITIAL>While      return T_WHILE;
<INITIAL>For        return T_FOR;
<INITIAL>\>         return T_COMPARE_G;
<INITIAL>\>=        return T_COMPARE_GE;
<INITIAL><          return T_COMPARE_L;
<INITIAL><=         return T_COMPARE_LE;
<INITIAL>==         return T_COMPARE_E;
<INITIAL>!=         return T_COMPARE_NE;
<INITIAL>[a-z]      yylval.char_val = yytext[0]; return T_VARIABLE_IDENTIFIER;
<INITIAL>[A-Z]      yylval.char_val = yytext[0]; return T_FUNCTION_IDENTIFIER;
<INITIAL>\/\*       BEGIN M_COMMENT;
<INITIAL>\/\/       BEGIN S_COMMENT;
<INITIAL>^#        BEGIN S_COMMENT;
<INITIAL>\n         /* do nothing */
<INITIAL>[ \t]      /* do nothing */
<INITIAL>.          return (int) yytext[0];

<M_COMMENT>\*\/     BEGIN INITIAL;
<M_COMMENT>.        /* do nothing */

<S_COMMENT>\n       BEGIN INITIAL;
<S_COMMENT>.        /* do nothing */
%%
