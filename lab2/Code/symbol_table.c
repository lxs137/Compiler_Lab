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

static void deleteSymbol(void *p)
{
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

int addSymbol(const char *name, AST_node *p)
{
    TypeInfo *info = (TypeInfo*)p->otherInformation;
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
}

void addFuncParam(FuncInfo *function, Symbol *param)
{
    if(param == NULL)
        return;
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
    void *symbol = findSymbol(globalSymbolTable, name);
    // 符号表中不存在该函数名
    if(symbol == NULL)
    {
        Symbol *func_symbol = (Symbol*)malloc(sizeof(Symbol));
        func_symbol->name = name;
        func_symbol->kind = 2;
        func_symbol->type = function->return_type;
        func_symbol->u.detail = function;
        int insert_result = insertFuncIntoTable(globalSymbolTable, func_symbol);
        free(func_symbol);
        return ((insert_result == 0) ? 1:0);
    }
    else 
    {
        Symbol *func_symbol = (Symbol*)symbol;
        if(func_symbol->kind != 2 
            || (((FuncInfo*)(func_symbol->u.detail))->status == 1 
            && function->status == 1))
            return 0;
        return checkFuncParam(func_symbol->u.detail, function);
    }
}

int insertFuncIntoTable(SymbolTable *st, Symbol *function)
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
        param = first_param;   
        while(param != NULL)
        {
            cur_param = param;
            param = param->u.next;
            free(cur_param);
        }
    }

    // 将函数信息插入符号表
    result = jsw_rbinsert(st, (void *)function);
    if (result == 0)
    {
        printf("failed to insert the function symbol with name %s\n",
         function->name);
        return -1;
    }        
    return 0;
}

int checkFuncParam(FuncInfo *func_exist, FuncInfo *func_uncheck)
{
    if(func_exist->param_num != func_uncheck->param_num
        || strcmp(func_exist->return_type, func_uncheck->return_type) != 0)
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