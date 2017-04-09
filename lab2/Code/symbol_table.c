#include "symbol_table.h"

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

int insertSymbol(SymbolTable *st, const char *name, void *p)
{
    int ret;
    
    Symbol *symbol = calloc(1, sizeof(Symbol));
    symbol->name = name;
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
    return insertSymbol(globalSymbolTable, name, (void *)p);
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
