#include "list.h"
#include "stdlib.h"

list *new_list_dimen()
{
    list *p = malloc(sizeof(list));
    list_new(p, sizeof(int), NULL);
    return p;
}

/* list *add */
