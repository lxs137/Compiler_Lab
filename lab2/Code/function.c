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
    }
}
