#include "syntax_tree.h"
#include "SDTAction.h"
#include <stdarg.h>
#include <malloc.h>

ID(6)
{
    if(childNum == 2)
    {
        FuncInfo *funDec = (FuncInfo*)malloc(sizeof(FuncInfo));
        funDec->return_type = parent->first_child->str;
        funDec->status = 1;
        funDec->param_num = 0;
        funDec->param_list = NULL;
        child->otherInformation = funDec;
    }
}

ID(59)
{
    if(childNum == 2)
    {
        FuncInfo *funDec = (FuncInfo*)malloc(sizeof(FuncInfo));
        funDec->return_type = parent->first_child->str;
        funDec->status = 0;
        funDec->param_num = 0;
        funDec->param_list = NULL;
        child->otherInformation = funDec;
    }
}

ID(18)
{
    if(childNum == 3)
    {
        child->otherInformation = parent->otherInformation;
    }
}

ID(20)
{
    if(childNum == 3)
    {
        child->otherInformation = parent->otherInformation;
    }
}

ID(22)
{
    if(childNum == 2)
    {
        TypeInfo *varDec = (TypeInfo*)malloc(sizeof(TypeInfo));
        TypeInfo *specifier = (TypeInfo*)(parent->first_child->otherInformation);
        varDec->iType = specifier->sType;
        varDec->iDimension = 0;
        child->otherInformation = varDec;
    }
}

SD(9)
{
    TypeInfo *specifier = (TypeInfo*)malloc(sizeof(TypeInfo));
    specifier->sType = parent->first_child->str;
    parent->otherInformation = specifier;
}

SDS(20, 21)
{
    FuncInfo *varList = (FuncInfo*)(parent->otherInformation);
    TypeInfo *paramDec = (TypeInfo*)(parent->first_child->otherInformation);
    if(paramDec == NULL){
        parent->otherInformation = NULL;
        return;
    }
    Symbol *param = (Symbol*)malloc(sizeof(Symbol));
    AST_node *varDec = parent->first_child->first_child->next_brother;
    while(varDec->first_child != NULL)
        varDec = varDec->first_child;
    param->name = varDec->str + 4;
    param->kind = 0;
    param->type = paramDec->sType;
    param->dimension = paramDec->sDimension;
    param->u.next = NULL;
    // TODO add Struct Type
    addFuncParam(varList, param);
    parent->otherInformation = NULL;
}

SDS(18, 19)
{

    const char *func_name = parent->first_child->str;
    FuncInfo *varList = (FuncInfo*)(parent->otherInformation);
    int result = addNewFunc(func_name, varList);
    parent->otherInformation = NULL;
    if(result == 0)
        printf("Error type 4 at Line %d: Redefined function \"%s\".\n", 
            parent->loc_line, func_name);
    else if(result == -1)
        printf("Error type 19 at Line %d: Function \"%s\" has been defined with confliction.\n", 
            parent->loc_line, func_name);
}

SD(22)
{
    TypeInfo *varDec = (TypeInfo*)(parent->first_child->next_brother->otherInformation);
    TypeInfo *paramDec = (TypeInfo*)malloc(sizeof(TypeInfo));
    if(varDec->sType != NULL)
    {
        paramDec->sType = varDec->sType;
        paramDec->sDimension = varDec->sDimension;
        parent->otherInformation = paramDec;
    }
    else
    {
        // 结构体定义非法，不能用该结构体定义变量
        printf("Error type 17 at Line %d: Struct has not been defined.\n", parent->loc_line);
        parent->otherInformation = NULL;
    }
}