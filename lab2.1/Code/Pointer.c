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

void alloc(int proNum, void **pointer, void *value, int isTypeInfo, int expectDeallocProNum, ...)
{
    va_list argptr;
    va_start(argptr, expectDeallocProNum);
    /* assert(expectDeallocProNum != 0); */
    ExpectProNum *ep = (ExpectProNum *)malloc(sizeof(ExpectProNum));
    ep->proNum = expectDeallocProNum;
    ExpectProNum *tmp = ep;
    while (expectDeallocProNum != 0)
    {
	expectDeallocProNum = va_arg(argptr, int);
	tmp->next = (ExpectProNum *)malloc(sizeof(ExpectProNum));
	tmp = tmp->next;
	tmp->proNum = expectDeallocProNum;
    }
    tmp->next = NULL;

    /* assert(value != NULL); */
    /* assert(*pointer == NULL); */
    *pointer = value;

    PointerLog *newPl = (PointerLog *)malloc(sizeof(PointerLog));
    newPl->allocProNum = proNum;
    newPl->expectDeallocProNums = ep;
    /* 不存在0号产生式，用0代表未赋值 */
    newPl->deallocProNum = 0;
    newPl->isTypeInfo = isTypeInfo;
    newPl->nextPointerLog = NULL;

    if (pl == NULL)
    {
	pl = newPl;
    }
    else
    {
	pl->nextPointerLog = newPl;
    }
}

void dealloc(int proNum, void **pointer)
{
    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog)
    {
	if (tmp->pointer == pointer)
	{
	    ExpectProNum *ep = tmp->expectDeallocProNums;
	    while (ep == NULL || ep->proNum == proNum) ;
	    /* assert(ep != NULL); */
	    /* assert(tmp->deallocProNum == 0); */
	    tmp->deallocProNum = proNum;

	    /* assert(*pointer != NULL); */
	    /* if (tmp->isTypeInfo == 1) */
	    /* { */
		/* TypeInfo *info = *((TypeInfo **)tmp); */
		/* assert(info->nextInfo == NULL); */
	    /* } */
	    *pointer = NULL;
	    return;
	}
    }
    /* assert(0); */
}
