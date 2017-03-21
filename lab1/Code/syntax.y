%locations
%{
    #include "syntax_tree.h"
%}

%union {
    int type_int;
    void* type_node;
}

%token <type_node> NOT INT FLOAT ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE
%type <type_node> Exp VarDec

%%

/* High-level Definitions */
Program :
      ExtDefList  
    ;
ExtDefList :
      ExtDef
    | ExtDefList
    | /* empty */
    ;
ExtDef :
      Specifier ExtDefList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    ;
//VarDec_ :
      /* empty */
//    | COMMA ExtDecList
//    ;
 ExtDecList :
       VarDec
     | VarDec COMMA ExtDecList
     ;
//ExtDecList :
//      VarDec VarDec_
//    ;

/* Specifiers */
Specifier :
      TYPE
    | StructSpecifier
    ;
StructSpecifier :
      STRUCT OptTag LC DefList RC
    | STRUCT Tag
    ;
OptTag :
       ID
    | /* empty */
    ;
Tag :
    ID

/* Declarators */
VarDec :
      ID { $$ = new_parent_node(1, $1); }
    | VarDec LB INT RB
    ;
FunDec :
      ID LP VarList RP
    | ID LP RP
    ;
VarList :
      ParamDec COMMA VarList
    | ParamDec
    ;
ParamDec :
      Specifier
    | VarDec
    ;

/* Statements */
CompSt :
       LC DefList StmtList RC
    ;
StmtList :
      Stmt StmtList
    | /* empty */
    ;
Stmt :
      Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt
    | IF LP Exp RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt
    ;

/* Local Definitions */
DefList :
      Def DefList
    | /* empty */
    ;
Def :
      Specifier DecList SEMI
    ;
DecList :
      Dec
    | Dec COMMA DecList
    ;
Dec :
      VarDec
    | VarDec ASSIGNOP Exp { 
        AST_node* m_node = new_parent_node(3, $1, $2, $3);
        printf("Bison--%s: %d, %d\n", m_node->str, m_node->loc_line, m_node->loc_column);
    }
    ;

/* Expressions */
Exp :
      Exp ASSIGNOP Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp RELOP Exp
    | Exp PLUS Exp
    | Exp MINUS Exp
    | Exp STAR Exp
    | Exp DIV Exp
    | LP Exp RP
    | MINUS Exp
    | NOT Exp
    | ID LP Args RP
    | ID LP RP
    | Exp LB Exp RB
    | Exp DOT ID
    | ID
    | INT
    | FLOAT { 
        $$ = new_parent_node(1, $1);
    }
    ;
Args :
      Exp COMMA Args
    | Exp
    ;
