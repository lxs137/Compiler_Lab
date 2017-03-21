%{
#define flex_debug_print
    #include <stdio.h>
    #include <stdlib.h>
    #include "syntax.tab.h"
    #include "syntax_tree.h"

    
    // 维护词法单元的位置信息
    int yylines = 1;
    int yycolumn = 1;
    #define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylines; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;

    void print_loc_info(char* name);
    enum RelopType
    {
        less = 0,
        more,
        less_equal,
        more_equal,
        equal,
        not_equal
    };
%}

digit [0-9]
letter [a-zA-Z|_]
ws [ |\t|\n]

%%
\n    { 
    yylines++;
    yycolumn = 1;
    printf("next_line\n"); 
}
{ws}+    { print_loc_info("find white space"); }
";"    {
    print_loc_info("SEMI");
    yylval.type_node = (void *)new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return SEMI;
}
","    {
    print_loc_info("COMMA");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return COMMA;
}
"="    {
    print_loc_info("ASSIGNOP");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return ASSIGNOP;
}
"<"    {
    print_loc_info("RELOP-less");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RELOP;
}
">"    {
    print_loc_info("RELOP-more");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RELOP;
}
"<="    {
    print_loc_info("RELOP-less_equal");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RELOP;
}
">="    {
    print_loc_info("RELOP-more_equal");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RELOP;
}
"=="    {
    print_loc_info("RELOP-equal");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RELOP;
}
"!="    {
    print_loc_info("RELOP-not_equal");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RELOP;
}
"+"    {
    print_loc_info("PLUS");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return PLUS;
}
"-"    {
    print_loc_info("MINUS");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return MINUS;
}
"*"    {
    print_loc_info("STAR");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return STAR;
}
"/"    {
    print_loc_info("DIV");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return DIV;
}
"&&"    {
    print_loc_info("AND");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return AND;
}
\|\|    {
    print_loc_info("OR");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return OR;
}
"."    {
    print_loc_info("DOT");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return DOT;
}
"!"    {
    print_loc_info("NOT");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return NOT;
}
int    {
    print_loc_info("TYPE-int");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return TYPE;
}
float    {
    print_loc_info("TYPE-float");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return TYPE;
}
"("    {
    print_loc_info("LP");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return LP;
}
")"    {
    print_loc_info("RP");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RP;
}
"["    {
    print_loc_info("LB");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return LB;
}
"]"    {
    print_loc_info("RB");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RB;
}
"{"    {
    print_loc_info("LC");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return LC;
}
"}"    {
    print_loc_info("RC");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RC;
}
struct    {
    print_loc_info("STRUCT");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return STRUCT;
}
return    {
    print_loc_info("RETURN");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return RETURN;
}
if    {
    print_loc_info("IF");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return IF;
}
else    {
    print_loc_info("ELSE");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return ELSE;
}
while    { 
    print_loc_info("WHILE");
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return WHILE;
}
0|[1-9]{digit}*    { 
    //yylval=atoi(yytext);
    char debug_output[50];
    strcpy(debug_output, "INT---");
    strcat(debug_output, yytext);
    print_loc_info(debug_output);
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return INT;
}
(({digit}*\.{digit}+)|({digit}+\.{digit}*))([Ee][+-]?[0-9]+)?    {
    //yylval.type_node = atof(yytext);
    char debug_output[50];
    strcpy(debug_output, "FLOAT---");
    strcat(debug_output, yytext);
    print_loc_info(debug_output);
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return FLOAT;
}
{letter}({letter}|{digit})*    {
    char debug_output[50];
    strcpy(debug_output, "ID---");
    strcat(debug_output, yytext);
    strcat(debug_output, "\0");
    print_loc_info(debug_output);
    yylval.type_node = new_token_node(yylloc.first_line, yylloc.first_column, yytext);
    return ID;
}
.    {
    printf("Error Type A at line %d", yylloc.first_line);
}

%%

void print_loc_info(char* name)
{
#ifdef flex_debug_print
    printf("%s: line--%d; column--%d\n", name, yylloc.first_line, yylloc.first_column);
#endif
}
