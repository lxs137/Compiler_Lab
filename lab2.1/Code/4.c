#include "SDTAction.h"
#include "symbol_table.h"
#include "9.h"

/* FuncParamType */
/*     : Specifier DEDUCT FuncParamType { */ 
/*         $$ = new_parent_node("FuncType", GROUP_4 + 1, 2, $1, $3); */ 
/*         $$ = new_parent_node("Specifier", GROUP_8 + 6, 1, $$); */
/*     } */
/*     | Specifier { $$ = $1; } */
/*     ; */
ID(401)
{
    if (childNum == 2)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->typeKind = FunctionType;
        type_info->node = (void *)malloc(sizeof(FunctionNode));
        child->other_info = type_info;
    }
}
SD(401)
{
    D_parent_info;
    D_child_1_info;
    D_child_2_info;

    assert(parent_info->typeKind == FunctionType);
    assert(child_2_info->typeKind == FunctionType);
    ((FunctionNode *)parent_info->node)->paramTypeInfo = child_1_info;
    ((FunctionNode *)parent_info->node)->returnTypeInfo = child_2_info;
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
    if (childNum == 1)
    {
        /* 402号产生式只有一个子节点：Specifier */
        /* 不需要为它分配空间 */
    }
}

void initActionTable4()
{
}
