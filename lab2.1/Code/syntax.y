%locations
%define parse.error verbose
%{
    #include "syntax_tree.h"
    #include "SDTAction.h"
    #include "symbol_table.h"
    int has_error = 0;
    void yyerror(const char *msg);
    void yyerror_lineno(const char *msg, int lineno);
%}

%union {
    int type_int;
    void *type_node;
}

%token <type_node> SINGLEOR DATA
%token <type_node> VALUEID NVALUEID
%token <type_node> FUNC DEDUCT
%token <type_node> LET
%token <type_node> ASSIGNOP RELOP AND OR NOT
%token <type_node> PLUS MINUS STAR DIV
%token <type_node> BUILDINTYPE STRUCT INT FLOAT
%token <type_node> IF ELSE WHILE RETURN
%token <type_node> SEMI COMMA DOT
%token <type_node> LP RP LB RB LC RC

%type <type_node> ADTHeader ADTParamList ADTParam
%type <type_node> ConstructorId TypeId TypeIdList ConstructorDec ConstructorDecList ADTDef
%type <type_node> FuncType FuncParamType FuncBody
%type <type_node> DSList
%type <type_node> Program
%type <type_node> Specifier
%type <type_node> VarDec FuncDec VarList ParamDec
%type <type_node> CompSt Stmt
%type <type_node> Def DecList Dec
%type <type_node> Exp Args
%type <type_node> StructDefList StructDef StructDecList
%type <type_node> NamedStructDef AnonymousStructDef

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%nonassoc LOWER_THAN_DEDUCT
%nonassoc DEDUCT

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT

%%
/* High-level Definitions */
Program
    : DSList {
        $$ = new_parent_node("Program", 1, 1, $1);
        print_child_node($$, 0);
        /* initTable(); */
        /* initTable_lxs(); */
        /* globalSymbolTable = newSymbolTable(); */
        /* globalFUNCSymbolTable = newFUNCSymbolTable(); */
        /* globalStructStack = newStructStack(); */
        /* traversalTreePerformAction($$); */
        /* //printSymbolTable(globalSymbolTable); */
        /* findUndefinedFUNCtion(); */
        /* clean_up_syntax_tree($$); */
        /* cleanUpSymbolTable(); */
    }
    ;

/* 增加函数类型构造子 */
/* 函数类型允许两种基本形式：只有一个返回值类型的函数类型；具有一个输入值类型和一个返回值类型的函数类型 */
/* 不允许函数没有返回值 */
/* 多参数函数用科里化变成嵌套的第二种形式的函数类型 */
FuncParamType
    : Specifier DEDUCT FuncParamType { 
        $$ = new_parent_node("FuncType", 101, 2, $1, $3); 
        $$ = new_parent_node("Specifier", 1000, 1, $$);
    }
    | Specifier { $$ = $1; }
    ;
FuncType
    : FUNC LP FuncParamType RP { 
        if (strcmp(((AST_node *)(((AST_node *)$3)->first_child))->str, "FuncType"))
        {
            $$ = new_parent_node("FuncType", 102, 1, $3);
            $$ = new_parent_node("Specifier", 1000, 1, $$);
        }
        else 
        {
            $$ = $3;
        }
    }
    ;
/* 函数体的定义 */
FuncDec
    : LP VarList RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", 104, 2, $2, $5); }
    | LP RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", 105, 1, $4); }
    ;
FuncBody
    : FuncDec CompSt { $$ = new_parent_node("FuncBody", 106, 2, $1, $2); }
    ;

/* ADT */
ADTDef
    : ADTHeader ASSIGNOP  ConstructorDecList
    | ADTHeader
    ;

ADTHeader
    : DATA TypeId ADTParamList
    ;

ADTParamList
    : ADTParam ADTParamList
    | /* empty */ { }
    ;

ADTParam
    : VALUEID
    ;

ConstructorDecList
    : ConstructorDec SEMI
    | ConstructorDec SEMI ConstructorDecList
    ;

ConstructorDec
    : ConstructorId TypeIdList
    ;

TypeIdList
    : TypeId TypeIdList
    | ADTParam TypeIdList
    | /* empty */ { }
    ;

TypeId
    : NVALUEID
    ;

ConstructorId
    : NVALUEID
    ;

/* Specifiers */
Specifier
    : BUILDINTYPE { $$ = new_parent_node("Specifier", 9, 1, $1); }
    | NVALUEID { $$ = new_parent_node("Specifier", 10, 1, $1); }
    | FuncType { $$ = $1; }
    | LET { $$ = new_parent_node("Specifier", 1000, 1, $1); }
    ;

/* 结构体定义中允许出现变量定义／具名结构体的声明／嵌套具名结构体的定义／嵌套匿名结构体的定义 */
StructDefList
    : StructDef StructDefList { $$ = new_parent_node("StructDefList", 1000, 2, $1, $2); }
    | NamedStructDef StructDefList { $$ = new_parent_node("StructDefList", 1000, 2, $1, $2); }
    | AnonymousStructDef VarDec SEMI StructDefList { $$ = new_parent_node("StructDefList", 1000, 3, $1, $2, $4); }
    | SEMI StructDefList { $$ = $2; }
    | /* empty */ { $$ = new_parent_node("StructDefList", 1000, 0); }
/* 结构体定义中不允许出现巨头初始化的变量定义 */
StructDef
    : Specifier StructDecList SEMI { $$ = new_parent_node("Def", 34, 3, $1, $2, $3); }
    ;
StructDecList
    : VarDec { $$ = new_parent_node("DecList", 35, 1, $1); }
    | VarDec COMMA StructDecList { $$ = new_parent_node("DecList", 36, 3, $1, $2, $3); }
    ;
/* 具名结构体的定义 */
/* 具名结构体后一定不跟变量的定义 */
NamedStructDef
    : STRUCT NVALUEID LC StructDefList RC SEMI
    ;
/* 匿名结构体的定义 */
/* 匿名结构体后一定要跟变量的定义 */
AnonymousStructDef
    : STRUCT LC StructDefList RC
    ;

/* Declarators */
VarDec
    : VALUEID { $$ = new_parent_node("VarDec", 16, 1, $1); }
    | VarDec LB INT RB { $$ = new_parent_node("varDec", 17, 4, $1, $2, $3, $4); }
    ;
VarList
    : ParamDec COMMA VarList { $$ = new_parent_node("VarList", 20, 2, $1, $3); }
    | ParamDec { $$ = new_parent_node("VarList", 21, 1, $1); }
    ;
ParamDec
    : Specifier VarDec { $$ = new_parent_node("ParamDec", 22, 2, $1, $2); }
    ;

/* 支持变量定义和变量使用的混合 */
/* 不再要求变量定义与变量使用分隔 */
/* StmtList & DefList */
DSList
    : Stmt DSList { $$ = new_parent_node("DSList", 1000, 2, $1, $2); }
    | Def DSList { $$ = new_parent_node("DSList", 1000, 2, $1, $2); }
    /* | StructSpecifier DSList { $$ = new_parent_node("DSList", 1000, 2, $1, $2); } */
    | NamedStructDef DSList { $$ = new_parent_node("DSList", 1000, 2, $1, $2); }
    | AnonymousStructDef VarDec SEMI DSList { $$ = new_parent_node("DSList", 1000, 3, $1, $2, $4); }
    | ADTDef DSList
    | SEMI DSList { $$ = $2; }
    | /* empty */ { $$ = new_parent_node("DSList", 1000, 0); }
    ;

/* Statements */
CompSt
    /* : LC DefList StmtList RC { $$ = new_parent_node("CompSt", 23, 4, $1, $2, $3, $4); } */
    : LC DSList RC { $$ = new_parent_node("Compst", 23, 1, $2); }
    ;

Stmt
    : Exp SEMI { $$ = new_parent_node("Stmt", 26, 2, $1, $2); }
    | CompSt { $$ = new_parent_node("Stmt", 27, 1, $1); }
    | RETURN Exp SEMI { $$ = new_parent_node("Stmt", 28, 3, $1, $2, $3); }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE { $$ = new_parent_node("Stmt", 29, 5, $1, $2, $3, $4, $5); }
    | IF LP Exp RP Stmt ELSE Stmt { $$ = new_parent_node("Stmt", 30, 7, $1, $2, $3, $4, $5, $6, $7); }
    | WHILE LP Exp RP Stmt { $$ = new_parent_node("Stmt", 31, 5, $1, $2, $3, $4, $5); }
    ;

/* Local Definitions */
Def
    : Specifier DecList SEMI { $$ = new_parent_node("Def", 34, 3, $1, $2, $3); }
    ;
DecList
    : Dec { $$ = new_parent_node("DecList", 35, 1, $1); }
    | Dec COMMA DecList { $$ = new_parent_node("DecList", 36, 3, $1, $2, $3); }
    ;
Dec
    : VarDec { $$ = new_parent_node("Dec", 37, 1, $1); }
    | VarDec ASSIGNOP Exp { $$ = new_parent_node("Dec", 38, 3, $1, $2, $3); }
    ;

/* Expressions */
Exp
    : Exp ASSIGNOP Exp {$$ = new_parent_node("Exp", 39, 3, $1, $2, $3); }
    | Exp AND Exp { $$ = new_parent_node("Exp", 40, 3, $1, $2, $3); }
    | Exp OR Exp { $$ = new_parent_node("Exp", 41, 3, $1, $2, $3); }
    | Exp RELOP Exp { $$ = new_parent_node("Exp", 42, 3, $1, $2, $3); }
    | Exp PLUS Exp { $$ = new_parent_node("Exp", 43, 3, $1, $2, $3); }
    | Exp MINUS Exp { $$ = new_parent_node("Exp", 44, 3, $1, $2, $3); }
    | Exp STAR Exp { $$ = new_parent_node("Exp", 45, 3, $1, $2, $3); }
    | Exp DIV Exp { $$ = new_parent_node("Exp", 46, 3, $1, $2, $3); }
    | LP Exp RP { $$ = new_parent_node("Exp", 47, 3, $1, $2, $3); }
    | MINUS Exp { $$ = new_parent_node("Exp", 48, 2, $1, $2); }
    | NOT Exp { $$ = new_parent_node("Exp", 49, 2, $1, $2); }
    | VALUEID LP Args RP { $$ = new_parent_node("Exp", 50, 4, $1, $2, $3, $4); }
    | VALUEID LP RP { $$ = new_parent_node("Exp", 51, 3, $1, $2, $3); }
    | Exp LB Exp RB { $$ = new_parent_node("Exp", 52, 4, $1, $2, $3, $4); }
    | Exp DOT VALUEID { $$ = new_parent_node("Exp", 53, 3, $1, $2, $3); }
    | VALUEID { $$ = new_parent_node("Exp", 54, 1, $1); }
    | INT { $$ = new_parent_node("Exp", 55, 1, $1); }
    | FLOAT { $$ = new_parent_node("Exp", 56, 1, $1); }
    | FuncBody { $$ = $1; }
    ;

Args
    : Exp COMMA Args { $$ = new_parent_node("Args", 57, 2, $1, $3); }
    | Exp { $$ = new_parent_node("Args", 58, 1, $1); }
    ;
