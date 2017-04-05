#include "syntax_tree.h"
#include "SDTAction.h"
#include <stdarg.h>
#include <malloc.h>

void traversalTreePerformAction(AST_node *parent)
{
    int proNum = parent->proNum;
    
    SDTIAction f = sdtIActionTable[proNum];
    if (f != NULL)
    {
        f(parent, parent, 0);
    }
    
    int i = 1;
    for (AST_node *child = parent->first_child;
            child != NULL;
            child = child->next_brother)
    {
        if (f != NULL)
        {
            f(parent, child, i);
        }
        traversalTreePerformAction(child);
        i++;
    }
    
    SDTSAction g = sdtSActionTable[proNum];
    if (g != NULL)
    {
        g(parent);
    }
}

SDTIAction sdtIActionTable[ProCount] = { NULL };
SDTSAction sdtSActionTable[ProCount] = { NULL };

typedef struct
{
    const char *iType;
    const char *sType;
    int iDimension;
    int sDimension;
    int sValid;
} TypeInfo;

ID(17)
{
    if (childNum == 1)
    {
        TypeInfo *parent_info = (TypeInfo *)parent->other_info;
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iType = parent_info->iType;
        type_info->iDimension = parent_info->iDimension + 1;
        child->other_info = type_info;
    }
}

ID(26)
{
    if (childNum == 1)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iDimension = 0;
        child->other_info = type_info;
    }
}

ID(34)
{
    if (childNum == 2)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iType = ((TypeInfo *)parent->first_child->other_info)->sType;
        child->other_info = type_info;
        /* printf("%s\n", type_info->iType); */
    }
}

ID(35)
{
    if (childNum == 1)
    {
        TypeInfo *decListInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        decListInfo->iType = ((TypeInfo *)parent->other_info)->iType;
        child->other_info = decListInfo;
    }
}

ID(36)
{
    if (childNum == 1)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iType = ((TypeInfo *)parent->other_info)->iType;
        child->other_info = type_info;
    }
    else if (childNum == 3)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iType = ((TypeInfo *)parent->other_info)->iType;
        child->other_info = type_info;
    }
}

ID(37)
{
    if (childNum == 1)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iType = ((TypeInfo *)parent->other_info)->iType;
        type_info->iDimension = 0;
        child->other_info = type_info;
    }
}

ID(38)
{
    if (childNum == 1)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iType = ((TypeInfo *)parent->other_info)->iType;
        type_info->iDimension = 0;
        child->other_info = type_info;
    }
    else if (childNum == 3)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iDimension = 0;
        child->other_info = type_info;
    }
}

IDS(39, 40, 41, 42, 43, 44, 45, 46)
{
    if (childNum == 1 || childNum == 3)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iDimension = 0;
        child->other_info = type_info;
    }
}

ID(52)
{
    if (childNum == 1 || childNum == 3)
    {
        TypeInfo *type_info = (TypeInfo *)malloc(sizeof(TypeInfo));
        type_info->iDimension = ((TypeInfo *)parent->other_info)->iDimension + 1;
        child->other_info = type_info;
    }
}

SD(9)
{
    TypeInfo *parent_info = (TypeInfo *)malloc(sizeof(TypeInfo));
    parent_info->sType = parent->first_child->str + 6;
    /* D_type_info; */
    /* type_info->sType = parent->first_child->str + 6; */
    /* D_parent_info; */
    parent_info = parent_info;
    parent->other_info = parent_info;
    /* printf("%s\n", parent_info->sType); */
}

SD(16)
{
    D_parent_info;
    parent_info->sType = parent_info->iType;
    parent_info->sDimension = parent_info->iDimension;
    D_type_info;
    type_info->sType = parent_info->sType;
    type_info->sDimension = parent_info->sDimension;
    /* D_child_1_info; */
    /* child_1_info = type_info; */
    parent->first_child->other_info = type_info;
    addSymbol(parent->first_child->str + 4, parent->first_child);
    /* printf("%s's type is %s, dimension is %d.\n", parent->first_child->str + 4, type_info->sType, type_info->sDimension); */
}

SD(17)
{
    D_parent_info;
    D_child_1_info;
    parent_info->sType = child_1_info->iType;
    parent_info->sDimension = child_1_info->sDimension;
}

SD(26)
{
    TypeInfo *child_info = (TypeInfo *)parent->first_child->other_info;
}

SD(37)
{
}

SD(38)
{
    D_child_1_info;
    D_child_3_info;
    /* strcmp() */
}

SD(39)
{
    D_parent_info;
    D_child_1_info;
    D_child_3_info;
    parent_info->sValid = child_1_info->sValid && child_3_info->sValid;
    if (parent_info->sValid)
    {
        parent_info->sValid &= strcmp(child_1_info->sType, child_3_info->sType);
        parent_info->sValid &= child_1_info->sDimension == child_3_info->sDimension;
    }
    if (parent_info->sValid)
    {
        parent_info->sType = child_1_info->sType;
        parent_info->sDimension = child_1_info->sDimension;
    }
    else
    {
        /* printf("error.\n"); */
    }
}

SDS(40, 41, 44, 45, 46)
{
    D_parent_info;
    D_child_1_info;
    D_child_3_info;
    parent_info->sValid = child_1_info->sValid && child_3_info->sValid;
    if (parent_info->sValid)
    {
        parent_info->sValid &= strcmp(child_1_info->sType, "Int");
        parent_info->sValid &= strcmp(child_3_info->sType, "Int");
        parent_info->sValid &= child_1_info->sDimension == 0;
        parent_info->sValid &= child_3_info->sDimension == 0;
    }
    if (parent_info->sValid)
    {
        parent_info->sType = "Int";
        parent_info->sDimension = 0;
    }
    else
    {
        /* printf("error.\n"); */
    }
}

SD(42)
{
    D_parent_info;
    D_child_1_info;
    D_child_3_info;
    parent_info->sValid = child_1_info->sValid && child_3_info->sValid;
    if (parent_info->sValid)
    {
        parent_info->sValid &= strcmp(child_1_info->sType, child_3_info->sType);
        parent_info->sValid &= child_1_info->sDimension == 0;
        parent_info->sValid &= child_3_info->sDimension == 0;
    }
    if (parent_info->sValid)
    {
        parent_info->sType = "Int";
        parent_info->sDimension = 0;
    }
    else
    {
        /* printf("error.\n"); */
    }
}

SD(43)
{
    D_parent_info;
    D_child_1_info;
    D_child_3_info;
    parent_info->sValid = child_1_info->sValid && child_3_info->sValid;
    if (parent_info->sValid)
    {
        parent_info->sValid &= strcmp(child_1_info->sType, child_3_info->sType);
        parent_info->sValid &= child_1_info->sDimension == 0;
        parent_info->sValid &= child_3_info->sDimension == 0;
    }
    if (parent_info->sValid)
    {
        parent_info->sType = child_1_info->sType;
        parent_info->sDimension = child_1_info->sDimension;
    }
    else
    {
        /* printf("error.\n"); */
    }
}

SD(52)
{
    D_parent_info;
    D_child_1_info;
    D_child_3_info;
    parent_info->sType = child_1_info->sType;
    parent_info->sDimension = child_1_info->sDimension;
    parent_info->sValid = child_1_info->sValid && child_3_info->sValid;
    parent_info->sValid &= strcmp(child_3_info->sType, "Int");
    parent_info->sValid &= child_3_info->sDimension == 0;
}

SD(54)
{
    D_parent_info;
    AST_node *child = getSymbol(parent->first_child->str + 4);
    if (child == NULL)
    {
        printf("Error type 1 at Line %d: Undefined variable \"%s\".\n",
               parent->first_child->loc_line,
               parent->first_child->str + 4);
        parent_info->sValid = 0;
        return;
    }
    D_child_info;
    parent_info->sType = child_info->sType;
    parent_info->sDimension = child_info->sDimension - parent_info->iDimension;
    if (parent_info->sDimension < 0)
    {
        parent_info->sValid = 0;
        return;
    }
    parent_info->sValid = 1;
}

SDS(55, 56)
{
    D_parent_info;
    parent_info->sValid = 1;
    parent_info->sType = parent->first_child->str;
    parent_info->sDimension = 0;
}

void initTable()
{
    IS(17, 26, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 52);
    SS(9, 16, 17, 26, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 52, 54, 55, 56);
}
