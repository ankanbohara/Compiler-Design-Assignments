%{
	#include <stdio.h>
%}
/* regular definitions */
keyword auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while
id ^[A-Z a-z _][A-Z a-z 0-9_]*
number -?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?)
%%
{keyword} {printf("keyword");}
{id} {printf("Identifier");}
{number} {printf("Number");}
%%
int main()
{
	yylex();
	return 0;
}