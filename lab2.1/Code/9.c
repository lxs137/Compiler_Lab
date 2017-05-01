#include "SDTAction.h"
#include "symbol_table.h"
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

/* Declarators */
/* VarDec */
/*     : LOWERID { $$ = new_parent_node("VarDec", GROUP_9 + 5, 1, $1); } */
/*     ; */
SD(905)
{
    assert(parent->proNum == 905);
    D_child_1;
    /* printf("%s\n", child_1->str + 4); */
    addSymbol(child_1->str + 4, child_1);
}

void initActionTable9()
{
    registerSAction(905, pro905SAction);
}
