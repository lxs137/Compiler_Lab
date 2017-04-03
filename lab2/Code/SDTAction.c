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
} TypeInfo;

void pro34IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 2)
    {
        TypeInfo *decListInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        decListInfo->iType = parent->first_child->str;
        child->otherInformation = decListInfo;
    }
}

void pro35IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 1)
    {
        TypeInfo *decListInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        decListInfo->iType = ((TypeInfo *)parent->otherInformation)->iType;
        child->otherInformation = decListInfo;
    }
}

void pro36IAction(AST_node *parent, AST_node *child, int childNum)
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

void pro37IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 1)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iType = ((TypeInfo *)parent->otherInformation)->iType;
        typeInfo->iDimension = 0;
        child->otherInformation = typeInfo;
    }
}

void pro37SAction(AST_node *parent)
{
    /* printf("Type valid."); */
}

void pro38IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 1)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iType = ((TypeInfo *)parent->otherInformation)->iType;
        typeInfo->iDimension = 0;
        child->otherInformation = typeInfo;
    }
}

void pro38SAction(AST_node *parent)
{
    /* printf("Type valid.") */
}

void pro17IAction(AST_node *parent, AST_node *child, int childNum)
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

void pro26IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 1)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iDimension = 0;
        child->otherInformation = typeInfo;
    }
}

void pro52IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 1)
    {
        TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
        typeInfo->iDimension = ((TypeInfo *)parent->otherInformation)->iDimension + 1;
        child->otherInformation = typeInfo;
    }
}

void pro16SAction(AST_node *parent)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    parentInfo->sType = parentInfo->iType;
    parentInfo->sDimension = parentInfo->iDimension;
    TypeInfo *typeInfo = (TypeInfo *)malloc(sizeof(TypeInfo));
    typeInfo->sType = parentInfo->sType;
    typeInfo->sDimension = parentInfo->sDimension;
    parent->first_child->otherInformation = typeInfo;
    printf("ID's base type is %s, dimension is %d\n", typeInfo->sType, typeInfo->sDimension);
    addSymbol(parent->first_child->str + 4, parent->first_child);
    printSymbolTable(globalSymbolTable);
}

void pro17SAction(AST_node *parent)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    TypeInfo *childInfo = (TypeInfo *)parent->first_child->otherInformation;
    parentInfo->sType = childInfo->iType;
    parentInfo->sDimension = childInfo->sDimension;
}

void pro52SAction(AST_node *parent)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    TypeInfo *childInfo = (TypeInfo *)parent->first_child->otherInformation;
    parentInfo->sType = childInfo->sType;
    parentInfo->sDimension = childInfo->sDimension;
}

void pro54SAction(AST_node *parent)
{
    TypeInfo *parentInfo = (TypeInfo *)parent->otherInformation;
    AST_node *child = getSymbol(parent->first_child->str + 4);
    if (child == NULL)
    {
        printf("can't find id defintion.\n");
        parentInfo->sType = "";
        parentInfo->sDimension = 0;
        return;
    }
    TypeInfo *childInfo = (TypeInfo *)child->otherInformation;
    parentInfo->sType = childInfo->sType;
    parentInfo->sDimension = childInfo->sDimension - parentInfo->iDimension;
    if (parentInfo->sDimension < 0)
    {
        printf("error.\n");
    }
}

void pro26SAction(AST_node *parent)
{
    TypeInfo *childInfo = (TypeInfo *)parent->first_child->otherInformation;
    printf("Stmt's type is %s, dimension is %d.\n", childInfo->sType, childInfo->sDimension);
}

void initTable()
{
    sdtIActionTable[17] = pro17IAction;
    sdtIActionTable[26] = pro26IAction;
    sdtIActionTable[34] = pro34IAction;
    sdtIActionTable[35] = pro35IAction;
    sdtIActionTable[36] = pro36IAction;
    sdtIActionTable[37] = pro37IAction;
    sdtIActionTable[38] = pro38IAction;
    sdtIActionTable[52] = pro52IAction;
    
    sdtSActionTable[16] = pro16SAction;
    sdtSActionTable[17] = pro17SAction;
    sdtSActionTable[26] = pro26SAction;
    sdtSActionTable[37] = pro37SAction;
    sdtSActionTable[38] = pro38SAction;
    sdtSActionTable[52] = pro52SAction;
    sdtSActionTable[54] = pro54SAction;
}
