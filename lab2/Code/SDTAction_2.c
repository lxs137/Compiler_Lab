#include "syntax_tree.h"
#include "SDTAction.h"
#include <stdarg.h>
#include <malloc.h>

ID(6)
{
    if(childNum == 2)
    {
        FuncInfo *funDec = (FuncInfo*)malloc(sizeof(FuncInfo));
        TypeInfo *specifier = (TypeInfo*)(parent->first_child->other_info);
        funDec->return_type = specifier->sType;
        funDec->status = 1;
        funDec->param_num = 0;
        funDec->param_list = NULL;
        child->other_info = funDec;
    }
}

ID(59)
{
    if(childNum == 2)
    {
        FuncInfo *funDec = (FuncInfo*)malloc(sizeof(FuncInfo));
        TypeInfo *specifier = (TypeInfo*)(parent->first_child->other_info);
        funDec->return_type = specifier->sType;
        funDec->status = 0;
        funDec->param_num = 0;
        funDec->param_list = NULL;
        child->other_info = funDec;
    }
}

ID(18)
{
    if(childNum == 3)
    {
        child->other_info = parent->other_info;
    }
}

ID(20)
{
    if(childNum == 3)
    {
        child->other_info = parent->other_info;
    }
}

ID(22)
{
    if(childNum == 2)
    {
        TypeInfo *varDec = (TypeInfo*)malloc(sizeof(TypeInfo));
        TypeInfo *specifier = (TypeInfo*)(parent->first_child->other_info);
        varDec->iType = specifier->sType;
        varDec->iDimension = 0;
        child->other_info = varDec;
    }
}

// SD(9)
// {
//     TypeInfo *specifier = (TypeInfo*)malloc(sizeof(TypeInfo));
//     specifier->sType = parent->first_child->str;
//     parent->other_info = specifier;
// }

SDS(20, 21)
{
    FuncInfo *varList = (FuncInfo*)(parent->other_info);
    TypeInfo *paramDec = (TypeInfo*)(parent->first_child->other_info);
    if(paramDec == NULL){
        parent->other_info = NULL;
        return;
    }
    AST_node *varDec = parent->first_child->first_child->next_brother;
    while(varDec->first_child != NULL)
        varDec = varDec->first_child;
    // TODO add Struct Type
    addFuncParam(varList, varDec->str + 4, paramDec->sType, paramDec->sDimension);
    parent->other_info = NULL;
}

SDS(18, 19)
{

    const char *func_name = parent->first_child->str;
    FuncInfo *varList = (FuncInfo*)(parent->other_info);
    int result = addNewFunc(func_name, varList);
    parent->other_info = NULL;
    if(result == 0)
        printf("Error type 4 at Line %d: Redefined function \"%s\".\n", 
            parent->loc_line, func_name);
    else if(result == -1)
        printf("Error type 19 at Line %d: Function \"%s\" has been defined with confliction.\n", 
            parent->loc_line, func_name);
    freeTempParamList(varList->param_list);
    free(varList);
}

SD(22)
{
    TypeInfo *varDec = (TypeInfo*)(parent->first_child->next_brother->other_info);
    TypeInfo *paramDec = (TypeInfo*)malloc(sizeof(TypeInfo));
    if(varDec->sType != NULL)
    {
        paramDec->sType = varDec->sType;
        paramDec->sDimension = varDec->sDimension;
        parent->other_info = paramDec;
    }
    else
    {
        // 结构体定义非法，不能用该结构体定义变量
        printf("Error type 17 at Line %d: Struct has not been defined.\n", parent->loc_line);
        parent->other_info = NULL;
    }
}

SD(51)
{
    const char* func_name = parent->first_child->str + 4;
    Symbol *func_in_table = getFuncSymbol(func_name);
    if(func_in_table == NULL)
        printf("Error type 2 at Line %d: Function %s has not been defined.\n",
         parent->loc_line, func_name);
    // 在变量符号表中查找该ID
    // TODO change find symbol function
    if(getSymbol(func_name) != NULL)
        printf("Error type 11 at Line %d: Variable %s is not a function.\n",
         parent->loc_line, func_name);
}