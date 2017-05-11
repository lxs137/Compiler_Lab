#include "SDTAction.h"
#include "Assert.h"
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
NSD(401)
    D_child_1;
    D_child_2;
    D_child_1_info;
    D_child_2_info;

    assert(parent->other_info == NULL);
    /* type begin */
    D_type_info;
    type_info->typeKind = FunctionType;
    /* node begin */
    AssertTypeInfo(child_1_info);
    AssertTypeInfo(child_2_info);
    FunctionNode *node = (FunctionNode *)malloc(sizeof(FunctionNode));
    node->paramTypeInfo = child_1_info;
    node->returnTypeInfo = child_2_info;
    /* node end */
    type_info->node = node;
    type_info->nextInfo = NULL;
    /* type end */

    Alloc(parent->other_info, type_info);
    Noalloc(parent->other_info);

#ifdef function_type_debug_print
    D_parent_info;
    printTypeInfo(parent_info);
    printf("\n");
#endif
END

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
/* SD(402) */
/* { */
NSD(402)
    /* type begin */
    D_type_info;
    type_info->typeKind = FunctionType;
    /* node begin */
    FunctionNode *node = (FunctionNode *)malloc(sizeof(FunctionNode));
    node->paramTypeInfo = NULL;
    D_child_1_info;
    /* assert(child_1_info != NULL); */
    /* assert(child_1_info->typeKind != 0); */
    /* assert(child_1_info->node != NULL); */
    AssertTypeInfo(child_1_info);
    assert(child_1_info->nextInfo == NULL);
    node->returnTypeInfo = child_1_info;
    /* node end */
    type_info->node = node;
    type_info->nextInfo = NULL;
    /* type end */

    Alloc(parent->other_info, type_info);
    Noalloc(parent->other_info);

#ifdef function_type_debug_print
    D_parent_info;
    printTypeInfo(parent_info);
    printf("\n");
#endif
END

/* FuncDec */
/*     : LP VarList RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", GROUP_4 + 3, 2, $2, $5); } */
/*     | LP RP DEDUCT Specifier { $$ = new_parent_node("FuncDec", GROUP_4 + 4, 1, $4); } */
/*     ; */
NSD(403)
    D_child_1_info;

    TypeInfo *returnTypeInfo = child_1_info;
    assert(returnTypeInfo != NULL);
    TypeInfo *n = (TypeInfo *)((FunctionNode *)returnTypeInfo->node)->returnTypeInfo;
    for (; n != NULL; 
         returnTypeInfo = n, n = (TypeInfo *)((FunctionNode *)n->node)->returnTypeInfo)
    {
	AssertFunctionTypeInfo(returnTypeInfo);
        assert(returnTypeInfo->nextInfo == NULL);
    }

    D_child_2_info;
    AssertTypeInfo(child_2_info);
    assert(child_2_info->nextInfo == NULL);
    ((FunctionNode *)(returnTypeInfo->node))->returnTypeInfo = child_2_info;

    Alloc(parent->other_info, child_1_info);

    D_child_1;
    Dealloc(child_1->other_info);
END

NSD(404)
    /* type begin */
    D_type_info;
    type_info->typeKind = FunctionType;
    /* node begin */
    FunctionNode *node = (FunctionNode *)malloc(sizeof(FunctionNode));
    node->paramTypeInfo = NULL;
    D_child_1_info;
    AssertTypeInfo(child_1_info);
    assert(child_1_info->nextInfo == NULL);
    node->returnTypeInfo = child_1_info;
    /* node end */
    type_info->node = node;
    type_info->nextInfo = NULL;
    /* type end */

    Alloc(parent->other_info, type_info);
END

/* VarList */
/*     : ParamDec COMMA VarList { $$ = new_parent_node("VarList", GROUP_4 + 5, 2, $1, $3); } */
/*     | ParamDec { $$ = new_parent_node("VarList", GROUP_4 + 6, 1, $1); } */
/*     ; */
NSD(405)
    D_child_1_info;
    /* assert(child_1_info != NULL); */
    /* assert(child_1_info->typeKind != 0); */
    AssertTypeInfo(child_1_info);
    /* assert(child_1_info->nextInfo == NULL); */

    D_child_2_info;
    /* assert(child_2_info != NULL); */
    /* assert(child_2_info->typeKind == FunctionType); */
    AssertFunctionTypeInfo(child_2_info);
    FunctionNode *node = (FunctionNode *)child_2_info->node;
    assert(node != NULL);
    assert(node->paramTypeInfo != NULL);
    /* 不好进行判断，两种情况都有可能 */
    /* assert(node->returnTypeInfo == NULL); */
    assert(child_2_info->nextInfo == NULL);

    /* type begin */
    D_type_info;
    type_info->typeKind = FunctionType;
    /* node begin */
    FunctionNode *fnode = (FunctionNode *)malloc(sizeof(FunctionNode));
    fnode->paramTypeInfo = child_1_info;
    fnode->returnTypeInfo = child_2_info;
    /* node end */
    type_info->node = fnode;
    type_info->nextInfo = NULL;
    /* type end */

    Alloc(parent->other_info, type_info);

    D_child_1;
    Dealloc(child_1->other_info);
END

NSD(406)
    D_parent_info;

    D_child_1_info;
    /* assert(child_1_info != NULL); */
    /* assert(child_1_info->typeKind != 0); */
    /* assert(child_1_info->node != NULL); */
    AssertTypeInfo(child_1_info);
    /* assert(child_1_info->nextInfo == NULL); */

    /* type begin */
    D_type_info;
    type_info->typeKind = FunctionType;
    /* node begin */
    FunctionNode *node = (FunctionNode *)malloc(sizeof(FunctionNode));
    node->paramTypeInfo = child_1_info;
    /* returnTypeInfo是整个函数的返回值，交给上层产生式填写 */
    /* 至此，形参列表的递归推导结束 */
    node->returnTypeInfo = NULL;
    /* node end */
    type_info->node = node;
    type_info->nextInfo = NULL;
    /* type end */

    Alloc(parent->other_info, type_info);

    D_child_1;
    Dealloc(child_1->other_info);
END

/* ParamDec */
/*     : Specifier VarDec { $$ = new_parent_node("ParamDec", GROUP_4 + 7, 2, $1, $2); } */
/*     ; */
NID(407)
    if (childNum == 2)
    {
        D_child_1_info;
        assert(child_1_info != NULL);
        assert(child_1_info->node != NULL);
        assert(child_1_info->nextInfo == NULL);

	Alloc(child->other_info, child_1_info);
	/* Noalloc(child->other_info); */
    }
END
NSD(407)
    D_child_1_info;
    /* assert(child_1_info != NULL); */
    /* assert(child_1_info->typeKind != 0); */
    /* assert(child_1_info->node !=  NULL); */
    AssertTypeInfo(child_1_info);
    /* 由于Specifer->other_info与VarDec->other_info共享同一块内存 */
    /* 所以当VarDec->other_in->nextInfofo被赋予变量名称时，Specifier->other_info->nextInfo也不再为空 */
    Alloc(parent->other_info, child_1_info);

    D_child_2;
    D_child_2_info;
    assert(child_2_info != NULL);
    addSymbol((char *)((TypeInfo *)child_2_info)->nextInfo, child_2);
#ifdef st_debug_print
    printf("add VarDec: %s in symbol table. (SD(407))\n", (char *)((TypeInfo *)child_2_info)->nextInfo);
#endif
END

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
NSD(408)
    gotoOuterSymbolTable();

    D_child_1_info;
    /* assert(child_1_info != NULL); */
    /* assert(child_1_info->typeKind == FunctionType); */
    AssertFunctionTypeInfo(child_1_info);
    FunctionNode *node = (FunctionNode *)child_1_info->node;
    assert(node->returnTypeInfo != NULL);
    assert(child_1_info->nextInfo == NULL);

    Alloc(parent->other_info, child_1_info);
    Noalloc(parent->other_info);

    D_child_1;
    Dealloc(child_1->other_info);

#ifdef function_type_debug_print
    D_parent_info;
    printTypeInfo(parent_info);
    printf("\n");
#endif
END

/* FuncCall */
/*     : Exp LP RP { $$ = new_parent_node("FuncCall", GROUP_4 + 9, 1, $1); } */
/*     | Exp LP Args RP { $$ = new_parent_node("FuncCall", GROUP_4 + 10, 2, $1, $3); } */
/*     ; */
NSD(409)
    D_child_1_info;
    assert(child_1_info->typeKind == FunctionType);
    FunctionNode *node = (FunctionNode *)child_1_info->node;
    if (node->paramTypeInfo == NULL)
    {
	Alloc(parent->other_info, node->returnTypeInfo);
    }
    else
    {
	Alloc(parent->other_info, child_1_info);
    }
#ifdef exp_type_debug_print
    printTypeInfo(parent->other_info);
    printf("\n");
#endif
END

NID(410)
    if (childNum == 2)
    {
        D_child_1_info;
	Alloc(child->other_info, child_1_info);
    }
END
NSD(410)
    D_child_2_info;
    Alloc(parent->other_info, child_2_info);
#ifdef function_type_debug_print
    printTypeInfo(parent->other_info);
    printf(" (SD(410))\n");
#endif
END

/* Args */
/*     : Exp COMMA Args { $$ = new_parent_node("Args", GROUP_4 + 11, 2, $1, $3); } */
/*     | PLACEHOLDER COMMA Args { $$ = new_parent_node("Args", GROUP_4 + 12, 2, $1, $3); } */
/*     | Exp { $$ = new_parent_node("Args", GROUP_4 + 13, 0); } */
/*     ; */

NID(411)
    if (childNum == 2)
    {
        D_parent_info;
        /* child->other_info = ((FunctionNode *)parent_info->node)->returnTypeInfo; */
	Alloc(child->other_info, ((FunctionNode *)parent_info->node)->returnTypeInfo);
    }
END
NSD(411)
    D_child_2_info;
    OverWrite(parent->other_info, child_2_info);
END

NID(412)
    if (childNum == 2)
    {
        D_parent_info;
	AssertFunctionTypeInfo(parent_info);

        FunctionNode *fn = parent_info->node;
        TypeInfo *paramTypeInfo = fn->paramTypeInfo;
        TypeInfo *returnTypeInfo = fn->returnTypeInfo;
        TypeInfo *realReturnTypeInfo = ((FunctionNode *)returnTypeInfo->node)->returnTypeInfo;
        while (realReturnTypeInfo->typeKind == FunctionType)
        {
            returnTypeInfo = realReturnTypeInfo;
            realReturnTypeInfo = ((FunctionNode *)realReturnTypeInfo->node)->returnTypeInfo;
        }
        FunctionNode *node = malloc(sizeof(FunctionNode));
        node->paramTypeInfo = paramTypeInfo;
        node->returnTypeInfo = realReturnTypeInfo; 
        TypeInfo *info = malloc(sizeof(TypeInfo));
        info->typeKind = FunctionType;
        info->node = node;
        info->nextInfo = NULL;
        ((FunctionNode *)returnTypeInfo->node)->returnTypeInfo = info;

	Alloc(child->other_info, ((FunctionNode *)parent_info->node)->returnTypeInfo);
#ifdef function_type_debug_print
        printTypeInfo(child->other_info);
        printf(" (ID(412))\n");
#endif
    }
END
NSD(412)
    D_child_2_info;
    OverWrite(parent->other_info, child_2_info);
END

NSD(413)
    D_parent_info;
    OverWrite(parent->other_info, ((FunctionNode *)parent_info->node)->returnTypeInfo);
END

void initActionTable4()
{
    IS(407, 408, 410, 411, 412);
    SS(401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413);
}
