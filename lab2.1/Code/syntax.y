%locations
%define parse.error verbose
%{
    #include "syntax_tree.h"
    #include "SDTAction.h"
    #include "symbol_table.h"

    #define GROUP_1 100
    #define GROUP_2 200
    #define GROUP_3 300
    #define GROUP_4 400
    #define GROUP_5 500
    #define GROUP_6 600
    #define GROUP_7 700
    #define GROUP_8 800

    int has_error = 0;
    void yyerror(const char *msg);
    void yyerror_lineno(const char *msg, int lineno);
%}

%union {
    int type_int;
    void *type_node;
}

%token <type_node> DEFER REFER
%token <type_node> SINGLEOR DATA PLACEHOLDER
%token <type_node> LOWERID UPPERID
%token <type_node> FUNC DEDUCT
%token <type_node> LET
%token <type_node> ASSIGNOP RELOP AND OR NOT
%token <type_node> PLUS MINUS STAR DIV
%token <type_node> BUILDINTYPE STRUCT INT FLOAT
%token <type_node> IF ELSE WHILE RETURN
%token <type_node> SEMI COMMA DOT
%token <type_node> LP RP LB RB LC RC

%type <type_node> ArrayType ReferType FuncCall
%type <type_node> ADTHeader ADTParamList ADTParam PatternMatching PatternMatchingParamList
%type <type_node> ConstructorId TypeId TypeIdList ConstructorDec ConstructorDecList ADTDef
%type <type_node> FuncType FuncParamType FuncBody
%type <type_node> DSList
%type <type_node> Program
%type <type_node> Specifier
%type <type_node> VarDec FuncDec VarList ParamDec
%type <type_node> CompSt Stmt
%type <type_node> VarDef DecList Dec
%type <type_node> Exp Args

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%nonassoc LOWER_THAN_DEDUCT
%nonassoc DEDUCT

%nonassoc LOWER_THAN_SEMI
%nonassoc SEMI

%nonassoc LOWER_THAN_ASSIGNOP
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
        $$ = new_parent_node("Program", GROUP_1 + 1, 1, $1);
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

/* 支持变量定义和变量使用的混合 */
/* 不再要求变量定义与变量使用分隔 */
/* StmtList & DefList */
DSList
    : Stmt DSList { $$ = new_parent_node("DSList", GROUP_2 + 1, 2, $1, $2); }
    | /* empty */ { $$ = new_parent_node("DSList", GROUP_2 + 2, 0); }
    ;

/* Statements */
Stmt
    : Exp SEMI { $$ = new_parent_node("Stmt", GROUP_3 + 1, 1, $1); }
    | VarDef SEMI { $$ = new_parent_node("Stmt", GROUP_3 + 2, 1, $1); }
    /* 为避免不明原因引起的冲突，把ADTDef后跟的SEMI移到下层产生式 */
    | ADTDef { $$ = new_parent_node("Stmt", GROUP_3 + 3, 1, $1); }
    | CompSt { $$ = new_parent_node("Stmt", GROUP_3 + 4, 1, $1); }
    | RETURN Exp SEMI { $$ = new_parent_node("Stmt", GROUP_3 + 5, 2, $1, $2); }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE { $$ = new_parent_node("Stmt", GROUP_3 + 6, 3, $1, $3, $5); }
    | IF LP Exp RP Stmt ELSE Stmt { $$ = new_parent_node("Stmt", GROUP_3 + 7, 5, $1, $3, $5, $6, $7); }
    | WHILE LP Exp RP Stmt { $$ = new_parent_node("Stmt", GROUP_3 + 8, 3, $1, $3, $5); }
    | SEMI { $$ = new_parent_node("Stmt", GROUP_3 + 9, 0); }
    ;
CompSt
    : LC DSList RC { $$ = new_parent_node("Compst", GROUP_3 + 9, 1, $2); }
    ;

/* Function */
/* 函数类型 */
FuncParamType
    : Specifier DEDUCT FuncParamType { 
        $$ = new_parent_node("FuncType", GROUP_4 + 1, 2, $1, $3); 
        $$ = new_parent_node("Specifier", 1000, 1, $$);
    }
    | Specifier { $$ = $1; }
    ;
FuncType
    : FUNC LP FuncParamType RP { 
        if (strcmp(((AST_node *)(((AST_node *)$3)->first_child))->str, "FuncType"))
        {
            $$ = new_parent_node("FuncType", GROUP_4 + 2, 1, $3);
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
    : LP VarList RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", GROUP_4 + 3, 2, $2, $5); }
    | LP RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", GROUP_4 + 4, 1, $4); }
    ;
VarList
    : ParamDec COMMA VarList { $$ = new_parent_node("VarList", GROUP_4 + 5, 2, $1, $3); }
    | ParamDec { $$ = new_parent_node("VarList", GROUP_4 + 6, 1, $1); }
    ;
ParamDec
    : Specifier VarDec { $$ = new_parent_node("ParamDec", GROUP_4 + 7, 2, $1, $2); }
    ;
FuncBody
    : FuncDec CompSt { $$ = new_parent_node("FuncBody", GROUP_4 + 8, 2, $1, $2); }
    ;
/* 函数调用 */
FuncCall
    : Exp LP Args RP { $$ = new_parent_node("FuncCall", GROUP_4 + 9, 2, $1, $3); }
    ;
Args
    : Exp COMMA Args { $$ = new_parent_node("Args", GROUP_4 + 10, 2, $1, $3); }
    | PLACEHOLDER COMMA Args { $$ = new_parent_node("Args", GROUP_4 + 11, 2, $1, $3); }
    | /* empty */ { $$ = new_parent_node("Args", GROUP_4 + 12, 0); }
    ;

/* Array */
ArrayType
    : Specifier LB Exp RB { $$ = new_parent_node("ArrayType", GROUP_5 + 1, 2, $1, $3); }
    ;

/* REFEVR */
/* 指针 */
ReferType
    : REFER LP Specifier RP
    ;

/* ADT */
ADTDef
    : ADTHeader %prec LOWER_THAN_ASSIGNOP SEMI
    | ADTHeader ASSIGNOP ConstructorDecList
    ;
ADTHeader
    : DATA TypeId ADTParamList
    ;
ADTParamList
    : ADTParam ADTParamList
    | /* empty */ { }
    ;
ADTParam
    : LOWERID
    ;
ConstructorDecList
    /* 分号不能上移，否则冲突 */
    : ConstructorDec SEMI
    | ConstructorDec SEMI ConstructorDecList
    ;
ConstructorDec
    : ConstructorId TypeIdList
    ;
ConstructorId
    : UPPERID
    ;
TypeIdList
    : TypeId TypeIdList
    | ADTParam TypeIdList
    | /* empty */ { }
    ;
TypeId
    : UPPERID
    ;
/* pattern matching */
PatternMatching
    : LET LP ConstructorId PatternMatchingParamList RP ASSIGNOP VarDec
    ;
PatternMatchingParamList
    : LOWERID PatternMatchingParamList
    | PLACEHOLDER PatternMatchingParamList
    | /* empty */ { }
    ;

/* Specifiers */
Specifier
    : BUILDINTYPE { $$ = new_parent_node("Specifier", 9, 1, $1); }
    | LET { $$ = new_parent_node("Specifier", 1000, 1, $1); }
    | TypeId { $$ = new_parent_node("Specifier", 10, 1, $1); }
    | ArrayType
    | ReferType
    | FuncType { $$ = $1; }
    ;

/* Local Definitions */
VarDef
    : Specifier DecList { $$ = new_parent_node("VarDef", 34, 2, $1, $2); }
    /* 模式匹配也可看成是一种特殊的变量定义 */
    | PatternMatching
    ;
DecList
    : Dec { $$ = new_parent_node("DecList", 35, 1, $1); }
    | Dec COMMA DecList { $$ = new_parent_node("DecList", 36, 3, $1, $2, $3); }
    ;
Dec
    : VarDec { $$ = new_parent_node("Dec", 37, 1, $1); }
    | VarDec ASSIGNOP Exp { $$ = new_parent_node("Dec", 38, 3, $1, $2, $3); }
    ;
/* Declarators */
VarDec
    : LOWERID { $$ = new_parent_node("VarDec", 16, 1, $1); }
    ;

/* Expressions */
Exp
    : Exp ASSIGNOP Exp {$$ = new_parent_node("Exp", 39, 3, $1, $2, $3); }
    /* 关系运算表达式／逻辑表达式／算数表达式 */
    | Exp RELOP Exp { $$ = new_parent_node("Exp", 42, 3, $1, $2, $3); }
    | Exp AND Exp { $$ = new_parent_node("Exp", 40, 3, $1, $2, $3); }
    | Exp OR Exp { $$ = new_parent_node("Exp", 41, 3, $1, $2, $3); }
    | NOT Exp { $$ = new_parent_node("Exp", 49, 2, $1, $2); }
    | Exp PLUS Exp { $$ = new_parent_node("Exp", 43, 3, $1, $2, $3); }
    | Exp MINUS Exp { $$ = new_parent_node("Exp", 44, 3, $1, $2, $3); }
    | Exp STAR Exp { $$ = new_parent_node("Exp", 45, 3, $1, $2, $3); }
    | Exp DIV Exp { $$ = new_parent_node("Exp", 46, 3, $1, $2, $3); }
    | MINUS Exp { $$ = new_parent_node("Exp", 48, 2, $1, $2); }
    /* 加上括号改变优先级 */
    | LP Exp RP { $$ = new_parent_node("Exp", 47, 3, $1, $2, $3); }
    /* 函数调用 */
    | FuncCall
    /* DEFER相关表达式 */
    | REFER LP Exp RP
    | DEFER LP Exp RP
    /* 从ADT中取数据 */
    | Exp DOT INT { $$ = new_parent_node("Exp", 53, 3, $1, $2, $3); }
    /* Exp building block */
    | VarDec { $$ = new_parent_node("Exp", 54, 1, $1); }
    | INT { $$ = new_parent_node("Exp", 55, 1, $1); }
    | FLOAT { $$ = new_parent_node("Exp", 56, 1, $1); }
    | FuncBody { $$ = $1; }
    ;
