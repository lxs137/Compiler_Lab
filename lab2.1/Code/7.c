#include "SDTAction.h"
#include "7.h"

/* ADT */
/* ADTDef */
/*     : ADTHeader %prec LOWER_THAN_ASSIGNOP SEMI { $$ = new_parent_node("ADTRef", GROUP_7 + 1, 1, $1); } */
/*     | ADTHeader ASSIGNOP ConstructorDecList { $$ = new_parent_node("ADTHeader", GROUP_7 + 2, 2, $1, $3); } */
/*     ; */
SD(701)
{
    /* 回收SD(703)分配的资源 */
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    /* 断言没有其他资源需要回收 */
    /* child_1_info是char *类型，不可能有nextInfo */
    /* assert(child_1_info->nextInfo == NULL); */
    deallocPointer();
    /* child_1->other_info = NULL; */
    int proNum = 701;
    Dealloc(child_1->other_info);
}

ID(702)
{
    if (childNum == 2)
    {
        D_child_1_info;
        /* child_1_info存储的是整个ADT的类型名：如Maybe */
        assert(child_1_info != NULL);

        assert(child->other_info == NULL);
        /* 分配的资源都SD(702)回收 */
	allocPointer();
        /* child->other_info = child_1_info; */
	int proNum = 702;
	Alloc(child->other_info, child_1_info);
    }
}
SD(702)
{
    int proNum = 702;

    /* 回收SD(703)分配的资源 */
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    deallocPointer();
    /* child_1->other_info = NULL; */
    Dealloc(child_1->other_info);

    /* 回收ID(702)分配的资源 */
    D_child_2;
    D_child_2_info;
    assert(child_2_info != NULL);
    deallocPointer();
    /* child_2->other_info = NULL; */
    Dealloc(child_2->other_info);
}

/* ADTHeader */
/*     : DATA TypeId ADTParamList { $$ = new_parent_node("ADTHeader", GROUP_7 + 3, 2, $2, $3); } */
/*     ; */
ID(703)
{
    int proNum = 703;
    if (childNum == 2)
    {
        D_child_1_info;
        assert(child_1_info != NULL);
        assert(child->other_info == NULL);
        /* 分配的资源由SD(703)回收 */
	allocPointer();
        /* child->other_info = child_1_info; */
	Alloc(child->other_info, child_1_info);
    }
}
SD(703)
{
    int proNum = 703;

    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
#ifdef st_debug_print
    printf("add TypeId: %s in symbol table. (SD(703))\n", (char *)child_1_info);
#endif

    assert(parent->other_info == NULL);
    /* 分配的资源由SD(701) / SD(702)回收 */
    /* 分配的资源是ADT的类型名称，如Maybe */
    allocPointer();
    /* parent->other_info = child_1_info; */
    Alloc(parent->other_info, child_1_info);

    /* /1* 回收SD(714)分配的资源 *1/ */
    /* deallocPointer(); */
    /* child_1->other_info = NULL; */

    /* 回收ID(703)分配的资源 */
    D_child_2;
    assert(child_2->other_info != NULL);
    deallocPointer();
    /* child_2->other_info = NULL; */
    Dealloc(child_2->other_info);
    assert(child_2->other_info == NULL);
}

/* ADTParamList */
/*     : ADTParam ADTParamList { $$ = new_parent_node("ADTParamList", GROUP_7 + 4, 2, $1, $2); } */
/*     | { $$ = new_parent_node("ADTParamList", GROUP_7 + 5, 0); } */
/*     ; */
ID(704)
{
    if (childNum ==  1 || childNum == 2)
    {
        assert(parent->other_info != NULL);
        assert(child->other_info == NULL);
        /* 分配的资源由SD(704)回收 */
	allocPointer();
        /* child->other_info = parent->other_info; */
	Alloc(child->other_info, parent->other_info);
    }
}
SD(704)
{
    int proNum = 704;
    D_child_1_info;
    D_child_1;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
#ifdef st_debug_print
    printf("add ADTParam: %s in symbol table. (SD(704))\n", (char *)child_1_info);
#endif

    /* 回收ID(704)分配的资源 */
    deallocPointer();
    /* child_1->other_info = NULL; */
    Dealloc(child_1->other_info);
    assert(child_1->other_info == NULL);

    /* 回收ID(704)分配的资源 */
    D_child_2;
    D_child_2_info;
    assert(child_2_info != NULL);
    deallocPointer();
    child_2->other_info = NULL;
}

/* ADTParam */
/*     : LOWERID { $$ = new_parent_node("ADTParam", GROUP_7 + 6, 1, $1); } */
/*     ; */
SD(706)
{
    D_parent_info;
    D_child_1;
    /* TypeId-ADTParam\0 */
    assert(parent_info != NULL);
    int part1 = strlen((char *)parent_info);
    int part2 = strlen(child_1->str + 4);
    char *name = malloc((part1 + 1 + part2 + 1) * sizeof(char));
    strcpy(name, (char *)parent_info);
    name[part1] = '-';
    strcpy(name + part1 + 1, child_1->str + 4);
    /* parent->other_info由继承属性变为综合属性 */
    parent->other_info = name;
}

/* ConstructorDecList */
/*     : ConstructorDec { $$ = new_parent_node("ConstructorDecList", GROUP_7 + 7, 1, $1); } */
/*     | ConstructorDec SEMI ConstructorDecList { $$ = new_parent_node("ConstructorDecList", GROUP_7 + 8, 2, $1, $3); } */ 
/*     ; */
ID(707)
{
    int proNum = 707;
    if (childNum == 1)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(child->other_info == NULL);
        /* 分配的资源由SD(707)回收 */
	allocPointer();
        /* child->other_info = parent_info; */
	Alloc(child->other_info, parent_info);
    }
}
SD(707)
{
    D_child_1;
    D_child_1_info;
    /* 回收ID(707)分配的资源 */
    assert(child_1_info != NULL);
    deallocPointer();
    child_1->other_info = NULL;
}

ID(708)
{
    if (childNum == 1 || childNum == 2)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(child->other_info == NULL);
        /* 分配的资源由SD(708)回收 */
	allocPointer();
        child->other_info = parent_info;
    }
}
SD(708)
{
    D_child_1;
    D_child_2;
    assert(child_1->other_info != NULL);
    /* 回收ID(708)分配的资源 */
    deallocPointer();
    child_1->other_info = NULL;
    assert(child_2->other_info != NULL);
    /* 回收ID(708)分配的资源 */
    deallocPointer();
    child_2->other_info = NULL;
}

/* ConstructorDec */
/*     : ConstructorId TypeIdList { $$ = new_parent_node("ConstructorDec", GROUP_7 + 9, 2, $1, $2); } */
/*     ; */
ID(709)
{
    if (childNum == 2)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(child->other_info == NULL);
        /* 分配的资源由SD(709)回收 */
	allocPointer();
        child->other_info = parent_info;
    }
}
SD(709)
{
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
#ifdef st_debug_print
    printf("add ConstructorId: %s in symbol table. (SD(709))\n", (char *)child_1_info);
#endif

    void *str = child_1_info;
    D_child_2_info;
    assert(child_2_info != NULL);
    assert(child_2_info->typeKind == FunctionType);
    assert(child_2_info->node != NULL);
    /* assert(child_2_info->nextInfo != NULL); */
    child_1->other_info = child_2_info;
    /* 分配的资源不回收直到语法树销毁 */
    allocPointer();
    noallocPointer();
    ((TypeInfo *)child_1->other_info)->nextInfo = str;
#ifdef type_debug_print
    printTypeInfo(child_1->other_info);
    printf(" (SD(709))\n");
#endif

    /* 回收SD(710)分配的资源 */
    deallocPointer();
    child_1->other_info = NULL;

    D_child_2;
    assert(child_2->other_info != NULL);
    /* 回收ID(709)分配的资源 */
    deallocPointer();
    child_2->other_info = NULL;
}

/* ConstructorId */
/*     : UPPERID { $$ = new_parent_node("ConstructorId", GROUP_7 + 10, 1, $1); } */
/*     ; */
SD(710)
{
    D_child_1;
    assert(parent->other_info == NULL);
    /* 分配的资源不回收直到语法树销毁 */
    allocPointer();
    noallocPointer();
    parent->other_info = (void *)(child_1->str + 4);
}

/* TypeIdList */
/*     : Specifier TypeIdList { $$ = new_parent_node("TypeIdList", GROUP_7 + 11, 2, $1, $2); } */
/*     | ADTParam TypeIdList { $$ = new_parent_node("TypeIdList", GROUP_7 + 12, 2, $1, $2); } */
/*     | SEMI { $$ = new_parent_node("TypeIdList", GROUP_7 + 13, 0); } */
/*     ; */
ID(711)
{
    if (childNum == 2)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(child->other_info == NULL);
        /* 分配的资源由SD(711)回收 */
	allocPointer();
        child->other_info = parent_info;
    }
}
SD(711)
{
    D_child_1_info;
    D_child_2_info;
    TypeInfo *info;
    if (((FunctionNode *)child_2_info->node)->paramTypeInfo == NULL)
    {
        ((FunctionNode *)child_2_info->node)->paramTypeInfo = child_1_info;
	info = child_2_info;
    }
    else
    {
        info = malloc(sizeof(TypeInfo));
        info->typeKind = FunctionType;
        FunctionNode *node = malloc(sizeof(FunctionNode));
        node->paramTypeInfo = child_1_info;
        node->returnTypeInfo = child_2_info;
        info->node = node;
        info->nextInfo = NULL;
    }
    void *str = parent->other_info;
    /* 分配的资源由SD(711)回收 */
    allocPointer();
    parent->other_info = info;
    D_parent_info;
    parent_info->nextInfo = str;

    /* 回收ID(711)分配的资源 */
    assert(child_2_info != NULL);
    assert(child_2_info->nextInfo != NULL);
    deallocPointer();
    child_2_info->nextInfo = NULL;

    /* 回收SD(711) / SD(712) / SD(713)分配的资源 */
    D_child_2;
    deallocPointer();
    child_2->other_info = NULL;
}

ID(712)
{
    if (childNum == 1 || childNum == 2)
    {
        D_parent_info;
        assert(parent_info != NULL);
        assert(child->other_info == NULL);
        /* 分配的资源由SD(712)回收 */
        child->other_info = parent_info;
    }
}
SD(712)
{
    D_child_1_info;
    TypeInfo *i = (TypeInfo *)malloc(sizeof(TypeInfo));
    i->typeKind = GenericType;
    GenericTypeNode *n = (GenericTypeNode *)malloc(sizeof(GenericTypeNode));
    n->genericTypeName = (char *)child_1_info;
    i->node = n;
    i->nextInfo = NULL;

    D_child_2_info;
    TypeInfo *info;
    if (((FunctionNode *)child_2_info->node)->paramTypeInfo == NULL)
    {
        ((FunctionNode *)child_2_info->node)->paramTypeInfo = i;
	info = child_2_info;
    }
    else
    {
        info = malloc(sizeof(TypeInfo));
        info->typeKind = FunctionType;
        FunctionNode *node = malloc(sizeof(FunctionNode));
        node->paramTypeInfo = i;
        node->returnTypeInfo = child_2_info;
        info->node = node;
        info->nextInfo = NULL;
    }
    void *str = parent->other_info;
    /* 分配的资源由SD(711)回收 */
    allocPointer();
    parent->other_info = info;
    D_parent_info;
    parent_info->nextInfo = str;

    /* 回收ID(711)分配的资源 */
    assert(child_2_info != NULL);
    assert(child_2_info->nextInfo != NULL);
    deallocPointer();
    child_2_info->nextInfo = NULL;

    /* 回收SD(711) / SD(712) / SD(713)分配的资源 */
    D_child_2;
    deallocPointer();
    child_2->other_info = NULL;
}

SD(713)
{
    /* info begin */
    TypeInfo *info = (TypeInfo *)malloc(sizeof(TypeInfo));
    /* node begin */
    FunctionNode *node = (FunctionNode *)malloc(sizeof(FunctionNode));
    node->paramTypeInfo = NULL;
    /* returnTypeInfo begin */
    TypeInfo *returnTypeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
    returnTypeInfo->typeKind = AlgebraicDataType;
    returnTypeInfo->node = (TypeInfo *)malloc(sizeof(AlgebraicDataTypeNode));
    D_parent_info;
    ((AlgebraicDataTypeNode *)returnTypeInfo->node)->typeIdName = (char *)parent_info;
    returnTypeInfo->nextInfo = NULL;
    /* returnTypeInfo end */
    node->returnTypeInfo = returnTypeInfo;
    /* node end */
    info->typeKind = FunctionType;
    info->node = node;
    info->nextInfo = NULL;
    /* info end */

    void *str = parent_info;
    assert(str != NULL);
    allocPointer();
    /* 分配的资源由SD(711) / SD(712)回收 */
    parent->other_info = info;
    ((TypeInfo *)parent->other_info)->nextInfo = str;
}

/* TypeId */
/*     : UPPERID { $$ = new_parent_node("TypeId", GROUP_7 + 14, 1, $1); } */
/*     ; */
SD(714)
{
    D_child_1;
    /* 把名字继承到父亲 */
    assert(parent->other_info == NULL);
    /* parent->other_info = child_1->str + 4; */
    int proNum = 714;
    Alloc(parent->other_info, child_1->str + 4);
}

/* pattern matching */
/* PatternMatching */
/*     : LET LP ConstructorId PatternMatchingParamList RP ASSIGNOP VarDec { */ 
/*         $$ = new_parent_node("PatternMatching", GROUP_7 + 15, 3, $3, $4, $7); */ 
/*     } */
/*     ; */
/* PatternMatchingParamList */
/*     : LOWERID PatternMatchingParamList { */ 
/*         $$ = new_parent_node("PatternMatchingParamList", GROUP_7 + 16, 2, $1, $2); */
/*     } */
/*     | PLACEHOLDER PatternMatchingParamList { */ 
/*         $$ = new_parent_node("PatternMatchingParamList", GROUP_7 + 17, 2, $1, $2); */ 
/*     } */
/*     | /1* empty *1/ { $$ = new_parent_node("PatternMatchingParamList", GROUP_7 + 18, 0); } */
/*     ; */

void initActionTable7()
{
    IS(702, 703, 704, 707, 708, 709, 711, 712);
    SS(701, 702, 703, 704, 706, 707, 708, 709, 710, 711, 712, 713, 714);
}
