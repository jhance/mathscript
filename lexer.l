%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"

%}

%%

[0-9]+      yylval.int_val = atoi(yytext); return T_INTEGER;
Print       return T_PRINT;
If          return T_IF;
[a-z]       yylval.char_val = yytext[0]; return T_VARIABLE_IDENTIFIER;
[A-Z]       yylval.char_val = yytext[0]; return T_FUNCTION_IDENTIFIER;
\n          /* do nothing */
[ \t]       /* do nothing */
.           return (int) yytext[0];
%%
