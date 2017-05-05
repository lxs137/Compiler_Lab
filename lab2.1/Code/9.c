#include "SDTAction.h"
#include "9.h"

/* Local Definitions */
/* VarDef */
/*     : Specifier DecList { $$ = new_parent_node("VarDef", GROUP_9 + 1, 2, $1, $2); } */
/*     | PatternMatching { $$ = new_parent_node("VarDef", GROUP_9 + 2, 1, $1); } */
/*     ; */
ID(901)
{
    if (childNum == 2)
    {
        D_child_1_info;
        assert(child_1_info != NULL);
        assert(child_1_info->typeKind != 0);
        assert(child_1_info->node != NULL);
        assert(child_1_info->nextInfo == NULL);

        assert(child->other_info == NULL);
        child->other_info = child_1_info;

        D_child_1;
        child_1->other_info = NULL;

#ifdef exp_type_debug_print
        D_child_2_info;
        printTypeInfo(child_2_info);
        printf("(ID(901))\n");
#endif
    }
}

/* DecList */
/*     : Dec { $$ = new_parent_node("DecList", GROUP_9 + 3, 1, $1); } */
/*     | Dec COMMA DecList { $$ = new_parent_node("DecList", GROUP_9 + 4, 2, $1, $3); } */
/*     ; */
ID(903)
{
    if (childNum == 1)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(parent_info->typeKind != 0);
        assert(parent_info->node != NULL);
        assert(parent_info->nextInfo == NULL);

        assert(child->other_info == NULL);
        child->other_info = parent_info;

        parent->other_info = NULL;

#ifdef exp_type_debug_print
        D_child_info;
        printTypeInfo(child_info);
        printf("(ID(903))\n");
#endif
    }
}

ID(904)
{
    if (childNum == 1 | childNum == 2)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(parent_info->typeKind != 0);
        assert(parent_info->node != NULL);
        assert(parent_info->nextInfo == NULL);

        assert(child->other_info == NULL);
        child->other_info = parent_info;

#ifdef exp_type_debug_print
        D_child_info;
        printTypeInfo(child_info);
        printf("(ID(904))\n");
#endif
    }

    if (childNum == 2)
    {
        parent->other_info = NULL;
    }
}

/* Dec */
/*     : VarDec { $$ = new_parent_node("Dec", GROUP_9 + 5, 1, $1); } */
/*     | VarDec ASSIGNOP Exp { $$ = new_parent_node("Dec", GROUP_9 + 6, 2, $1, $3); } */
/*     ; */
ID(905)
{
    if (childNum == 1)
    {
        D_parent_info;
        child->other_info = parent_info;
    }
}
SD(905)
{
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
    /* 回收SD(906)分配的资源 */;
    child_1->other_info = NULL;
}

SD(906)
{
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
    /* 回收SD(906)分配的资源 */;
    child_1->other_info = NULL;
}

/* Declarators */
/* VarDec */
/*     : LOWERID { $$ = new_parent_node("VarDec", GROUP_9 + 7, 1, $1); } */
/*     ; */
SD(907)
{
    D_child_1;
    /* assert(parent->other_info == NULL); */
    /* 分配的资源由SD(904) / SD(905) / SD(1016)回收 */
    /* parent->other_info = child_1->str + 4; */
    ((TypeInfo *)parent->other_info)->nextInfo = child_1->str + 4;
}

void initActionTable9()
{
    IS(901, 903, 904, 905);
    SS(905, 906, 907);
}

/* Using Variables */
/* VarUse */
/*     : LOWERID { $$ = new_parent_node("VarUse", GROUP_9 + 8, 1, $1); } */
