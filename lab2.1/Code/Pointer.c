#include "Pointer.h"
#include "SDTAction.h"
#include <malloc.h>
#include <assert.h>

bool isChildProduction(AST_node *node, int proNum)
{
    node = node->first_child;
    if (node == NULL)
    {
	return false;
    }
    for (; node != NULL; node = node->next_brother)
    {
	if (node->proNum == proNum)
	{
	    return true;
	}
    }
    return false;
}

typedef struct PL
{
    int allocProNum;
    AllocatorRole role;
    int deallocProNum;
    void **pointer;
    void **sharePointer;
    struct PL *nextPointerLog;
} PointerLog;

static PointerLog *pl = NULL;

void alloc(int proNum, AllocatorRole role, void **pointer, void *value)
{
    assert(value != NULL);
    assert(*pointer == NULL);
    *pointer = value;

    PointerLog *tmp = pl;
    while (tmp != NULL && tmp->nextPointerLog != NULL && tmp->pointer != &value)
    {
	tmp = tmp->nextPointerLog;
    }
    void **sharePointer;
    if (tmp != NULL)
    {
	sharePointer = tmp->sharePointer;
    }
    else
    {
	sharePointer = NULL;
    }

    PointerLog *newPl = (PointerLog *)malloc(sizeof(PointerLog));
    newPl->allocProNum = proNum;
    newPl->role = role;
    newPl->deallocProNum = UNALLOC;
    newPl->pointer = pointer;
    newPl->sharePointer = sharePointer;
    newPl->nextPointerLog = NULL;

    sharePointer = NULL;
    if (pl == NULL)
    {
	pl = newPl;
    }
    else
    {
	PointerLog *tmp = pl;
	while (tmp->nextPointerLog != NULL)
	{
	    tmp = tmp->nextPointerLog;
	}
	tmp->nextPointerLog = newPl;
    }
}

void overwrite(int proNum, AllocatorRole role, void **pointer, void *value)
{
    assert(*pointer != NULL);
    assert(value != NULL);

    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog)
    {
	if (tmp->pointer == pointer && tmp->deallocProNum == UNALLOC)
	{
	    tmp->deallocProNum = OVERWRITE;
	    break;
	}
    }
    assert(tmp != NULL);

    *pointer = NULL;
    alloc(proNum, role, pointer, value);
}

void noalloc(int proNum, void **pointer, AST_node *parent)
{
    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog)
    {
	if (tmp->pointer == pointer && tmp->deallocProNum == UNALLOC)
	{
	    tmp->deallocProNum = NOALLOC;
	    assert(tmp->allocProNum == proNum || isChildProduction(parent, tmp->allocProNum) == true);
	    break;
	}
    }
    assert(tmp != NULL);
}

void dealloc(int proNum, void **pointer, AST_node *parent)
{
    *pointer = NULL;
    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog)
    {
	if (tmp->pointer == pointer && tmp->deallocProNum == UNALLOC)
	{
	    assert(tmp->role != IRole || tmp->allocProNum == proNum);
	    assert(tmp->role != SRole || isChildProduction(parent, tmp->allocProNum) == true);
	    tmp->deallocProNum = proNum;

	    *pointer = NULL;
	    return;
	}
    }
    assert(0);
}

void assignFieldOf(int proNum, void **pointer)
{
    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog)
    {
	if (tmp->pointer == pointer)
	{
	    if (tmp->sharePointer != NULL)
	    {
		printf("Assing To Share Memory.\n");
		return;
	    }
	}
    }
    assert(0);
}

void printPointerLog()
{
    PointerLog *tmp;
    for (tmp = pl; tmp != NULL; tmp = tmp->nextPointerLog)
    {
	printf("%p alloc: %d dealloc: %d.\n", tmp->pointer, tmp->allocProNum, tmp->deallocProNum);
    }
}
