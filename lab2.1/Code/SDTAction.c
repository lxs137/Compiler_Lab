#include "SDTAction.h"
#include "3.h"
#include "4.h"
#include "9.h"

/* 产生式数目 */
static const int ProCount[10] = { 1, 2, 10, 12, 1, 1, 18, 6, 5, 19};

static SDTIAction *sdtIActionTable = NULL;
static SDTSAction *sdtSActionTable = NULL;

void initActionTable()
{
    int sum  = 0;
    int i;
    for (i = 0; i < 10; i++)
    {
        sum += ProCount[i];
    }

    /* calloc() zero-initializes the buffer, while malloc() leaves the memory uninitialized. */
    assert(sdtIActionTable == NULL);
    assert(sdtSActionTable == NULL);
    sdtIActionTable = (SDTIAction *)calloc(sum, sizeof(SDTIAction));
    sdtSActionTable = (SDTSAction *)calloc(sum, sizeof(SDTIAction));

    initActionTable3();
    initActionTable4();
    initActionTable9();
}

void cleanActionTable()
{
    assert(sdtIActionTable != NULL);
    free(sdtIActionTable);
    sdtIActionTable = NULL;

    assert(sdtSActionTable != NULL);
    free(sdtSActionTable);
    sdtSActionTable = NULL;
}

void registerIAction(int proNum, SDTIAction action)
{
    int tableIndex = proNum2TableIndex(proNum);
    assert(sdtIActionTable[tableIndex] == NULL);
    sdtIActionTable[tableIndex] = action;
}

void registerSAction(int proNum, SDTSAction action)
{
    int tableIndex = proNum2TableIndex(proNum);
    assert(sdtSActionTable[tableIndex] == NULL);
    sdtSActionTable[tableIndex] = action;
}

int proNum2TableIndex(int proNum)
{
    int group = proNum / 100;
    int sum = proNum % 100;

    int i;
    for (i = 0; i < group; i++)
    {
        sum += ProCount[i];
    }

    return sum;
}

void traversalTreePerformAction(AST_node *parent)
{
    int proNum = parent->proNum;
    int tableIndex = proNum2TableIndex(proNum);
    
    SDTIAction f = sdtIActionTable[tableIndex];
    if (f != NULL)
    {
        f(parent, parent, 0);
    }
    int i = 1;
#ifdef DEBUG
    printf("Line %d: %s childNum(%d) (%d) I Action start.\n",
        parent->loc_line, parent->str, i, proNum);
#endif
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
#ifdef DEBUG
    printf("Line %d: %s (%d) I Action end.\n", parent->loc_line, parent->str, proNum);
#endif
    
    SDTSAction g = sdtSActionTable[tableIndex];
    if (g != NULL)
    {
        g(parent);
    }
#ifdef DEBUG
    printf("Line %d: %s (%d) S Action end.\n", parent->loc_line, parent->str, proNum);
#endif
}
