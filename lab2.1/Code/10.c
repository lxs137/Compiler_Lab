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
/*     | VarDec { $$ = new_parent_node("Exp", GROUP_10 + 16, 1, $1); } */
/*     | INT { $$ = new_parent_node("Exp", GROUP_10 + 17, 1, $1); } */
/*     | FLOAT { $$ = new_parent_node("Exp", GROUP_10 + 18, 1, $1); } */
/*     | FuncBody { $$ = new_parent_node("Exp", GROUP_10 + 19, 1, $1); } */
/*     ; */
SD(1001)
{
    D_child_1;
    D_child_2;
    child_1->other_info = child_2->other_info;
}

SD(1016)
{
    D_parent_info;
    assert(parent_info != NULL);
    assert(parent_info->nextInfo == NULL);

    D_child_1;
    assert(child_1->other_info == NULL);
    child_1->other_info = parent_info;
    parent->other_info = NULL;

    /* D_child_1_info; */
    /* assert(child_1_info != NULL); */
    /* AST_node *anode = getASTNode((char *)child_1_info); */
    /* assert(anode != NULL); */
    /* assert(anode->other_info != NULL); */
    /* TypeInfo *info = (TypeInfo *)anode->other_info; */
    /* assert(info != NULL); */
    /* assert(info->typeKind != 0); */
    /* assert(info->node != NULL); */
    /* assert(info->nextInfo == NULL); */

    /* assert(parent->other_info == NULL); */
    /* parent->other_info = info; */

    /* D_child_1; */
    /* /1* 回收SD(906)分配的资源 *1/; */
    /* child_1->other_info = NULL; */

#ifdef exp_type_debug_print
    D_child_1_info;
    printTypeInfo(child_1_info);
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
#endif
}

void initActionTable10()
{
    SS(1001, 1016, 1019);
}
