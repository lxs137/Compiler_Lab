#ifndef Pointer_H
#define Pointer_H

#include <stdarg.h>
#include "SDTAction.h"

#define Alloc(p1, p2) assert((p1) == NULL); alloc(proNum, allocatorRole, (void **)&(p1), (void *)(p2))
#define OverWrite(p1, p2) overwrite(proNum, allocatorRole, (void **)&(p1), (void *)(p2))
#define Noalloc(p) noalloc((void **)&(p))
#define Dealloc(p) assert((p) != NULL); dealloc(proNum, (void **)&(p), parent)

typedef enum {true, false} bool;
typedef enum {IRole, SRole} AllocatorRole;
#define UNALLOC 0
#define OVERWRITE 1
#define NOALLOC 2

void alloc(int proNum, AllocatorRole role, void **pointer, void *value);
void overwrite(int proNum, AllocatorRole role, void **pointer, void *value);
void noalloc(void **pointer);
void dealloc(int proNum, void **pointer, AST_node *parent);
void printPointerLog();

#endif
