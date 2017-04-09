#include "symbol_table.h"
#include "SDTAction.h"

static int compSymbol(const void *p1, const void *p2)
{
    return strcmp(((Symbol *)p1)->name, ((Symbol *)p2)->name);
}

static void *dupSymbol(void *p)
{
    void *dup_p;
    dup_p = calloc(1, sizeof(Symbol));
    memmove(dup_p, p, sizeof(Symbol));
    return dup_p;
}

static void *dupFuncSymbol(void *p)
{
    void *dup_p;
    void *dup_func_info;
    dup_func_info = calloc(1, sizeof(FuncInfo));
    memmove(dup_func_info, ((Symbol*)p)->u.detail, sizeof(FuncInfo));
    dup_p = calloc(1, sizeof(Symbol));
    memmove(dup_p, p, sizeof(Symbol));
    ((Symbol*)dup_p)->u.detail = dup_func_info;
    return dup_p;
}

static void deleteSymbol(void *p)
{
    free(p);
}

static void deleteFuncSymbol(void *p)
{
    free(((Symbol*)p)->u.detail);
    free(p);
}

SymbolTable *newSymbolTable()
{
    jsw_rbtree_t *rbtree;
    rbtree = jsw_rbnew(compSymbol, dupSymbol, deleteSymbol);
    return rbtree;
}

void delSymbolTable(SymbolTable *st)
{
    jsw_rbdelete(st);
}

int insertSymbol(SymbolTable *st, const char *name, int kind,
 const char *type, int dimension, void* next_detail, void *p)
{
    int ret;
    
    Symbol *symbol = calloc(1, sizeof(Symbol));
    symbol->name = name;
    symbol->kind = kind;
    symbol->type = type;
    symbol->dimension = dimension;
    symbol->u.next = next_detail;
    symbol->p = p;
    
    ret = jsw_rbinsert(st, (void *)symbol);
    if (ret == 0)
    {
        printf("failed to insert the symbol with name %s and pointer %p\n", name, p);
        free(symbol);
        return -1;
    }
    free(symbol);
    return 0;
}

int eraseSymbol(SymbolTable *st, const char *name)
{
    int ret;
    Symbol *symbol = calloc(1, sizeof(Symbol));
    symbol->name = name;
    
    ret =jsw_rberase(st, (void *)symbol);
    if (ret == 0)
    {
        printf("failed to erase the symbol with name %s\n", name);
        free(symbol);
        return -1;
    }
    free(symbol);
    return 0;
}

void *findSymbol(SymbolTable *st, const char *name)
{
    Symbol *symbol, symbol_find;
    symbol_find.name = name;
    symbol = jsw_rbfind(st, &symbol_find);
    return symbol;
}

void printSymbolTable(SymbolTable *st)
{
    jsw_rbtrav_t *rbtrav;
    rbtrav = jsw_rbtnew();
    
    for (Symbol *symbol = jsw_rbtfirst(rbtrav, st);
            symbol != NULL;
            symbol = jsw_rbtnext(rbtrav))
    {
        printf("name: %s, pointer: %p\n", symbol->name, symbol->p);
    }
    
    free(rbtrav);
}

int addSymbol(const char *name, void *p)
{
    TypeInfo *info = (TypeInfo*)p->other_info;
    return insertSymbol(globalSymbolTable, name, 0,
     info->sType, info->sDimension, NULL, (void *)p);
}

int delSymbol(const char *name)
{
    return eraseSymbol(globalSymbolTable, name);
}

AST_node *getSymbol(const char *name)
{
    void *p = findSymbol(globalSymbolTable, name);
    if (p == NULL)
    {
        return NULL;
    }
    else
    {
        return ((Symbol *)p)->p;
    }
}

void cleanUpSymbolTable()
{
    delSymbolTable(globalSymbolTable);
    delSymbolTable(globalFuncSymbolTable);
}


SymbolTable *newFuncSymbolTable()
{
    jsw_rbtree_t *rbtree;
    rbtree = jsw_rbnew(compSymbol, dupFuncSymbol, deleteFuncSymbol);
    return rbtree;
}

void addFuncParam(FuncInfo *function, const char *param_name,
 const char*param_type, int param_dimension)
{
    Symbol *param = (Symbol*)malloc(sizeof(Symbol));
    param->name = param_name;
    param->kind = 0;
    param->type = param_type;
    param->dimension = param_dimension;
    param->u.next = NULL;
    function->param_num += 1;
    if(function->param_list == NULL)
    {
        function->param_list = param;
    }
    else
    {
        Symbol *last_param = function->param_list;
        while(last_param->u.next != NULL)
            last_param = last_param->u.next;
        last_param->u.next = param;
    }
}
// 将语法树节点中存的函数定义信息存入符号表
// 若返回1表示成功
// 返回0表示失败,函数重复定义; 
// 返回-1表示失败，函数多次声明相互冲突、声明和定义相互冲突
int addNewFunc(const char *name, FuncInfo *function)
{
    void *symbol = findSymbol(globalFuncSymbolTable, name);
    // 符号表中不存在该函数名
    if(symbol == NULL)
    {
        Symbol *func_symbol = (Symbol*)malloc(sizeof(Symbol));
        func_symbol->name = name;
        func_symbol->kind = 2;
        func_symbol->type = function->return_type;
        func_symbol->u.detail = function;
        int insert_result = insertFuncIntoTable(func_symbol);
        free(func_symbol);
        return ((insert_result == 0) ? 1:0);
    }
    else 
    {
        Symbol *func_symbol = (Symbol*)symbol;
        FuncInfo *func_in_table = (FuncInfo*)func_symbol->u.detail;
        if(func_symbol->kind != 2 
            || (func_in_table->status == 1 && function->status == 1))
            return 0;
        if(strcmp(func_in_table->return_type, function->return_type) != 0)
            return -1;
        int check_result = checkFuncParam(func_in_table, function);
        // 修改函数定义声明状态
        if(check_result == 1 
            && function->status == 1 && func_in_table->status == 0)
            func_in_table->status = 1;
        return check_result;
    }
}

int insertFuncIntoTable(Symbol *function)
{
    int result;
    // 将function的param插入符号表
    Symbol *param = ((FuncInfo*)(function->u.detail))->param_list;
    Symbol *first_param = param, *cur_param = param;
    if(param != NULL)
    {
        insertSymbol(globalSymbolTable, param->name, param->kind, 
            param->type, param->dimension, param->u.next, param->p);
        cur_param = (Symbol*)findSymbol(globalSymbolTable, param->name);
        ((FuncInfo*)(function->u.detail))->param_list = cur_param;
        while(param->u.next != NULL)
        {
            param = param->u.next;
            insertSymbol(globalSymbolTable, param->name, param->kind, 
                param->type, param->dimension, param->u.next, param->p);
            cur_param->u.next = (Symbol*)findSymbol(globalSymbolTable, param->name);
            cur_param = cur_param->u.next;
        }
    }

    // 将函数信息插入符号表
    result = jsw_rbinsert(globalFuncSymbolTable, (void *)function);
    // 使function中的参数指针仍然指向临时参数列表
    ((FuncInfo*)(function->u.detail))->param_list = first_param;
    if (result == 0)
    {
        printf("failed to insert the function symbol with name %s\n",
         function->name);
        return -1;
    }        
    return 0;
}

void freeTempParamList(Symbol *param_list)
{
    Symbol *cur_param = param_list;
    while(param_list != NULL)
    {
        cur_param = param_list;
        param_list = param_list->u.next;
        free(cur_param);
    } 
}

int checkFuncParam(FuncInfo *func_exist, FuncInfo *func_uncheck)
{
    if(func_exist->param_num != func_uncheck->param_num)
        return -1;
    Symbol *exi_param = func_exist->param_list;
    Symbol *unc_param = func_uncheck->param_list;
    while(exi_param != NULL)
    {
        if(exi_param->kind != unc_param->kind 
            || strcmp(exi_param->type, unc_param->type) != 0
            || exi_param->dimension != unc_param->dimension)
            return -1;
        exi_param = exi_param->u.next;
        unc_param = unc_param->u.next;
    }
    return 1;
}

Symbol *getFuncSymbol(const char *func_name)
{
    void *symbol = findSymbol(globalFuncSymbolTable, func_name);
    if(symbol == NULL)
        return NULL;
    return (Symbol*)symbol;
}