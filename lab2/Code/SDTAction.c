#include "syntax_tree.c"

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
