#ifndef Pointer_H
#define Pointer_H

#include <stdarg.h>

void alloc(int proNum, void **pointer, void *value, int isTypeInfo, int expectDeallocProNum, ...);
void dealloc(int proNum, void **pointer);

#endif
