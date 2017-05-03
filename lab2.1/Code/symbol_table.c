#include "symbol_table.h"
#include "SDTAction.h"

/* 封装一：把红黑树包装成符号表 */

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

static SymbolTable *newSymbolTable()
{
    jsw_rbtree_t *rbtree;
    rbtree = jsw_rbnew(compSymbol, dupSymbol, deleteSymbol);
    SymbolTable *symbolTable = (SymbolTable *)malloc(sizeof(SymbolTable));
    symbolTable->symbols = rbtree;
    symbolTable->outerSymbolTable = NULL;
    symbolTable->firstInnerSymbolTable = NULL;
    symbolTable->nextSymbolTable = NULL;
    return symbolTable;
}

static void delSymbolTable(SymbolTable *st)
{
    SymbolTable *innerSymbolTable = st->firstInnerSymbolTable;
    while (innerSymbolTable != NULL)
    {
        SymbolTable *nextInnerSymbolTable = innerSymbolTable->nextSymbolTable;
        delSymbolTable(innerSymbolTable);
        innerSymbolTable = nextInnerSymbolTable;
    }
    jsw_rbdelete(st->symbols);
    free(st);
    st = NULL;
}

static int insertSymbol(SymbolTable *st, char *name, AST_node *node)
{
    int ret;
    
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = name;
    symbol->node = node;
    
    ret = jsw_rbinsert(st->symbols, (void *)symbol);
    if (ret == 0)
    {
        printf("failed to insert the symbol with name %s and pointer %p\n", name, node);
        free(symbol);
        return -1;
    }
    free(symbol);
    return 0;
}

static int eraseSymbol(SymbolTable *st, char *name)
{
    int ret;
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = name;
    
    ret =jsw_rberase(st->symbols, (void *)symbol);
    if (ret == 0)
    {
        printf("failed to erase the symbol with name %s\n", name);
        free(symbol);
        return -1;
    }
    free(symbol);
    return 0;
}

static Symbol *findSymbol(SymbolTable *st, char *name)
{
    Symbol *symbol, symbol_find;
    symbol_find.name = name;
    symbol = jsw_rbfind(st->symbols, &symbol_find);
    return symbol;
}

/* 封装二：符号表栈 */

static SymbolTable *globalSymbolTable = NULL;
static SymbolTableStack *symbolTableStack = NULL;
static int stackDepth = 1;

void initSymbolTableStack()
{
    assert(globalSymbolTable == NULL);
    globalSymbolTable = newSymbolTable();
    assert(globalSymbolTable != NULL);
    assert(globalSymbolTable->symbols != NULL);
    assert(globalSymbolTable->outerSymbolTable == NULL);
    assert(globalSymbolTable->firstInnerSymbolTable == NULL);
    assert(globalSymbolTable->nextSymbolTable == NULL);

    assert(symbolTableStack == NULL);
    symbolTableStack = (SymbolTableStack *)malloc(sizeof(SymbolTableStack));
    symbolTableStack->symbolTable = globalSymbolTable;
    symbolTableStack->last = NULL;
    symbolTableStack->next = NULL;
}

static SymbolTable *currentSymbolTable()
{
    assert(symbolTableStack != NULL);
    assert(symbolTableStack->symbolTable != NULL);
    return symbolTableStack->symbolTable;
}

static void pushSymbolTable(SymbolTable *st)
{
    assert(symbolTableStack != NULL);
    assert(symbolTableStack->symbolTable != NULL);
    SymbolTable *t = symbolTableStack->symbolTable->firstInnerSymbolTable;
    if (t == NULL)
    {
        symbolTableStack->symbolTable->firstInnerSymbolTable = st;
    }
    else
    {
        while (t->nextSymbolTable != NULL)
        {
            t = t->nextSymbolTable;
        }
        t->nextSymbolTable = st;
    }

    assert(st != NULL);
    assert(st->symbols != NULL);
    assert(st->outerSymbolTable == NULL);
    st->outerSymbolTable = symbolTableStack->symbolTable;
    assert(st->firstInnerSymbolTable == NULL);
    assert(st->nextSymbolTable == NULL);

    SymbolTableStack *stack = (SymbolTableStack *)malloc(sizeof(SymbolTableStack));
    stack->symbolTable = st;
    stack->last = symbolTableStack;
    stack->next = NULL;

    assert(symbolTableStack->symbolTable == globalSymbolTable || symbolTableStack->last != NULL);
    symbolTableStack->next = stack;
    symbolTableStack = stack;

    stackDepth++;
#ifdef st_stack_debug_print
    printf("symbol table stack depth: %d\n", stackDepth);
#endif
}

static void popSymbolTable()
{
    symbolTableStack = symbolTableStack->last;
    assert(symbolTableStack != NULL);
    free(symbolTableStack->next);
    symbolTableStack->next = NULL;

    stackDepth--;
#ifdef st_stack_debug_print
    printf("symbol table stack depth: %d\n", stackDepth);
#endif
}

void cleanSymbolTableStack()
{
    while (currentSymbolTable() != globalSymbolTable)
    {
        popSymbolTable();
    }
    free(symbolTableStack);
    symbolTableStack = NULL;
}

static void printSymbolTable(SymbolTable *st, int depth, int order)
{
    printf("symbol table %d.%d begin.\n", depth, order);
    jsw_rbtrav_t *rbtrav;
    rbtrav = jsw_rbtnew();
    for (Symbol *symbol = jsw_rbtfirst(rbtrav, st->symbols);
         symbol != NULL;
         symbol = jsw_rbtnext(rbtrav))
    {
        printf("name: %s, pointer: %p\n", symbol->name, symbol->node);
    }
    free(rbtrav);

    SymbolTable *inner = st->firstInnerSymbolTable;
    int i = 0;
    while (inner != NULL)
    {
        i++;
        printSymbolTable(inner, depth + 1, i);
        inner = inner->nextSymbolTable;
    }
    printf("symbol table %d.%d end.\n", depth, order);

    /* while ((st = st->nextSymbolTable) != NULL) */
    /* { */
    /*     printSymbolTable(st, depth, order + 1); */
    /* } */
}

void printGlobalSymbolTable()
{
    printSymbolTable(globalSymbolTable, 1, 1);
}

/* 封装三：联合使用符号表和符号表栈 */
/* 提供符号插入／查找／进入内层符号表／回退到外层符号表API */

int addSymbol(char *name, AST_node *node)
{
    return insertSymbol(currentSymbolTable(), name, node);
}

AST_node *getASTNode(char *name)
{
    SymbolTableStack *stt = symbolTableStack;
    while (stt != NULL)
    {
        SymbolTable *st = stt->symbolTable;
        void *symbol = findSymbol(st, name);
        if (symbol != NULL)
        {
            return ((Symbol *)symbol)->node;
        }
        stt = stt->last;
    }
    return NULL;
}

void createInnerSymbolTable()
{
    SymbolTable *st = newSymbolTable();
    pushSymbolTable(st);
}

void gotoOuterSymbolTable()
{
    popSymbolTable();
}

void cleanSymbolTable()
{
    delSymbolTable(globalSymbolTable);
}
