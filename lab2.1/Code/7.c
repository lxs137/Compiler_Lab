#include "SDTAction.h"
#include "symbol_table.h"
#include "7.h"

/* ADT */
/* ADTDef */
/*     : ADTHeader %prec LOWER_THAN_ASSIGNOP SEMI { $$ = new_parent_node("ADTRef", GROUP_7 + 1, 1, $1); } */
/*     | ADTHeader ASSIGNOP ConstructorDecList { $$ = new_parent_node("ADTHeader", GROUP_7 + 2, 2, $1, $3); } */
/*     ; */
/* ADTHeader */
/*     : DATA TypeId ADTParamList { $$ = new_parent_node("ADTHeader", GROUP_7 + 3, 2, $2, $3); } */
/*     ; */
/* ADTParamList */
/*     : ADTParam ADTParamList { $$ = new_parent_node("ADTParamList", GROUP_7 + 4, 2, $1, $2); } */
/*     | /1* empty *1/ { $$ = new_parent_node("ADTParamList", GROUP_7 + 5, 0); } */
/*     ; */
/* ADTParam */
/*     : LOWERID { $$ = new_parent_node("ADTParam", GROUP_7 + 6, 0); } */
/*     ; */
/* ConstructorDecList */
/*     : ConstructorDec SEMI { $$ = new_parent_node("ConstructorDecList", GROUP_7 + 7, 1, $1); } */
/*     | ConstructorDec SEMI ConstructorDecList { $$ = new_parent_node("ConstructorDecList", GROUP_7 + 8, 2, $1, $3); } */ 
/*     ; */
/* ConstructorDec */
/*     : ConstructorId TypeIdList { $$ = new_parent_node("ConstructorDec", GROUP_7 + 9, 2, $1, $2); } */
/*     ; */
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
/* TypeId */
/*     : UPPERID { $$ = new_parent_node("TypeId", GROUP_7 + 14, 1, $1); } */
/*     ; */
SD(714)
{
    D_child_1;
    addSymbol(child_1->str + 4, parent);
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
    SS(710, 714);
}
