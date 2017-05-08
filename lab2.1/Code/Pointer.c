#include "Pointer.h"
#include <malloc.h>
#include <assert.h>

typedef struct PL {
    int allocProNum;
    int deallocProNum;
    void **pointer;
    int isTypeInfo;
    struct PL *nextPointerLog;
} PointerLog;

static PointerLog *pl = NULL;

void allocPointer(int proNum, void **pointer, void *value, int isTypeInfo)
{
    assert(*pointer == NULL);
    *pointer = value;

    PointerLog *newPl = (PointerLog *)malloc(sizeof(PointerLog));
    newPl->allocProNum = proNum;
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

void deallocPointer(int proNum, void **pointer)
{
    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog)
    {
	if (tmp->pointer == pointer)
	{
	    assert(tmp->deallocProNum == 0);
	    tmp->deallocProNum = proNum;

	    assert(*pointer != NULL);
	    *pointer = NULL;
	    return;
	}
    }
    assert(0);
}

void printPointerLog()
{
    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog)
    {
	printf("%p, alloc at %d, dealloc at %d, ", tmp->pointer, tmp->allocProNum, tmp->deallocProNum);
	if (tmp->isTypeInfo)
	{
	    printf("TypeInfo");
	}
	else
	{
	    printf("Other");
	}
	printf(".\n");
    }
}

void cleanPointerLog()
{
    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; )
    {
	PointerLog *next = tmp->nextPointerLog;
	free(tmp);
	tmp = next;
    }
    assert(pl == NULL);
}
