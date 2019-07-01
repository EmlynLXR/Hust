%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	int type_float;
	int type_char;
	char type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL

%}
%option yylineno

id   [A-Za-z][A-Za-z0-9]*  
int    [0-9]+
float  ([0-9]*\.[0-9]+)|([0-9]+\.)
char (\'[\x21-\x7D]\')
CommentSingleLine   ("//"[^\n]*)

%%
{int}        {yylval.type_int=atoi(yytext);printf("%d,%s\n",INT,yytext); return INT;}
{float}      {yylval.type_float=atof(yytext); printf("%d,%s\n",FLOAT,yytext);return FLOAT;}
{char}		 {yylval.type_char=yytext[1]; printf("%d,%c\n",CHAR,yytext[1]);return CHAR;}
{CommentSingleLine} {printf("CommentSingleLine,%s\n",yytext);}
"int"        {strcpy(yylval.type_id,  yytext);printf("%d,%s\n",TYPE,yytext);return TYPE;}
"float"      {strcpy(yylval.type_id,  yytext);printf("%d,%s\n",TYPE,yytext);return TYPE;}
"char"		 {strcpy(yylval.type_id,  yytext);printf("%d,%s\n",TYPE,yytext);return TYPE;}


"return"    {printf("%d,%s\n",RETURN,yytext);return RETURN;}
"if"        {printf("%d,%s\n",IF,yytext);return IF;}
"else"      {printf("%d,%s\n",ELSE,yytext);return ELSE;}
"while"     {printf("%d,%s\n",WHILE,yytext);return WHILE;}
"for"		{printf("%d,%s\n",FOR,yytext);return FOR;}

{id}       	{strcpy(yylval.type_id,  yytext);printf("%d,%s\n",ID,yytext); return ID;/*由于关键字的形式也符合表示符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{printf("%d,%s\n",SEMI,yytext);return SEMI;}
","			{printf("%d,%s\n",COMMA,yytext);return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);printf("%d,%s\n",RELOP,yytext);return RELOP;}
"+="|"-="|"*="|"/="|"%=" {strcpy(yylval.type_id, yytext);printf("%d,%s\n",COMOP,yytext);return COMOP;}
"++"|"--"	{strcpy(yylval.type_id, yytext);printf("%d,%s\n",DOUOP,yytext);return DOUOP;}
"="			{printf("%d,%s\n",ASSIGNOP,yytext);return ASSIGNOP;}
"+"			{printf("%d,%s\n",PLUS,yytext);return PLUS;}
"-"			{printf("%d,%s\n",MINUS,yytext);return MINUS;}
"*"			{printf("%d,%s\n",STAR,yytext);return STAR;}
"/"			{printf("%d,%s\n",DIV,yytext);return DIV;}
"&&"        {printf("%d,%s\n",AND,yytext);return AND;}
"||"        {printf("%d,%s\n",OR,yytext);return OR;}
"!"			{printf("%d,%s\n",NOT,yytext);return NOT;}
"("			{printf("%d,%s\n",LP,yytext);return LP;}
")"			{printf("%d,%s\n",RP,yytext);return RP;}
"{"			{printf("%d,%s\n",LC,yytext);return LC;}
"}"			{printf("%d,%s\n",RC,yytext);return RC;}
[\n]           {yycolumn=1;}   
[ \r\t]          {}   
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}


%%

int yywrap()
{
return 1;
}
