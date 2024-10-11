%{
 #include <string.h>
 #include "nutsh.tab.h"
%}

%% 
[ \t] {	} // ignore all whitespaces
\n {return NEWLINE;}
">" {return GREAT;}
"<" {return LESS;}
">>" {return GREATGREAT;}
">>&" {return GREATGREATAMPERSAND;}
">&" {return GREATAMPERSAND;}
"|" {return PIPE;}
"&" {return AMPERSAND;}
[^ \t\n][^ \t\n]* {
	yylval.string_val = strdup(yytext);
	return WORD;
}
%%
