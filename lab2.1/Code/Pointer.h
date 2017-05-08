#ifndef Pointer_H
#define Pointer_H

#include <stdarg.h>

#define Alloc(p1, p2) assert((p1) == NULL); alloc(proNum, (void **)&(p1), (void *)(p2))
#define Dealloc(p) assert((p) != NULL); dealloc(proNum, (void **)&(p))

/* void alloc(int proNum, void **pointer, void *value, int isTypeInfo, int expectDeallocProNum, ...); */
void alloc(int proNum, void **pointer, void *value);
void dealloc(int proNum, void **pointer);

#endif
