#ifndef Pointer_H
#define Pointer_H

#include <stdarg.h>

#define Alloc(p1, p2) assert((p1) == NULL); alloc(proNum, SRole, (void **)&(p1), (void *)(p2))
#define Dealloc(p) assert((p) != NULL); dealloc(proNum, (void **)&(p))

typedef enum {true, false} bool;
typedef enum {IRole, SRole} AllocatorRole;
#define UNALLOC 0

void alloc(int proNum, AllocatorRole role, void **pointer, void *value);
void dealloc(int proNum, void **pointer);
void printPointerLog();

#endif
