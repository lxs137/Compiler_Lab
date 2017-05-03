#include "SDTAction.h"
#include "8.h"

/* Specifiers */
/* Specifier */
/*     : BUILDINTYPE { $$ = new_parent_node("Specifier", GROUP_8 + 1, 1, $1); } */
/*     | LET { $$ = new_parent_node("Specifier", GROUP_8 + 2, 1, $1); } */
/*     | TypeId { $$ = new_parent_node("Specifier", GROUP_8 + 3, 1, $1); } */
/*     | ArrayType { $$ = new_parent_node("Specifier", GROUP_8 + 4, 1, $1); } */
/*     | ReferType { $$ = new_parent_node("Specifier", GROUP_8 + 5, 1, $1); } */
/*     | FuncType { $$ = $1; } */
/*     ; */

SD(801)
{
    D_child_1;

    assert(parent->other_info == NULL);
    D_type_info;
    parent->other_info = type_info;
    D_parent_info;

    parent_info->typeKind = BuildInType;
    if (!strcmp(child_1->str + 4, "Int"))
    {
        parent_info->node = (void *)Int;
    }
    else
    {
        parent_info->node = (void *)Float;
    }
    parent_info->nextInfo = NULL;
}

SD(802)
{
    assert(parent->other_info == NULL);
    D_type_info;
    parent->other_info = type_info;
    D_parent_info;

    parent_info->typeKind = BuildInType;
    parent_info->node = (void *)Let;
    parent_info->nextInfo = NULL;
}

SD(803)
{
    D_child_1;

    assert(parent->other_info == NULL);
    D_type_info;
    parent->other_info = type_info;
    D_parent_info;

    parent_info->typeKind = AlgebraicDataType;
    AlgebraicDataTypeNode *node = (AlgebraicDataTypeNode *)malloc(sizeof(AlgebraicDataTypeNode));
    node->typeIdName = child_1 ->str + 4;
    node->constructors = NULL;
    parent_info->node = node;
    parent_info->nextInfo = NULL;
}

SD(804)
{
    D_child_1_info;
    assert(child_1_info->typeKind == ArrayType);
    ArrayNode *node = (ArrayNode *)child_1_info->node;
    assert(node != NULL);
    assert(node->arrayTo != NULL);
    assert(node->width > 0);
    assert(child_1_info->nextInfo == NULL);
    
    assert(parent->other_info == NULL);
    parent->other_info = child_1_info;
}

SD(805)
{
    D_child_1_info;
    assert(child_1_info->typeKind == ReferType);
    ReferNode *node = (ReferNode *)child_1_info->node;
    assert(node != NULL);
    assert(node->referTo != NULL);
    assert(child_1_info->nextInfo == NULL);
    
    assert(parent->other_info == NULL);
    parent->other_info = child_1_info;
}

SD(806)
{
    D_child_1_info;
    assert(child_1_info->typeKind == FunctionType);
    FunctionNode *node = (FunctionNode *)child_1_info->node;
    assert(node != NULL);
    assert(node->returnTypeInfo!= NULL);
    assert(child_1_info->nextInfo == NULL);

    assert(parent->other_info == NULL);
    parent->other_info = child_1_info;
}

void initActionTable8()
{
    SS(801, 802, 803, 804, 805, 806);
}
