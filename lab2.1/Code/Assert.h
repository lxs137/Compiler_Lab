#ifndef Assert_H
#define Assert_H

#define AssertTypeInfo(info) \
    assert(info != NULL); \
    assert(((TypeInfo *)info)->typeKind != 0); \
    assert(((TypeInfo *)info)->node != NULL);

#define AssertFunctionTypeInfo(info) \
    assert(info != NULL); \
    assert(((TypeInfo *)info)->typeKind == FunctionType); \
    assert(((TypeInfo *)info)->node != NULL);

#endif
