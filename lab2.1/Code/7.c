#include "SDTAction.h"
#include "symbol_table.h"
#include "7.h"

/* ADT */
/* ADTDef */
/*     : ADTHeader %prec LOWER_THAN_ASSIGNOP SEMI { $$ = new_parent_node("ADTRef", GROUP_7 + 1, 1, $1); } */
/*     | ADTHeader ASSIGNOP ConstructorDecList { $$ = new_parent_node("ADTHeader", GROUP_7 + 2, 2, $1, $3); } */
/*     ; */
ID(702)
{
    if (childNum == 2)
    {
        D_child_1_info;
        child->other_info = child_1_info;
    }
}
/* ADTHeader */
/*     : DATA TypeId ADTParamList { $$ = new_parent_node("ADTHeader", GROUP_7 + 3, 2, $2, $3); } */
/*     ; */
ID(703)
{
    if (childNum == 2)
    {
        D_child_1_info;
        /* child->oter_info充当继承属性 */
        child->other_info = child_1_info;
    }
}
SD(703)
{
    D_child_1_info;
    parent->other_info = child_1_info;
}
/* ADTParamList */
/*     : ADTParam ADTParamList { $$ = new_parent_node("ADTParamList", GROUP_7 + 4, 2, $1, $2); } */
/*     | /1* empty *1/ { $$ = new_parent_node("ADTParamList", GROUP_7 + 5, 0); } */
/*     ; */
ID(704)
{
    if (childNum ==  1 || childNum == 2)
    {
        child->other_info = parent->other_info;
    }
}
/* ADTParam */
/*     : LOWERID { $$ = new_parent_node("ADTParam", GROUP_7 + 6, 1, $1); } */
/*     ; */
SD(706)
{
    D_parent_info;
    D_child_1;
    /* TypeId-ADTParam\0 */
    int part1 = strlen((char *)parent_info);
    int part2 = strlen(child_1->str + 4);
    char *name = malloc((part1 + 1 + part2 + 1) * sizeof(char));
    strcpy(name, (char *)parent_info);
    name[part1] = '-';
    strcpy(name + part1 + 1, child_1->str + 4);
    parent->other_info = name;
    addSymbol(name, parent);
}

/* ConstructorDecList */
/*     : ConstructorDec SEMI { $$ = new_parent_node("ConstructorDecList", GROUP_7 + 7, 1, $1); } */
/*     | ConstructorDec SEMI ConstructorDecList { $$ = new_parent_node("ConstructorDecList", GROUP_7 + 8, 2, $1, $3); } */ 
/*     ; */
ID(707)
{
    if (childNum == 1)
    {
        D_parent_info;
        child->other_info = parent_info;
    }
}
ID(708)
{
    if (childNum == 1 || childNum == 3)
    {
        D_parent_info;
        child->other_info = parent_info;
    }
}
/* ConstructorDec */
/*     : ConstructorId TypeIdList { $$ = new_parent_node("ConstructorDec", GROUP_7 + 9, 2, $1, $2); } */
/*     ; */
ID(709)
{
    if (childNum == 2)
    {
        D_parent_info;
        child->other_info = parent_info;
    }
}
/* ConstructorId */
/*     : UPPERID { $$ = new_parent_node("ConstructorId", GROUP_7 + 10, 1, $1); } */
/*     ; */
SD(710)
{
    D_child_1;
    addSymbol(child_1->str + 4, parent);
}
/* TypeIdList */
/*     : TypeId TypeIdList { $$ = new_parent_node("TypeIdList", GROUP_7 + 11, 2, $1, $2); } */
/*     | ADTParam TypeIdList { $$ = new_parent_node("TypeIdList", GROUP_7 + 12, 2, $1, $2); } */
/*     | /1* empty *1/ { $$ = new_parent_node("TypeIdList", GROUP_7 + 13, 0); } */
/*     ; */
ID(712)
{
    if (childNum == 1 || childNum == 2)
    {
        D_parent_info;
        child->other_info = parent_info;
    }
}
/* TypeId */
/*     : UPPERID { $$ = new_parent_node("TypeId", GROUP_7 + 14, 1, $1); } */
/*     ; */
SD(714)
{
    D_child_1;
    addSymbol(child_1->str + 4, parent);
    /* 把名字继承到父亲 */
    parent->other_info = (void *)child_1->str + 4;
}

/* pattern matching */
/* PatternMatching */
/*     : LET LP ConstructorId PatternMatchingParamList RP ASSIGNOP VarDec { */ 
/*         $$ = new_parent_node("PatternMatching", GROUP_7 + 15, 3, $3, $4, $7); */ 
/*     } */
/*     ; */
/* PatternMatchingParamList */
/*     : LOWERID PatternMatchingParamList { */ 
/*         $$ = new_parent_node("PatternMatchingParamList", GROUP_7 + 16, 2, $1, $2); */
/*     } */
/*     | PLACEHOLDER PatternMatchingParamList { */ 
/*         $$ = new_parent_node("PatternMatchingParamList", GROUP_7 + 17, 2, $1, $2); */ 
/*     } */
/*     | /1* empty *1/ { $$ = new_parent_node("PatternMatchingParamList", GROUP_7 + 18, 0); } */
/*     ; */

void initActionTable7()
{
    IS(702, 703, 704, 707, 708, 709, 712);
    SS(703, 706, 710, 714);
}
