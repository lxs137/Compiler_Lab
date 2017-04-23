#include "syntax_tree.h"
#include "SDTAction.h"
#include <stdarg.h>
#include <malloc.h>

/* 处理函数定义, 声明和使用 */

ID(6)
{
    if(childNum == 2)
    {
        FuncInfo *funDec = (FuncInfo*)malloc(sizeof(FuncInfo));
        TypeInfo *specifier = (TypeInfo*)(parent->first_child->other_info);
        if(!specifier->sValid)
            funDec->return_type = NULL;
        else
            funDec->return_type = specifier->sType;
        funDec->status = 1;
        funDec->param_num = 0;
        funDec->param_list = NULL;
        child->other_info = funDec;
    }
    else if(childNum == 3)
    {
        TypeInfo *specifier = (TypeInfo*)(parent->first_child->other_info);
        TypeInfo *compSt = (TypeInfo*)malloc(sizeof(TypeInfo));
        if(!specifier->sValid)
            compSt->sType = NULL;
        else
            compSt->sType = specifier->sType;
        compSt->sValid = 1;
        child->other_info = compSt;
    }
}

ID(59)
{
    if(childNum == 2)
    {
        FuncInfo *funDec = (FuncInfo*)malloc(sizeof(FuncInfo));
        TypeInfo *specifier = (TypeInfo*)(parent->first_child->other_info);
        if(!specifier->sValid)
            funDec->return_type = NULL;
        else
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
        varDec->sValid = 1;
        child->other_info = varDec;
    }
}

ID(23)
{
    if(childNum == 3)
    {
        TypeInfo *stmtList = (TypeInfo*)malloc(sizeof(TypeInfo));
        TypeInfo *compSt = (TypeInfo*)(parent->other_info);
        stmtList->sType = compSt->sType;
        stmtList->sValid = compSt->sValid;
        child->other_info = stmtList;
    }
}

ID(24)
{
    if(childNum == 1 || childNum == 2)
    {
        TypeInfo *stmt = (TypeInfo*)malloc(sizeof(TypeInfo));
        TypeInfo *stmtList = (TypeInfo*)(parent->other_info);
        stmt->sType = stmtList->sType;
        stmt->sValid = stmtList->sValid;
        child->other_info = stmt;
    }
}

ID(27)
{
    if(childNum == 1)
    {
        TypeInfo *compSt = (TypeInfo*)malloc(sizeof(TypeInfo));
        TypeInfo *stmt = (TypeInfo*)(parent->other_info);
        compSt->sType = stmt->sType;
        compSt->sValid = stmt->sValid;
        child->other_info = compSt;
    }
}

ID(28)
{
    if(childNum == 2)
    {
        TypeInfo *exp = (TypeInfo*)malloc(sizeof(TypeInfo));
        child->other_info = exp;
    }
}

IDS(29, 31)
{
    if(childNum == 3)
    {
        TypeInfo *exp = (TypeInfo*)malloc(sizeof(TypeInfo));
        child->other_info = exp;
    }
    else if(childNum == 5)
    {
        TypeInfo *stmt_ = (TypeInfo*)malloc(sizeof(TypeInfo));
        TypeInfo *stmt = (TypeInfo*)(parent->other_info);
        stmt_->sType = stmt->sType;
        stmt_->sValid = stmt->sValid;
        child->other_info = stmt_;
    }
}

ID(30)
{
    if(childNum == 3)
    {
        TypeInfo *exp = (TypeInfo*)malloc(sizeof(TypeInfo));
        child->other_info = exp;
    }
    if(childNum == 5 || childNum == 7)
    {
        TypeInfo *stmt_ = (TypeInfo*)malloc(sizeof(TypeInfo));
        TypeInfo *stmt = (TypeInfo*)(parent->other_info);
        stmt_->sType = stmt->sType;
        stmt_->sValid = stmt->sValid;
        child->other_info = stmt_;
    }
}

ID(50)
{
    if(childNum == 3)
    {
        FuncInfo *args = (FuncInfo*)malloc(sizeof(FuncInfo));
        args->param_num = 0;
        args->param_list = NULL;
        child->other_info = args;
        parent->first_child->other_info = args;
    }
}

ID(51)
{
    if(childNum == 2)
    {
        FuncInfo *args = (FuncInfo*)malloc(sizeof(FuncInfo));
        args->param_num = 0;
        args->param_list = NULL;
        child->other_info = args;
        parent->first_child->other_info = args;        
    }
}

ID(57)
{
    if(childNum == 1)
    {
        TypeInfo* exp = (TypeInfo*)malloc(sizeof(TypeInfo));
        child->other_info = exp;
    }
    if(childNum == 3)
    {
        child->other_info = parent->other_info;
    }
}

ID(58)
{
    if(childNum == 1)
    {
        TypeInfo* exp = (TypeInfo*)malloc(sizeof(TypeInfo));
        child->other_info = exp; 
    }
}

// SD(9)
// {
//     TypeInfo *specifier = (TypeInfo*)malloc(sizeof(TypeInfo));
//     specifier->sType = parent->first_child->str;
//     parent->other_info = specifier;
// }


SDS(18, 19)
{

    const char *func_name = parent->first_child->str + 4;
    FuncInfo *varList = (FuncInfo*)(parent->other_info);
    int result = addNewFunc(func_name, varList, parent->loc_line);
    parent->other_info = NULL;
    if(result == 0)
        printf("Error type 4 at Line %d: Redefined function \"%s\".\n", 
            parent->loc_line, func_name);
    else if(result == -1)
        printf("Error type 19 at Line %d: Function \"%s\" has been defined with confliction.\n", 
            parent->loc_line, func_name);
    freeTempParamList(varList->param_list);
    free(varList);
    parent->other_info = NULL;
}

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
    addTempFuncParam(varList, varDec->str + 4, paramDec->sType, paramDec->sDimension);
    parent->other_info = NULL;
}

SD(22)
{
    TypeInfo *varDec = (TypeInfo*)(parent->first_child->next_brother->other_info);
    TypeInfo *paramDec = (TypeInfo*)malloc(sizeof(TypeInfo));
    if(varDec->sType != NULL)
    {
        paramDec->sType = varDec->sType;
        paramDec->sDimension = varDec->sDimension;
        paramDec->sValid = varDec->sValid;
        parent->other_info = paramDec;
    }
    else
    {
        // 结构体定义非法，不能用该结构体定义变量
        printf("Error type 17 at Line %d: Struct has not been defined.\n", parent->loc_line);
        parent->other_info = NULL;
    }
}

SD(28)
{
    TypeInfo* stmt = (TypeInfo*)(parent->other_info);
    TypeInfo* exp = (TypeInfo*)(parent->first_child->next_brother->other_info);
    if(exp->sValid)
    {
        if(exp->sDimension != 0 
            || stmt->sType == NULL 
            || strcmp(exp->sType, stmt->sType) != 0)
            printf("Error type 8 at Line %d: Unmatch return value type.\n", parent->loc_line);
    }

}

SDS(50, 51)
{
    const char* func_name = parent->first_child->str + 4;
    Symbol *symbol_in_table = getFuncSymbol(func_name);
    if(symbol_in_table == NULL)
    {
        if(getSymbol(func_name) != NULL)
            printf("Error type 11 at Line %d: Value %s is not a function.\n",
                parent->loc_line, func_name);
        else
            printf("Error type 2 at Line %d: Function %s has not been defined.\n",
                parent->loc_line, func_name);
        return;
    }
    // 在变量符号表中查找该ID
    // TODO change find symbol function
    FuncInfo *func_call = (FuncInfo*)(parent->first_child->other_info);
    FuncInfo *func_in_table = (FuncInfo*)(symbol_in_table->u.detail);
    if(!checkFuncParamMatch(func_in_table, func_call))
        printf("Error type 9 at Line %d: Function \"%s\" call is not match its defination.\n", 
            parent->loc_line, func_name);
    else
    {
        int old_size = func_in_table->use_line_size;
        func_in_table->use_line = expandFuncUseLine(func_in_table->use_line, old_size);
        func_in_table->use_line[old_size] = -(parent->loc_line);
        func_in_table->use_line_size = old_size + 1;
    }

    TypeInfo* exp = (TypeInfo*)(parent->other_info);
    exp->sType = func_in_table->return_type;
    exp->sDimension = 0;
    if(exp->sType == NULL)
        exp->sValid = 0;
    else
        exp->sValid = 1;

    freeTempParamList(func_call->param_list);
}


SDS(57, 58)
{
    FuncInfo *args = (FuncInfo*)(parent->other_info);
    TypeInfo *exp = (TypeInfo*)(parent->first_child->other_info);
    if(exp->sValid)
        addTempFuncParam(args, NULL, exp->sType, exp->sDimension);
    parent->other_info = NULL;
}



/**************************************************************/
/**************************************************************/
/* 处理结构体定义和使用 */

/* StructSPecifier -> STRUCT OptTag LC DefLIst RC */
ID(11)
{
    if(childNum == 4)
    {
        AST_node *optTag = parent->first_child->next_brother;
        /* 无名结构体的定义 */
        if(optTag->first_child == NULL)
        {
            stackPush(NULL, 1);
        }
        /* 非无名结构体则把该结构体的名称压栈 */
        else
        {
            stackPush(optTag->first_child->str + 4, 0);
        }
        /* stackAddRegion函数会处理结构体内定义变量的情况 */
    }
}

ID(53)
{
    if(childNum == 1)
    {
        TypeInfo *exp_ = (TypeInfo *)malloc(sizeof(TypeInfo));
        exp_->iDimension = 0;
        child->other_info = exp_;
    }

}

/* Specifier -> StructSpecifier */
SD(10)
{
    TypeInfo *specifier = (TypeInfo*)malloc(sizeof(TypeInfo));
    TypeInfo *structSpecifier = (TypeInfo*)(parent->first_child->other_info);
    /* structSpecifier->sValid表征符号表有没有该结构体名称 */
    if(!structSpecifier->sValid)
        specifier->sValid = 0;
    else 
        specifier->sType = structSpecifier->sType;
    parent->other_info = specifier;
}

/* StructSpecifier -> STRUCT OptTag LC DefList RC */
SD(11)
{
    Symbol *struct_symbol = stackPop();
    TypeInfo *structSpecifier = (TypeInfo*)malloc(sizeof(TypeInfo));
    structSpecifier->sType = struct_symbol->name;
    structSpecifier->sValid = 1; 
    parent->other_info = structSpecifier;
}

/* StructSpecifier -> STRUCT Tag */
/* Tag -> ID */
SD(12)
{
    const char *struct_name = parent->first_child->next_brother->first_child->str + 4;
    Symbol *struct_symbol = getSymbolFull(struct_name);
    TypeInfo *structSpecifier = (TypeInfo*)malloc(sizeof(TypeInfo));
    if(struct_symbol == NULL) 
    {
        printf("Error type 17 at Line %d: Struct \"%s\" has not been defined.\n",
           parent->loc_line, struct_name);
        structSpecifier->sValid = 0;
    }
    else
    {
        structSpecifier->sValid = 1;
        structSpecifier->sType = struct_symbol->type; 
    }
    parent->other_info = structSpecifier;
}

/* OptTag -> ID */
SD(13)
{
    const char *struct_name = parent->first_child->str + 4;
    if(getSymbolFull(struct_name) != NULL)
        printf("Error type 16 at Line %d: Struct \"%s\" has been redefined.\n",
             parent->loc_line, struct_name);
}

/* Exp -> Exp DOT ID */
SD(53)
{
    TypeInfo *parent_info = (TypeInfo *)malloc(sizeof(TypeInfo));
    /* 表明该表达式是左值 */
    parent_info->nextInfo = (void *)1;
    parent_info->sValid = 0;
    parent->other_info = parent_info;

    TypeInfo *exp_ = (TypeInfo*)(parent->first_child->other_info);
    if(exp_->sValid) 
    {
        if(strcmp(exp_->sType, "int") == 0 || strcmp(exp_->sType, "float") == 0 
            || exp_->sDimension != 0) 
        {
            printf("Error type 13 at Line %d: Exp is not a struct.\n", parent->loc_line);
            return;
        }
    }
    else
        return;
    const char* struct_name = exp_->sType;
    const char *region_id = parent->first_child->next_brother->next_brother->str + 4;
    Symbol *region_symbol = findRegionInStruct(struct_name, region_id);
    if(region_symbol == NULL)
        printf("Error type 14 at Line %d: \"%s\" is not a region in struct \"%s\".\n",
             parent->loc_line, region_id, struct_name);
    else
    {
        parent_info->sValid = 1;
        parent_info->sType = region_symbol->type;
        parent_info->sDimension = region_symbol->dimension;
    }
}





void initTable_lxs()
{
    IS(6, 11, 18, 20, 22, 23, 24, 27, 28, 29, 30, 31, 50, 53, 57, 58, 59);
    SS(10, 11, 12, 13, 18, 19, 20, 21, 22, 28, 50, 51, 53, 57, 58);
}
