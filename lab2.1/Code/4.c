#include "SDTAction.h"
#include "4.h"

/* FuncParamType */
/*     : Specifier DEDUCT FuncParamType { */ 
/*         $$ = new_parent_node("FuncType", GROUP_4 + 1, 2, $1, $3); */ 
/*         $$ = new_parent_node("Specifier", GROUP_8 + 6, 1, $$); */
/*     } */
/*     | Specifier { $$ = $1; } */
/*     ; */
/* 由于要兼容不同写法的函数类型 */
/* 真正的语法树稍有调整，不再有FuncParam这种节点 */
SD(401)
{
    D_child_1;
    D_child_2;
    D_child_1_info;
    D_child_2_info;

    assert(parent->other_info == NULL);
    /* type begin */
    D_type_info;
    type_info->typeKind = FunctionType;
    /* node begin */
    assert(child_1_info != NULL);
    assert(child_1_info->typeKind != 0);
    assert(child_1_info->node != NULL);
    assert(child_2_info != NULL);
    assert(child_2_info->typeKind != 0);
    assert(child_2_info->node != NULL);
    FunctionNode *node = (FunctionNode *)malloc(sizeof(FunctionNode));
    node->paramTypeInfo = child_1_info;
    node->returnTypeInfo = child_2_info;
    /* node end */
    type_info->node = node;
    type_info->nextInfo = NULL;
    /* type end */
    assert(parent->other_info == NULL);
    /* 类型信息不能删除，直到销毁语法树 */
    /* 故在销毁语法树时才回收 */
    parent->other_info = type_info;

#ifdef function_type_debug_print
    D_parent_info;
    printTypeInfo(parent_info);
    printf("\n");
#endif
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
/* 由于要兼容不同写法的函数类型 */
/* 真正的语法树稍有调整，不再有FuncParam这种节点 */
SD(402)
{
    /* type begin */
    D_type_info;
    type_info->typeKind = FunctionType;
    /* node begin */
    FunctionNode *node = (FunctionNode *)malloc(sizeof(FunctionNode));
    node->paramTypeInfo = NULL;
    D_child_1_info;
    assert(child_1_info != NULL);
    assert(child_1_info->typeKind != 0);
    assert(child_1_info->node != NULL);
    assert(child_1_info->nextInfo == NULL);
    node->returnTypeInfo = child_1_info;
    /* node end */
    type_info->node = node;
    type_info->nextInfo = NULL;
    /* type end */
    assert(parent->other_info == NULL);
    /* 类型信息不能删除，直到销毁语法树 */
    /* 故在销毁语法树时才回收 */
    parent->other_info = type_info;

#ifdef function_type_debug_print
    D_parent_info;
    printTypeInfo(parent_info);
    printf("\n");
#endif
}

/* FuncDec */
/*     : LP VarList RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", GROUP_4 + 3, 2, $2, $5); } */
/*     | LP RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", GROUP_4 + 4, 1, $4); } */
/*     ; */
ID(403)
{
    if (childNum == 0)
    {
        createInnerSymbolTable();
    }
    else if (childNum == 1)
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
    gotoOuterSymbolTable();

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
    if (childNum == 1)
    {
        /* ParamDec直接用其子节点的other_info就可以 */
        /* 不需要额外分配空间 */
    }
    else if (childNum == 2)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->typeKind = FunctionType;
        type_info->nextInfo = NULL;
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
    /* 不能确定传入参数的类型，也就是不能确定child_2_info->typeKind */
    assert(child_2_info->typeKind == FunctionType);
    ((FunctionNode *)parent_info->node)->paramTypeInfo = child_1_info;
    ((FunctionNode *)parent_info->node)->returnTypeInfo = child_2_info;
}

SD(406)
{
    D_parent_info;
    D_child_1_info;

    assert(parent_info->typeKind == FunctionType);
    ((FunctionNode *)parent_info->node)->paramTypeInfo = child_1_info;
    /* returnTypeInfo是整个函数的返回值，交给上层产生式填写 */
    /* 至此，形参列表的递归推导结束 */
    ((FunctionNode *)parent_info->node)->returnTypeInfo = NULL;
}

/* ParamDec */
/*     : Specifier VarDec { $$ = new_parent_node("ParamDec", GROUP_4 + 7, 2, $1, $2); } */
/*     ; */
SD(407)
{
    D_parent_info;
    D_child_1;
    D_child_1_info;
    D_child_2;
    D_child_2_info;
    parent_info = child_1_info;
    addSymbol((char *)child_2_info, child_2);
}

/* FuncBody */
/*     : FuncDec CompSt { $$ = new_parent_node("FuncBody", GROUP_4 + 8, 2, $1, $2); } */
/*     ; */
ID(408)
{
    if (childNum == 0)
    {
        createInnerSymbolTable();
    }
}
SD(408)
{
    gotoOuterSymbolTable();
    D_parent_info;
    D_child_1_info;
    parent_info = child_1_info;
}

/* Specifier */
/*     : BUILDINTYPE { $$ = new_parent_node("Specifier", GROUP_8 + 1, 1, $1); } */
/*     | LET { $$ = new_parent_node("Specifier", GROUP_8 + 2, 1, $1); } */
/*     | TypeId { $$ = new_parent_node("Specifier", GROUP_8 + 3, 1, $1); } */
/*     | ArrayType { $$ = new_parent_node("Specifier", GROUP_8 + 4, 1, $1); } */
/*     | ReferType { $$ = new_parent_node("Specifier", GROUP_8 + 5, 1, $1); } */
/*     | FuncType { $$ = $1; } */
/*     ; */
/* IDS(801, 802) */
/* { */
/*     if (childNum == 1) */
/*     { */
/*         TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo)); */
/*         type_info->typeKind = BuildInType; */
/*         /1* 内建类型没有对应的节点类型，直接用node域标记 *1/ */
/*         /1* 故不需要分配空间 *1/ */
/*         type_info->nextInfo = NULL; */
/*     } */
/* } */
ID(803)
{
    if (childNum == 1)
    {
        /* TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo)); */
        /* type_info->typeKind = AlgebraicDataType; */
        /* type_info->node = (void *)malloc(sizeof(AlgebraicDataTypeNode)); */
        /* type_info->nextInfo = NULL; */
        /* child->other_info = type_info; */
    }
}
ID(804)
{
    if (childNum == 1)
    {
        /* TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo)); */
        /* type_info->typeKind = ArrayType; */
        /* type_info->node = (void *)malloc(sizeof(ArrayNode)); */
        /* type_info->nextInfo = NULL; */
        /* child->other_info = type_info; */
    }
}
ID(805)
{
    if (childNum == 1)
    {
        /* TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo)); */
        /* type_info->typeKind = ReferType; */
        /* type_info->node = (void *)malloc(sizeof(ReferNode)); */
        /* type_info->nextInfo = NULL; */
        /* child->other_info = type_info; */
    }
}
ID(806)
{
    if (childNum == 1)
    {
        /* TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo)); */
        /* type_info->typeKind = FunctionType; */
        /* type_info->node = (void *)malloc(sizeof(FunctionNode)); */
        /* type_info->nextInfo = NULL; */
        /* child->other_info = type_info; */
    }
}
/* SDS(801, 802, 803, 804, 805, 806) */
/* { */
/*     D_parent_info; */
/*     D_child_1_info; */
/*     parent_info = child_1_info; */
/* } */

/* FuncCall */
/*     : Exp LP RP { $$ = new_parent_node("FuncCall", GROUP_4 + 9, 1, $1); } */
/*     | Exp LP Args RP { $$ = new_parent_node("FuncCall", GROUP_4 + 10, 2, $1, $3); } */
/*     ; */
/* Args */
/*     : Exp COMMA Args { $$ = new_parent_node("Args", GROUP_4 + 11, 2, $1, $3); } */
/*     | PLACEHOLDER COMMA Args { $$ = new_parent_node("Args", GROUP_4 + 12, 2, $1, $3); } */
/*     | Exp { $$ = new_parent_node("Args", GROUP_4 + 13, 0); } */
/*     ; */

void initActionTable4()
{
    /* IS(408); */
    /* registerIAction(408, pro408IAction); */
    /* SS(401, 407, 408); */
    IS(403, 408);
    SS(401, 402, 403, 407, 408);
    /* registerSAction(408, pro408SAction); */
    /* registerSAction(407, pro407SAction); */
}
