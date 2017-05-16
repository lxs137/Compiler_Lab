#include "list.h";

list_t *IR_list;

void free_IR(void *val)
{
    if(val == NULL)
        return;
    else
    {
        IR *ir = (Value*)val;
        free(ir->target);
        free(ir->arg1);
        free(ir->arg2);
        free(ir);
    }
}

list_t *new_IR_list()
{
    list_t *new_list = list_new(free_IR);
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

char* value2str(Value *value)
{
    if(value == NULL)
        return NULL;
    else
        return value->content;
}

Value* str2value(char *str) 
{
    if(str == NULL)
        return NULL;
    else
    {
        Value *value = (Value*)malloc(sizeof(Value));
        if(str[0] == '*')
        {
            value->kind = 3;
            // value->u.name = str + 1;
        }
        else if(str[0] == '&')
        {
            value->kind = 2;
            // value->u.name = str + 1;
        }
        else if(str[0] == '#')
        {
            value->kind = 1;
            // value->u.value = atoi(str + 1);
        }
        else
        {
            value->kind = 0;
            // value->u.name = str;
        }
        value->content = str;
        return value;
    }
}


void print_IR(IR *ir)
{
    switch(ir->kind)
    {
        case 0:
            gen("LABEL %s :\n", value2str(ir->target));
            break;
        case 1:
            gen("FUNCTION %s :\n", value2str(ir->target));
            break;
        case 2:
            gen("%s := %s %s %s\n", value2str(ir->target), 
                value2str(ir->arg1), ir->u.op, value2str(ir->arg2));
            break;
        case 3:
        {
            gen("%s := %s\n", value2str(ir->target), value2str(ir->arg1));
            break;
        }
        case 4:
            gen("GOTO %s\n", value2str(ir->target));
            break;
        case 5:
            gen("IF %s %s %s GOTO %s\n", value2str(ir->arg1),
                ir->u.relop, value2str(ir->arg2), value2str(ir->target));
            break;
        case 6:
            gen("RETURN %s\n", value2str(ir->target));
            break;
        case 7:
            gen("DEC %s %d\n", );
            break;
        case 8:
            gen("ARG %s\n", value2str(ir->target));
            break;
        case 9:
            gen("%s := CALL %s\n", value2str(ir->target), value2str(ir->arg1));
            break;
        case 10:
            gen("PARAM %s\n", value2str(ir->target));
            break;
        case 11:
            gen("READ %s\n", value2str(ir->target));
            break;
        case 12:
            gen("WRITE %s\n", value2str(ir->target));
            break;
    }
}