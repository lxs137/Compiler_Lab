/* TypeId作为整个ADT的名称，需要借给ADTParamList使用，同时继承到ADTHeader，方便借给ConstructorDecList使用 */
/* ConstructorDecList会把借来的TypeId借给它的子节点使用 */
/* ConstructorDecList在综合的时候已经不需要借来的TypeId信息，把这个域换成类型信息 */
/* 所以，一些确定的分配规则是不可能的，不要想了，实现起来代价也太大 */

#include "SDTAction.h"
#include "7.h"

/* ADT */
/* ADTDef */
/*     : ADTHeader %prec LOWER_THAN_ASSIGNOP SEMI { $$ = new_parent_node("ADTRef", GROUP_7 + 1, 1, $1); } */
/*     | ADTHeader ASSIGNOP ConstructorDecList { $$ = new_parent_node("ADTHeader", GROUP_7 + 2, 2, $1, $3); } */
/*     ; */
NSD(701)
    D_child_1;
    Dealloc(child_1->other_info);
END

NID(702)
    if (childNum == 2)
    {
        D_child_1_info;
        assert(child_1_info != NULL);

        assert(child->other_info == NULL);
	Alloc(child->other_info, child_1_info);
    }
END
NSD(702)
    D_child_1;
    Dealloc(child_1->other_info);

    D_child_2;
    Dealloc(child_2->other_info);
END

/* ADTHeader */
/*     : DATA TypeId ADTParamList { $$ = new_parent_node("ADTHeader", GROUP_7 + 3, 2, $2, $3); } */
/*     ; */
NID(703)
    if (childNum == 2)
    {
        D_child_1_info;
	Alloc(child->other_info, child_1_info);
    }
END
NSD(703)
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
#ifdef st_debug_print
    printf("add TypeId: %s in symbol table. (SD(703))\n", (char *)child_1_info);
#endif

    Alloc(parent->other_info, child_1_info);

    D_child_2;
    Dealloc(child_2->other_info);
END

/* ADTParamList */
/*     : ADTParam ADTParamList { $$ = new_parent_node("ADTParamList", GROUP_7 + 4, 2, $1, $2); } */
/*     | { $$ = new_parent_node("ADTParamList", GROUP_7 + 5, 0); } */
/*     ; */
NID(704)
    if (childNum ==  1 || childNum == 2)
    {
	Alloc(child->other_info, parent->other_info);
    }
END
NSD(704)
    D_child_1_info;
    D_child_1;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
#ifdef st_debug_print
    printf("add ADTParam: %s in symbol table. (SD(704))\n", (char *)child_1_info);
#endif

    Dealloc(child_1->other_info);

    D_child_2;
    Dealloc(child_2->other_info);
END

/* ADTParam */
/*     : LOWERID { $$ = new_parent_node("ADTParam", GROUP_7 + 6, 1, $1); } */
/*     ; */
NSD(706)
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
    /* parent->other_info = name; */
    OverWrite(parent->other_info, name);
END

/* ConstructorDecList */
/*     : ConstructorDec { $$ = new_parent_node("ConstructorDecList", GROUP_7 + 7, 1, $1); } */
/*     | ConstructorDec SEMI ConstructorDecList { $$ = new_parent_node("ConstructorDecList", GROUP_7 + 8, 2, $1, $3); } */ 
/*     ; */
NID(707)
    if (childNum == 1)
    {
        D_parent_info;
	Alloc(child->other_info, parent_info);
    }
END
NSD(707)
    D_child_1;
    Dealloc(child_1->other_info);
END

NID(708)
    if (childNum == 1 || childNum == 2)
    {
        D_parent_info;
	Alloc(child->other_info, parent_info);
    }
END
NSD(708)
    D_child_1;
    Dealloc(child_1->other_info);

    D_child_2;
    Dealloc(child_2->other_info);
END

/* ConstructorDec */
/*     : ConstructorId TypeIdList { $$ = new_parent_node("ConstructorDec", GROUP_7 + 9, 2, $1, $2); } */
/*     ; */
NID(709)
    if (childNum == 2)
    {
        D_parent_info;
	Alloc(child->other_info, parent_info);
    }
END
NSD(709)
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
    OverWrite(child_1->other_info, child_2_info);
    Alloc(((TypeInfo *)child_1->other_info)->nextInfo, str);
    Noalloc(((TypeInfo *)child_1->other_info)->nextInfo);
#ifdef type_debug_print
    printTypeInfo(child_1->other_info);
    printf(" (SD(709))\n");
#endif

    D_child_2;
    Dealloc(child_2->other_info);
END

/* ConstructorId */
/*     : UPPERID { $$ = new_parent_node("ConstructorId", GROUP_7 + 10, 1, $1); } */
/*     ; */
NSD(710)
    D_child_1;
    assert(parent->other_info == NULL);
    /* 分配的资源不回收直到语法树销毁 */
    allocPointer();
    noallocPointer();
    /* parent->other_info = (void *)(child_1->str + 4); */
    Alloc(parent->other_info, child_1->str + 4);
END

/* TypeIdList */
/*     : Specifier TypeIdList { $$ = new_parent_node("TypeIdList", GROUP_7 + 11, 2, $1, $2); } */
/*     | ADTParam TypeIdList { $$ = new_parent_node("TypeIdList", GROUP_7 + 12, 2, $1, $2); } */
/*     | SEMI { $$ = new_parent_node("TypeIdList", GROUP_7 + 13, 0); } */
/*     ; */
NID(711)
    if (childNum == 2)
    {
        D_parent_info;
	Alloc(child->other_info, parent_info);
    }
END
NSD(711)
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
    OverWrite(parent->other_info, info);

    D_child_2;
    Dealloc(child_2->other_info);
END

NID(712)
    if (childNum == 1 || childNum == 2)
    {
        D_parent_info;
	Alloc(child->other_info, parent_info);
    }
END
NSD(712)
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
	info->nextInfo = NULL;
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
    OverWrite(parent->other_info, info);

    D_child_2;
    Dealloc(child_2->other_info);
END

NSD(713)
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
    parent->other_info = info;
END

/* TypeId */ 
/*     : UPPERID { $$ = new_parent_node("TypeId", GROUP_7 + 14, 1, $1); } */
/*     ; */
NSD(714)
    D_child_1;
    Alloc(parent->other_info, child_1->str + 4);
    Noalloc(parent->other_info);
END

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
