#include "SDTAction.h"
#include "8.h"

/* Specifiers */
/* Specifier */
/*     : BUILDINTYPE { $$ = new_parent_node("Specifier", GROUP_8 + 1, 1, $1); } */
/*     | LET { $$ = new_parent_node("Specifier", GROUP_8 + 2, 1, $1); } */
/*     | TypeId { $$ = new_parent_node("Specifier", GROUP_8 + 3, 1, $1); } */
/*     | ArrayType { $$ = new_parent_node("Specifier", GROUP_8 + 4, 1, $1); } */
/*     | ReferType { $$ = new_parent_node("Specifier", GROUP_8 + 5, 1, $1); } */
/*     | FuncType { $$ = $1; } */
/*     ; */

SD(801)
{
    D_child_1;
    D_parent_info;

    parent_info->typeKind = BuildInType;
    if (!strcmp(child_1->str + 4, "Int"))
    {
        parent_info->node = (void *)Int;
    }
    else
    {
        parent_info->node = (void *)Float;
    }
    assert(parent_info->nextInfo == NULL);
}

SD(802)
{
    D_child_1;
    D_parent_info;

    parent_info->typeKind = BuildInType;
    parent_info->node = (void *)Let;
    assert(parent_info->nextInfo == NULL);
}

SD(803)
{
}
