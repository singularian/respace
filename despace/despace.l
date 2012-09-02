%option noyywrap
%{
#include <stdio.h>
// #include <conio.h>
#include <stdlib.h>
#include <string.h>
%}
lt                        [<]
gt                       [>]
nl                       [\n]
line                   .|\n
space                 [ ]
comment          [#]
commentline    {comment}.*{nl}
commlines        [<][#]{line}*[#][>][\n]?
%%

{space}                        { /* remove single space */ }
([0-9]+{space}+[0-9]+)+        { printf("%s", yytext); }          
{space}+                       { printf("%s", yytext); }
.|\n                           {  printf("%s", yytext); }
%%

int main (int argc, char *argv[], char const *opts)
{

     if (argc > 1)   {
		FILE *file;
		file = fopen(argv[1], "r");
		yyin = file; 
		yylex();
		fclose(file);
        }
	else
	{
        	yylex();
	}
	return (0);
}
