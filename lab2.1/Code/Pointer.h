#ifndef Pointer_H
#define Pointer_H

#include <stdarg.h>

void allocPointer(int proNum, void **pointer, void *value, int isTypeInfo, int expectDeallocProNum, ...);
void deallocPointer(int proNum, void **pointer);

#endif
