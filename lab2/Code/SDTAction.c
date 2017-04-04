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

ID(34)
{
    if (childNum == 2)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iType = ((TypeInfo *)parent->first_child->otherInformation)->sType;
        child->otherInformation = typeInfo;
        printf("%s\n", typeInfo->iType);
    }
}

/* void pro35IAction(AST_node *parent, AST_node *child, int childNum) */
ID(35)
{
    if (childNum == 1)
    {
        TypeInfo *decListInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        decListInfo->iType = ((TypeInfo *)parent->otherInformation)->iType;
        child->otherInformation = decListInfo;
    }
}

/* void pro36IAction(AST_node *parent, AST_node *child, int childNum) */
ID(36)
{
    if (childNum == 1)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iType = ((TypeInfo *)parent->otherInformation)->iType;
        child->otherInformation = typeInfo;
    }
    else if (childNum == 3)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iType = ((TypeInfo *)parent->otherInformation)->iType;
        child->otherInformation = typeInfo;
    }
}

/* void pro37IAction(AST_node *parent, AST_node *child, int childNum) */
ID(37)
{
    if (childNum == 1)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iType = ((TypeInfo *)parent->otherInformation)->iType;
        typeInfo->iDimension = 0;
        child->otherInformation = typeInfo;
    }
}

/* void pro37SAction(AST_node *parent) */
SD(37)
{
}

/* void pro38IAction(AST_node *parent, AST_node *child, int childNum) */
ID(38)
{
    if (childNum == 1)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iType = ((TypeInfo *)parent->otherInformation)->iType;
        typeInfo->iDimension = 0;
        child->otherInformation = typeInfo;
    }
    else if (childNum == 3)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iDimension = 0;
        child->otherInformation = typeInfo;
    }
}

/* void pro38SAction(AST_node *parent) */
SD(38)
{
    TypeInfo *childOneInfo = (TypeInfo *)parent->first_child->otherInformation;
    TypeInfo *childThreeInfo = (TypeInfo *)parent->first_child->next_brother->next_brother->otherInformation;
    /* strcmp() */
}

/* void pro17IAction(AST_node *parent, AST_node *child, int childNum) */
ID(17)
{
    if (childNum == 1)
    {
        TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iType = parentInfo->iType;
        typeInfo->iDimension = parentInfo->iDimension + 1;
        child->otherInformation = typeInfo;
    }
}

/* void pro26IAction(AST_node *parent, AST_node *child, int childNum) */
ID(26)
{
    if (childNum == 1)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iDimension = 0;
        child->otherInformation = typeInfo;
    }
}

/* void pro52IAction(AST_node *parent, AST_node *child, int childNum) */
ID(52)
{
    if (childNum == 1 || childNum == 3)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iDimension = ((TypeInfo *)parent->otherInformation)->iDimension + 1;
        child->otherInformation = typeInfo;
    }
}

IDS(39, 40, 41, 42, 43, 44, 45, 46)
{
    if (childNum == 1 || childNum == 3)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iDimension = 0;
        child->otherInformation = typeInfo;
    }
}

SD(9)
{
    TypeInfo *parentInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
    parentInfo->sType = parent->first_child->str + 6;
    parent->otherInformation = parentInfo;
    /* printf("%s\n", parentInfo->sType); */
}

/* void pro16SAction(AST_node *parent) */
SD(16)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    parentInfo->sType = parentInfo->iType;
    parentInfo->sDimension = parentInfo->iDimension;
    TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
    typeInfo->sType = parentInfo->sType;
    typeInfo->sDimension = parentInfo->sDimension;
    parent->first_child->otherInformation = typeInfo;
    addSymbol(parent->first_child->str + 4, parent->first_child);
}

/* void pro17SAction(AST_node *parent) */
SD(17)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    TypeInfo *childInfo = (TypeInfo *)parent->first_child->otherInformation;
    parentInfo->sType = childInfo->iType;
    parentInfo->sDimension = childInfo->sDimension;
}

/* void pro52SAction(AST_node *parent) */
SD(52)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    TypeInfo *childOneInfo = (TypeInfo *)parent->first_child->otherInformation;
    TypeInfo *childThreeInfo = (TypeInfo *)parent->first_child->next_brother->next_brother->otherInformation;
    parentInfo->sType = childOneInfo->sType;
    parentInfo->sDimension = childOneInfo->sDimension;
    parentInfo->sValid = childOneInfo->sValid && childThreeInfo->sValid;
    parentInfo->sValid &= strcmp(childThreeInfo->sType, "Int");
    parentInfo->sValid &= childThreeInfo->sDimension == 0;
}

/* void pro54SAction(AST_node *parent) */
SD(54)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    AST_node *child = getSymbol(parent->first_child->str + 4);
    if (child == NULL)
    {
        printf("Error type 1 at Line %d: Undefined variable \"%s\".\n",
               parent->first_child->loc_line,
               parent->first_child->str + 4);
        /* parentInfo->sType = ""; */
        /* parentInfo->sDimension = -1; */
        parentInfo->sValid = 0;
        return;
    }
    TypeInfo *childInfo = (TypeInfo *)child->otherInformation;
    parentInfo->sType = childInfo->sType;
    parentInfo->sDimension = childInfo->sDimension - parentInfo->iDimension;
    if (parentInfo->sDimension < 0)
    {
        /* printf("error.\n"); */
        parentInfo->sValid = 0;
        return;
    }
    parentInfo->sValid = 1;
}

/* void pro55SAction(AST_node *parent) */
SDS(55, 56)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    parentInfo->sValid = 1;
    parentInfo->sType = parent->first_child->str;
    parentInfo->sDimension = 0;
}

/* SDTSAction pro56SAction = pro55SAction; */

/* void pro26SAction(AST_node *parent) */
SD(26)
{
    TypeInfo *childInfo = (TypeInfo *)parent->first_child->otherInformation;
}

/* void pro39SAction(AST_node *parent) */
SD(39)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    TypeInfo *childOneInfo = (TypeInfo *)parent->first_child->otherInformation;
    TypeInfo *childTwoInfo = (TypeInfo *)parent->first_child->next_brother->next_brother->otherInformation;
    parentInfo->sValid = childOneInfo->sValid && childTwoInfo->sValid;
    if (parentInfo->sValid)
    {
        parentInfo->sValid &= strcmp(childOneInfo->sType, childTwoInfo->sType);
        parentInfo->sValid &= childOneInfo->sDimension == childTwoInfo->sDimension;
    }
    if (parentInfo->sValid)
    {
        parentInfo->sType = childOneInfo->sType;
        parentInfo->sDimension = childOneInfo->sDimension;
    }
    else
    {
        /* printf("error.\n"); */
    }
}

/* void pro42SAction(AST_node *parent) */
SD(42)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    TypeInfo *childOneInfo = (TypeInfo *)parent->first_child->otherInformation;
    TypeInfo *childTwoInfo = (TypeInfo *)parent->first_child->next_brother->next_brother->otherInformation;
    parentInfo->sValid = childOneInfo->sValid && childTwoInfo->sValid;
    if (parentInfo->sValid)
    {
        parentInfo->sValid &= strcmp(childOneInfo->sType, childTwoInfo->sType);
        parentInfo->sValid &= childOneInfo->sDimension == 0;
        parentInfo->sValid &= childTwoInfo->sDimension == 0;
    }
    if (parentInfo->sValid)
    {
        parentInfo->sType = "Int";
        parentInfo->sDimension = 0;
    }
    else
    {
        /* printf("error.\n"); */
    }
}

/* void pro43SAction(AST_node *parent) */
SD(43)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    TypeInfo *childOneInfo = (TypeInfo *)parent->first_child->otherInformation;
    TypeInfo *childTwoInfo = (TypeInfo *)parent->first_child->next_brother->next_brother->otherInformation;
    parentInfo->sValid = childOneInfo->sValid && childTwoInfo->sValid;
    if (parentInfo->sValid)
    {
        parentInfo->sValid &= strcmp(childOneInfo->sType, childTwoInfo->sType);
        parentInfo->sValid &= childOneInfo->sDimension == 0;
        parentInfo->sValid &= childTwoInfo->sDimension == 0;
    }
    if (parentInfo->sValid)
    {
        parentInfo->sType = childOneInfo->sType;
        parentInfo->sDimension = childOneInfo->sDimension;
    }
    else
    {
        /* printf("error.\n"); */
    }
}

/* void pro40SAction(AST_node *parent) */
SDS(40, 41, 44, 45, 46)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    TypeInfo *childOneInfo = (TypeInfo *)parent->first_child->otherInformation;
    TypeInfo *childTwoInfo = (TypeInfo *)parent->first_child->next_brother->next_brother->otherInformation;
    parentInfo->sValid = childOneInfo->sValid && childTwoInfo->sValid;
    if (parentInfo->sValid)
    {
        parentInfo->sValid &= strcmp(childOneInfo->sType, "Int");
        parentInfo->sValid &= strcmp(childTwoInfo->sType, "Int");
        parentInfo->sValid &= childOneInfo->sDimension == 0;
        parentInfo->sValid &= childTwoInfo->sDimension == 0;
    }
    if (parentInfo->sValid)
    {
        parentInfo->sType = "Int";
        parentInfo->sDimension = 0;
    }
    else
    {
        /* printf("error.\n"); */
    }
}

/* SDTSAction pro41SAction = pro40SAction; */
/* IDS(40, 41); */

/* SDTSAction pro44SAction = pro43SAction; */
/* SDTSAction pro45SAction = pro43SAction; */
/* SDTSAction pro46SAction = pro43SAction; */

void initTable()
{
    IS(17, 26, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 52);
    SS(9, 16, 17, 26, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 52, 54, 55, 56);
}
