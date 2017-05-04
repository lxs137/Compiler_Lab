#include "SDTAction.h"
#include "9.h"

/* Local Definitions */
/* VarDef */
/*     : Specifier DecList { $$ = new_parent_node("VarDef", GROUP_9 + 1, 2, $1, $2); } */
/*     | PatternMatching { $$ = new_parent_node("VarDef", GROUP_9 + 2, 1, $1); } */
/*     ; */
/* DecList */
/*     : Dec { $$ = new_parent_node("DecList", GROUP_9 + 3, 1, $1); } */
/*     | Dec COMMA DecList { $$ = new_parent_node("DecList", GROUP_9 + 4, 2, $1, $3); } */
/*     ; */

/* Dec */
/*     : VarDec { $$ = new_parent_node("Dec", GROUP_9 + 4, 1, $1); } */
/*     | VarDec ASSIGNOP Exp { $$ = new_parent_node("Dec", GROUP_9 + 5, 2, $1, $3); } */
/*     ; */
SD(904)
{
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
    /* 回收SD(906)分配的资源 */;
    child_1->other_info = NULL;
}

SD(905)
{
    D_child_1;
    D_child_1_info;
    assert(child_1_info != NULL);
    addSymbol((char *)child_1_info, child_1);
    /* 回收SD(906)分配的资源 */;
    child_1->other_info = NULL;
}

/* Declarators */
/* VarDec */
/*     : LOWERID { $$ = new_parent_node("VarDec", GROUP_9 + 6, 1, $1); } */
/*     ; */
SD(906)
{
    D_child_1;
    assert(parent->other_info == NULL);
    /* 分配的资源由SD(904) / SD(905) / SD(1016)回收 */
    parent->other_info = child_1->str + 4;
}

void initActionTable9()
{
    /* registerSAction(906, pro906SAction); */
    SS(904, 905, 906);
}
