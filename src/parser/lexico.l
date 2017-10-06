%option noyywrap
%option yylineno
%{
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "sintactico.tab.h"
extern vector<string> readed;

//#define DEBUG true
void debug(const char *);

%}

label [a-zA-Z][a-zA-Z1-9]*:
identificador [a-zA-Z][a-zA-Z1-9]* 
registro $[a-zA-Z][a-zA-Z1-9]*
numero (0x|0X)[0-9a-fA-F]+|[0-9]+|0[0-9]+

%%
\{	{return '{';}
\} {return '}';}
\( {return '(';}
\)	{return ')';}
\-	{return '-';}
\:	{return ':';}
\;	{return ';';}
\,	{return ',';}
\|	{return '|';}
\&	{return '&';}
\<	{return '<';}
\>	{return '>';}
\!	{return '!';}
\=	{return '=';}
\+	{return '+';}
\[	{return '[';}
\]	{return ']';}
\*	{return '*';}
\/	{return '/';}
\%	{return '%';}
" "	{;}
"\n" {;}
"\t"	{;}
"\r"	{;}
"\f"	{;}
{identificador} {debug("IDENTIFICADOR"); readed.push_back(string(yytext)); return IDENTIFICADOR; }
{registro} {debug("REGISTRO"); readed.push_back(string(yytext)); return REGISTRO; }
{numero} {debug("NUMERO"); readed.push_back(string(yytext)); return NUMERO; }
{label} {debug("LABEL"); readed.push_back(string(yytext)); return LABEL; }

%%

void debug(const char *lugar){
#ifdef DEBUG
    cerr << lugar << ": " << yytext << endl;
#endif
}
