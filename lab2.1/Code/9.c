#include "SDTAction.h"
#include "9.h"
#include <string.h>

/* Local Definitions */
/* VarDef */
/*     : Specifier DecList { $$ = new_parent_node("VarDef", GROUP_9 + 1, 2, $1, $2); } */
/*     | PatternMatching { $$ = new_parent_node("VarDef", GROUP_9 + 2, 1, $1); } */
/*     ; */
NID(901)
/* ID(901) */
/* { */
    if (childNum == 2)
    {
        D_child_1_info;
        assert(child_1_info != NULL);
        assert(child_1_info->typeKind != 0);
        assert(child_1_info->node != NULL);
        assert(child_1_info->nextInfo == NULL);

        /* assert(child->other_info == NULL); */
        /* /1* 分配的资源由SD(901)回收 *1/ */
        /* child->other_info = child_1_info; */
	Alloc(child->other_info, child_1_info);
    }
}
SD(901)
{
    D_child_1;
    assert(child_1->other_info != NULL);
    /* 回收SD(801)-SD(805)分配的资源 */
    child_1->other_info = NULL;

    D_child_2;
    assert(child_2->other_info != NULL);
    /* 回收ID(901)回收的资源 */
    child_2->other_info = NULL;
}

/* DecList */
/*     : Dec { $$ = new_parent_node("DecList", GROUP_9 + 3, 1, $1); } */
/*     | Dec COMMA DecList { $$ = new_parent_node("DecList", GROUP_9 + 4, 2, $1, $3); } */
/*     ; */
NID(903)
/* ID(903) */
/* { */
    if (childNum == 1)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(parent_info->typeKind != 0);
        assert(parent_info->node != NULL);
        assert(parent_info->nextInfo == NULL);

        /* assert(child->other_info == NULL); */
        /* /1* 分配的资源由SD(903)回收 *1/ */
        /* child->other_info = parent_info; */
	Alloc(child->other_info, parent_info);
    }
}
SD(903)
{
    D_child_1;
    assert(child_1->other_info != NULL);
    /* 回收由ID(903)分配的资源 */
    child_1->other_info = NULL;
}

NID(904)
/* ID(904) */
/* { */
    if (childNum == 1 | childNum == 2)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(parent_info->typeKind != 0);
        assert(parent_info->node != NULL);
        assert(parent_info->nextInfo == NULL);

        /* assert(child->other_info == NULL); */
        /* /1* 分配的资源由SD(904)回收 *1/ */
        /* child->other_info = parent_info; */
	Alloc(child->other_info, parent_info);
    }
}
SD(904)
{
    D_child_1;
    assert(child_1->other_info != NULL);
    /* 回收ID(904)分配的资源 */
    child_1->other_info = NULL;

    D_child_2;
    assert(child_2->other_info != NULL);
    /* 回收ID(904)分配的资源 */
    child_2->other_info = NULL;
}

/* Dec */
/*     : VarDec { $$ = new_parent_node("Dec", GROUP_9 + 5, 1, $1); } */
/*     | VarDec ASSIGNOP Exp { $$ = new_parent_node("Dec", GROUP_9 + 6, 2, $1, $3); } */
/*     ; */
NID(905)
/* ID(905) */
/* { */
    if (childNum == 1)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(parent_info->typeKind != 0);
        assert(parent_info->node != NULL);
        assert(parent_info->nextInfo == NULL);

        /* assert(child->other_info == NULL); */
        /* /1* 分配的资源不回收直到语法树销毁 *1/ */
        /* child->other_info = parent_info; */
	Alloc(child->other_info, parent_info);
    }
}
SD(905)
{
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)((TypeInfo *)child_1_info)->nextInfo, child_1);
#ifdef st_debug_print
    printf("add varDec: %s in symbol table. (SD(906))\n", (char *)((TypeInfo *)child_1_info)->nextInfo);
#endif
}

NID(906)
/* ID(906) */
/* { */
    if (childNum == 1)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(parent_info->typeKind != 0);
        assert(parent_info->node != NULL);
        assert(parent_info->nextInfo == NULL);

        /* assert(child->other_info == NULL); */
        /* /1* 分配的资源不回收直到语法树销毁 *1/ */
        /* child->other_info = parent_info; */
	Alloc(child->other_info, parent_info);
    }
}
SD(906)
{
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)((TypeInfo *)child_1_info)->nextInfo, child_1);

    if (child_1_info->typeKind == BuildInType && (intptr_t)child_1_info->node == Let)
    {
        TypeInfo *info = (TypeInfo *)malloc(sizeof(TypeInfo));
        D_child_2_info;
        char *c = (char *)((TypeInfo *)child_1_info)->nextInfo;
        memcpy(info, child_2_info, sizeof(TypeInfo));
        info->nextInfo = c;
        child_1->other_info = info;
    }

#ifdef st_debug_print
    printf("add varDec: %s in symbol table. (SD(906))\n", (char *)((TypeInfo *)child_1_info)->nextInfo);
#endif
}

/* Declarators */
/* VarDec */
/*     : LOWERID { $$ = new_parent_node("VarDec", GROUP_9 + 7, 1, $1); } */
/*     ; */
SD(907)
{
    D_parent_info;
    assert(parent_info != NULL);
    assert(parent_info->typeKind != 0);
    assert(parent_info->nextInfo == NULL);

    D_child_1;
    /* 分配的资源不回收直到语法树销毁 */
    /* parent_info->nextInfo = child_1->str + 4; */
    TypeInfo *info = (TypeInfo *)malloc(sizeof(TypeInfo));
    memcpy(info, parent_info, sizeof(TypeInfo));
    info->nextInfo = child_1->str + 4;
    parent->other_info = info;

#ifdef exp_type_debug_print
    printTypeInfo(parent_info);
    printf(" (VarDec: %s)", (char *)parent_info->nextInfo);
    printf(" (SD(907))\n");
#endif
}

/* Using Variables */
/* VarUse */
/*     : LOWERID { $$ = new_parent_node("VarUse", GROUP_9 + 8, 1, $1); } */
SD(908)
{
    D_child_1;
    parent->other_info = child_1->str + 4;
}

void initActionTable9()
{
    IS(901, 903, 904, 905, 906);
    SS(901, 903, 904, 905, 906, 907, 908);
}
