#include "syntax_tree.h"
#include "SDTAction.h"
#include <stdarg.h>
#include <malloc.h>

void traversalTreePerformAction(AST_node *parent)
{
    int proNum = parent->proNum;
    sdtIActionTable[proNum](parent, parent, 0);

    int i = 0;
    for (AST_node *child = parent->first_child; 
         child != NULL;
         child = child->next_brother) 
    {
        sdtIActionTable[proNum](parent, child, i);
        traversalTreePerformAction(child);
        i++;
    }

    sdtSActionTable[proNum](parent);
}

void nullIAction(AST_node *parent, AST_node *child, int childNum)
{
    printf("%d\n", parent->proNum);
}

void nullSAction(AST_node *parent)
{
}

SDTIAction sdtIActionTable[ProCount];
SDTSAction sdtSActionTable[ProCount];

void initTable()
{
    for (int i = 0; i < ProCount; i++)
    {
        sdtIActionTable[i] = nullIAction;
    }
    for (int i = 0; i < ProCount; i++)
    {
        sdtSActionTable[i] = nullSAction;
    }
}

typedef struct
{
    const char *iType;
} DecListInfo;

void pro34IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 0)
    {
        DecListInfo *decListInfo = (DecListInfo*)malloc(sizeof(DecListInfo));
        decListInfo->iType = parent->first_child->str;
        child->otherInformation = decListInfo;
    }
}

void pro35IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 0)
    {
        DecListInfo *decListInfo = (DecListInfo*)malloc(sizeof(DecListInfo));
        decListInfo->iType = ((DecListInfo*)parent->otherInformation)->iType;
        child->otherInformation = decListInfo;
    }
}

void pro36IAction(AST_node *parent, AST_node *child, int childNum)
{
    if (childNum == 0)
    {
        DecListInfo *decListInfo1 = (DecListInfo*)malloc(sizeof(DecListInfo));
        decListInfo1->iType = ((DecListInfo*)parent->otherInformation)->iType;
        child->otherInformation = decListInfo1;
    }
}
