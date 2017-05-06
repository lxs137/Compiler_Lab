#include "SDTAction.h"
#include "10.h"

/* Expressions */
/* Exp */
/*     : Exp ASSIGNOP Exp {$$ = new_parent_node("Exp", GROUP_10 + 1, 2, $1, $3); } */
/*     | Exp RELOP Exp { $$ = new_parent_node("Exp", GROUP_10 + 2, 3, $1, $2, $3); } */
/*     | Exp AND Exp { $$ = new_parent_node("Exp", GROUP_10 + 3, 2, $1, $3); } */
/*     | Exp OR Exp { $$ = new_parent_node("Exp", GROUP_10 + 4, 2, $1, $3); } */
/*     | NOT Exp { $$ = new_parent_node("Exp", GROUP_10 + 5, 1, $2); } */
/*     | Exp PLUS Exp { $$ = new_parent_node("Exp", GROUP_10 + 6, 2, $1, $3); } */
/*     | Exp MINUS Exp { $$ = new_parent_node("Exp", GROUP_10 + 7, 2, $1, $3); } */
/*     | Exp STAR Exp { $$ = new_parent_node("Exp", GROUP_10 + 8, 2, $1, $3); } */
/*     | Exp DIV Exp { $$ = new_parent_node("Exp", GROUP_10 + 9, 2, $1, $3); } */
/*     | MINUS Exp { $$ = new_parent_node("Exp", GROUP_10 + 10, 1, $2); } */
/*     | LP Exp RP { $$ = new_parent_node("Exp", GROUP_10 + 11, 1, $2); } */
/*     | FuncCall { $$ = new_parent_node("Exp", GROUP_10 + 12, 1, $1); } */
/*     | REFER LP Exp RP { $$ = new_parent_node("Exp", GROUP_10 + 13, 2, $1, $3); } */
/*     | DEFER LP Exp RP { $$ = new_parent_node("Exp", GROUP_10 + 14, 2, $1, $3); } */
/*     | Exp DOT INT { $$ = new_parent_node("Exp", GROUP_10 + 15, 2, $1, $3); } */
/*     | VarUse { $$ = new_parent_node("Exp", GROUP_10 + 16, 1, $1); } */
/*     | INT { $$ = new_parent_node("Exp", GROUP_10 + 17, 1, $1); } */
/*     | FLOAT { $$ = new_parent_node("Exp", GROUP_10 + 18, 1, $1); } */
/*     | FuncBody { $$ = new_parent_node("Exp", GROUP_10 + 19, 1, $1); } */
/*     ; */
SD(1001)
{
    /* 默认类型推断从右到左 */
    D_child_2;
    D_child_1;
    assert(child_1->other_info == NULL);
    child_1->other_info = child_2->other_info;
    child_2->other_info = NULL;
}

SDS(1002, 1003, 1004, 1005)
{
    parent->other_info = (TypeInfo *)malloc(sizeof(TypeInfo));
    D_parent_info;
    parent_info->typeKind = BuildInType;
    parent_info->node = (void *)Int;
}

SDS(1006, 1007, 1008, 1009)
{
    parent->other_info = (TypeInfo *)malloc(sizeof(TypeInfo));
    D_parent_info;
    parent_info->typeKind = BuildInType;
    D_child_1_info;
    parent_info->node = child_1_info->node;
}

SD(1010)
{
    D_child_1_info;
    parent->other_info = child_1_info;
}

SD(1011)
{
    D_child_1_info;
    parent->other_info = child_1_info;
}

SD(1013)
{
    D_child_2_info;
    parent->other_info = (TypeInfo *)malloc(sizeof(TypeInfo));
    D_parent_info;
    parent_info->typeKind = ReferType;
    parent_info->node = (ReferNode *)malloc(sizeof(ReferNode));
    ((ReferNode *)parent_info->node)->referTo = child_2_info;
    parent_info->nextInfo = NULL;
}

SD(1014)
{
    D_child_2_info;
    parent->other_info = ((ReferNode *)child_2_info->node)->referTo;
}

SD(1016)
{
    D_child_1_info;
    assert(child_1_info != NULL);
    AST_node *anode = getASTNode((char *)child_1_info);
    assert(anode != NULL);
    TypeInfo *info = anode->other_info;
    assert(info != NULL);
    assert(info->typeKind != 0);
    void *node = info->node;
    assert(node != NULL);
    assert(info->nextInfo != NULL);
    parent->other_info = info;

#ifdef exp_type_debug_print
    D_parent_info;
    printTypeInfo(parent_info);
    printf(" (SD(1016))\n");
#endif
}

SD(1019)
{
    D_child_1_info;
    assert(child_1_info != NULL);
    assert(child_1_info->typeKind == FunctionType);
    FunctionNode *node = (FunctionNode *)child_1_info->node;
    assert(node != NULL);
    assert(node->returnTypeInfo != NULL);
    assert(child_1_info->nextInfo == NULL);

    assert(parent->other_info == NULL);
    parent->other_info = child_1_info;

    D_child_1;
    child_1->other_info = NULL;

#ifdef exp_type_debug_print
    D_parent_info;
    printTypeInfo(parent_info);
    printf(" (SD(1019))\n");
#endif
}

void initActionTable10()
{
    SS(1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1013, 1014, 1016, 1019);
}
