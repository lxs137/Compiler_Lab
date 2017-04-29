#include "SDTAction.h"
#include <assert.h>
#include <malloc.h>

enum TypeKindEnum { BuildInType, ArrayType, ReferType, FunctionType, AlgebraicDataType };

typedef struct
{
    enum TypeKindEnum typeKind;
    void *node;
    void *nextInfo;
} TypeInfo;

/* 节点中的域除特别说明者，均为继承属性 */

typedef struct
{
    TypeInfo *arrayTo;
    int width;
} ArrayNode;

typedef struct
{
    TypeInfo *referTo;
} ReferNode;

typedef struct
{
    TypeInfo *paramTypeInfo;
    TypeInfo *returnTypeInfo;
} FunctionNode;

typedef struct LN
{
    struct LN *lastBrother, *nextBrother;
    void *data;
} ListNode;

typedef struct
{
    char *constructorIdName;
    ListNode *fields;
} ConstructorNode;

typedef struct
{
    char *typeIdName;
    ListNode *constructors;
} AlgebraicDataTypeNode;

/* FuncParamType */
/*     : Specifier DEDUCT FuncParamType { */ 
/*         $$ = new_parent_node("FuncType", GROUP_4 + 1, 2, $1, $3); */ 
/*         $$ = new_parent_node("Specifier", GROUP_8 + 6, 1, $$); */
/*     } */
/*     | Specifier { $$ = $1; } */
/*     ; */
ID(401)
{
}

/* FuncType */
/*     : FUNC LP FuncParamType RP { */ 
/*         if (strcmp(((AST_node *)(((AST_node *)$3)->first_child))->str, "FuncType")) */
/*         { */
/*             $$ = new_parent_node("FuncType", GROUP_4 + 2, 1, $3); */
/*             $$ = new_parent_node("Specifier", GROUP_8 + 6, 1, $$); */
/*         } */
/*         else */ 
/*         { */
/*             $$ = $3; */
/*         } */
/*     } */
/*     ; */
ID(402)
{
}

/* FuncDec */
/*     : LP VarList RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", GROUP_4 + 3, 2, $2, $5); } */
/*     | LP RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", GROUP_4 + 4, 1, $4); } */
/*     ; */
ID(403)
{
    if (childNum == 1)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->typeKind = FunctionType;
        type_info->node = (void *)malloc(sizeof(FunctionNode));
        child->other_info = type_info;
    }
    else if (childNum == 2)
    {
        /* 不需要额外的内存空间 */
    }
}
SD(403)
{
    D_parent_info;
    D_child_1_info;
    D_child_2_info;

    TypeInfo *returnTypeInfo;
    for (returnTypeInfo = child_1_info; 
         returnTypeInfo != NULL; 
         returnTypeInfo = (TypeInfo *)((FunctionNode *)returnTypeInfo->node)->returnTypeInfo)
    {
        assert(returnTypeInfo->typeKind == FunctionType);
    }
    returnTypeInfo = child_2_info;

    parent_info = child_1_info;
}

ID(404)
{
    if (childNum == 1)
    {
        /* 不需要额外的内存空间 */
    }
}
SD(404)
{
    D_parent_info;
    D_child_1_info;
    parent_info = child_1_info;
}

/* VarList */
/*     : ParamDec COMMA VarList { $$ = new_parent_node("VarList", GROUP_4 + 5, 2, $1, $3); } */
/*     | ParamDec { $$ = new_parent_node("VarList", GROUP_4 + 6, 1, $1); } */
/*     ; */
ID(405)
{
    if (childNum == 2)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->typeKind = FunctionType;
        type_info->node = (void *)malloc(sizeof(FunctionNode));
        child->other_info = type_info;
    }
}
SD(405)
{
    D_parent_info;
    D_child_1_info;
    D_child_2_info;

    assert(parent_info->typeKind == FunctionType);
    ((FunctionNode *)parent_info->node)->paramTypeInfo = child_1_info;
    ((FunctionNode *)parent_info->node)->returnTypeInfo = child_2_info;
}

SD(406)
{
    D_parent_info;
    D_child_1_info;

    assert(parent_info->typeKind == FunctionType);
    ((FunctionNode *)parent_info->node)->paramTypeInfo = child_1_info;
    ((FunctionNode *)parent_info->node)->returnTypeInfo = NULL;
}

/* ParamDec */
/*     : Specifier VarDec { $$ = new_parent_node("ParamDec", GROUP_4 + 7, 2, $1, $2); } */
/*     ; */
SD(407)
{
    D_parent_info;
    D_child_1_info;
    parent_info = child_1_info;
}

/* FuncBody */
/*     : FuncDec CompSt { $$ = new_parent_node("FuncBody", GROUP_4 + 8, 2, $1, $2); } */
/*     ; */
SD(408)
{
    D_parent_info;
    D_child_1_info;
    parent_info = child_1_info;
}

/* FuncCall */
/*     : Exp LP Args RP { $$ = new_parent_node("FuncCall", GROUP_4 + 9, 2, $1, $3); } */
/*     ; */
/* Args */
/*     : Exp COMMA Args { $$ = new_parent_node("Args", GROUP_4 + 10, 2, $1, $3); } */
/*     | PLACEHOLDER COMMA Args { $$ = new_parent_node("Args", GROUP_4 + 11, 2, $1, $3); } */
/*     | /1* empty *1/ { $$ = new_parent_node("Args", GROUP_4 + 12, 0); } */
/*     ; */
