#include "list.h";

list_t *IR_list;

list_t *new_IR_list()
{
    list_t *new_list = list_new();
    return new_list;
}

void del_IR_list()
{
    list_destroy(IR_list);
}

void traverse_IR_list(void (*action)(IR*))
{
    list_node_t *node;
    list_iterator_t *it = list_iterator_new(IR_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) 
    {
      action((IR*)node->val);
    }
    list_iterator_destroy(it);
}


void print_IR(IR *ir)
{
    switch(ir->kind)
    {
        case 0:
            gen("LABEL %s :\n", ir->target);
            break;
        case 1:
            gen("FUNCTION %s :\n", ir->target);
            break;
        case 2:
            gen("READ %s\n", ir->target);
            break;
        case 3:
            gen("WRITE %s\n", ir->target);
            break;
        case 4:
            gen("%s := %s %s %s\n", ir->target, ir->arg1, ir->u.op, ir->arg2);
            break;
        case 5:
            gen("")
    }
}