#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "jsw_rbtree.h"
#include "syntax_tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    const char *name;
    void *p;
} Symbol;

typedef struct jsw_rbtree SymbolTable;

SymbolTable *newSymbolTable();
void delSymbolTable(SymbolTable *st);

int insertSymbol(SymbolTable *st, const char *name, void *p);
int eraseSymbol(SymbolTable *st, const char *name);
void *findSymbol(SymbolTable *st, const char *name);
void printSymbolTable(SymbolTable *st);

SymbolTable *globalSymbolTable;

int addSymbol(const char *name, AST_node *p);
int delSymbol(const char *name);
AST_node *getSymbol(const char *name);
void cleanUpSymbolTable();

#endif
