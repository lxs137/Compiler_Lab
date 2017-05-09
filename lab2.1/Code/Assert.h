#ifndef Assert_H
#define Assert_H

#define AssertFunctionTypeInfo(info) \
    assert(info != NULL); \
    assert(((TypeInfo *)info)->typeKind == FunctionType); \
    assert(((TypeInfo *)info)->node != NULL);

#endif
