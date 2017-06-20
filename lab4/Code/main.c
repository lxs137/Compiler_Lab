#include <stdio.h>
#include "syntax.tab.h"
#include "lex.yy.c"
extern FILE *f_output;
int main(int argc, char **argv)
{
    if (argc < 1)
    {
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    f_output = fopen(argv[2], "w+");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    if(!f_output)
    {
        perror(argv[2]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    fclose(f);
    fclose(f_output);
    yylex_destroy();
    return 0;
}
extern int has_error;
void yyerror(const char *msg)
{
    has_error = 1;
    printf("Error type B at line %d: ", yylineno);
    printf("%s\n", msg);
}
void yyerror_lineno(const char *msg, int lineno)
{
    has_error = 1;
    printf("Error type B at line %d: ", lineno);
    printf("%s\n", msg);
}
