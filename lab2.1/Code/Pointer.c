#include "Pointer.h"
#include "SDTAction.h"
#include <malloc.h>
/* #include <assert.h> */
/* #define assert(exp) ; */

typedef struct EP
{
    int proNum;
    struct EP *next;
} ExpectProNum;

typedef struct PL
{
    int allocProNum;
    ExpectProNum *expectDeallocProNums;
    int deallocProNum;
    void **pointer;
    int isTypeInfo;
    struct PL *nextPointerLog;
} PointerLog;

static PointerLog *pl = NULL;

void alloc(int proNum, void **pointer, void *value)
{
    assert(*pointer == NULL);
    *pointer = value;
}

void dealloc(int proNum, void **pointer)
{
    assert(*pointer != NULL);
    *pointer = NULL;
}

/* void alloc(int proNum, void **pointer, void *value, int isTypeInfo, int expectDeallocProNum, ...) */
/* { */
/*     va_list argptr; */
/*     va_start(argptr, expectDeallocProNum); */
/*     /1* assert(expectDeallocProNum != 0); *1/ */
/*     ExpectProNum *ep = (ExpectProNum *)malloc(sizeof(ExpectProNum)); */
/*     ep->proNum = expectDeallocProNum; */
/*     ExpectProNum *tmp = ep; */
/*     while (expectDeallocProNum != 0) */
/*     { */
/* 	expectDeallocProNum = va_arg(argptr, int); */
/* 	tmp->next = (ExpectProNum *)malloc(sizeof(ExpectProNum)); */
/* 	tmp = tmp->next; */
/* 	tmp->proNum = expectDeallocProNum; */
/*     } */
/*     tmp->next = NULL; */

/*     /1* assert(value != NULL); *1/ */
/*     /1* assert(*pointer == NULL); *1/ */
/*     *pointer = value; */

/*     PointerLog *newPl = (PointerLog *)malloc(sizeof(PointerLog)); */
/*     newPl->allocProNum = proNum; */
/*     newPl->expectDeallocProNums = ep; */
/*     /1* 不存在0号产生式，用0代表未赋值 *1/ */
/*     newPl->deallocProNum = 0; */
/*     newPl->isTypeInfo = isTypeInfo; */
/*     newPl->nextPointerLog = NULL; */

/*     if (pl == NULL) */
/*     { */
/* 	pl = newPl; */
/*     } */
/*     else */
/*     { */
/* 	pl->nextPointerLog = newPl; */
/*     } */
/* } */

/* void dealloc(int proNum, void **pointer) */
/* { */
/*     PointerLog *tmp; */
/*     for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog) */
/*     { */
/* 	if (tmp->pointer == pointer) */
/* 	{ */
/* 	    ExpectProNum *ep = tmp->expectDeallocProNums; */
/* 	    while (ep == NULL || ep->proNum == proNum) ; */
/* 	    /1* assert(ep != NULL); *1/ */
/* 	    /1* assert(tmp->deallocProNum == 0); *1/ */
/* 	    tmp->deallocProNum = proNum; */

/* 	    /1* assert(*pointer != NULL); *1/ */
/* 	    /1* if (tmp->isTypeInfo == 1) *1/ */
/* 	    /1* { *1/ */
/* 		/1* TypeInfo *info = *((TypeInfo **)tmp); *1/ */
/* 		/1* assert(info->nextInfo == NULL); *1/ */
/* 	    /1* } *1/ */
/* 	    *pointer = NULL; */
/* 	    return; */
/* 	} */
/*     } */
/*     /1* assert(0); *1/ */
/* } */
