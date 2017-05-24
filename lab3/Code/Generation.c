#include "list.h"
#include "Generation.h"
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

Value* new_value(int kind, int value) 
{
    Value *new_value = (Value*)malloc(sizeof(Value));
    new_value->kind = kind;
    if(kind == Const)
        new_value->u.value = value;
    else
        new_value->u.no = value;
    char *value_str = (char*)malloc(sizeof(char) * 10);
    switch(kind)
    {
        case 0:
            sprintf(value_str, "v%d", value);
            break;
        case 1:
            sprintf(value_str, "t%d", value);
            break;
        case 2:
            sprintf(value_str, "l%d", value);
            break;
        case 3:
            if(value == 0)
                sprintf(value_str, "main");
            else
                sprintf(value_str, "f%d", value);
            break;
        case 4:
            sprintf(value_str, "#%d", value);
            break;
        case 5:
            sprintf(value_str, "&v%d", value);
            break;
        case 6:
            sprintf(value_str, "*v%d", value);
            break;
    }
    new_value->str = value_str;
    return new_value;
}

void free_value(Value *value)
{
    if(value == NULL)
        return;
    free(value->str);
    free(value);
}

IR* gen_IR(int kind, Value *target, ...)
{
    if(kind < 0 || kind >12)
        return NULL;
    IR *ir = (IR*)malloc(sizeof(IR));
    ir->kind = kind;
    ir->target = target;
    ir->arg1 = NULL;
    ir->arg2 = NULL;
    ir->u.op = NULL;
    va_list ap;
    va_start(ap, target);
    switch(kind)
    {
        case 0:case 1:case 4:case 6:case 8:case 10:case 11:case 12:
            break;
        case 3:case 7: case 9:
            ir->arg1 = va_arg(ap, Value*);
            break;
        case 2:
            ir->arg1 = va_arg(ap, Value*);
            ir->arg2 = va_arg(ap, Value*);
            ir->u.op = va_arg(ap, char*);
            break;
        case 5:
            ir->arg1 = va_arg(ap, Value*);
            ir->arg2 = va_arg(ap, Value*);
            ir->u.relop = va_arg(ap, char*);
            break;
    }
    va_end(ap);
    list_rpush(IR_list, list_node_new(ir));
    return ir;
}

void free_IR(void *val)
{
    if(val == NULL)
        return;
    IR *ir = (IR*)val;
    free_value(ir->target);
    free_value(ir->arg1);
    free_value(ir->arg2);
    free(ir);
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

void traverse_IR_list(void (*action)(list_node_t*))
{
    list_node_t *node;
    list_iterator_t *it = list_iterator_new(IR_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) 
    {
        action(node);
    }
    list_iterator_destroy(it);
}

void print_IR(list_node_t *ir_node)
{
    IR *ir = (IR*)(ir_node->val);
    switch(ir->kind)
    {
        case 0:
            printf("LABEL %s :\n", ir->target->str);
            break;
        case 1:
            printf("FUNCTION %s :\n", ir->target->str);
            break;
        case 2:
            printf("%s := %s %s %s\n", ir->target->str, 
                ir->arg1->str, ir->u.op, ir->arg2->str);
            break;
        case 3:
            printf("%s := %s\n", ir->target->str, ir->arg1->str);
            break;
        case 4:
            printf("GOTO %s\n", ir->target->str);
            break;
        case 5:
            printf("IF %s %s %s GOTO %s\n", ir->arg1->str,
                ir->u.relop, ir->arg2->str, ir->target->str);
            break;
        case 6:
            printf("RETURN %s\n", ir->target->str);
            break;
        case 7:
            printf("DEC %s %d\n", ir->target->str, ir->arg1->u.value);
            break;
        case 8:
            printf("ARG %s\n", ir->target->str);
            break;
        case 9:
            printf("%s := CALL %s\n", ir->target->str, ir->arg1->str);
            break;
        case 10:
            printf("PARAM %s\n", ir->target->str);
            break;
        case 11:
            printf("READ %s\n", ir->target->str);
            break;
        case 12:
            printf("WRITE %s\n", ir->target->str);
            break;
    }
}

void generate_jump_target(int label_count, int func_count)
{
    label_jump = (JumpTarget*)malloc(sizeof(JumpTarget) * label_count);
    func_jump = (CalTarget*)malloc(sizeof(CalTarget) * func_count);
    int label_index = 0, func_index = 0;
    list_node_t *node;
    IR *ir;
    list_iterator_t *it = list_iterator_new(IR_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) 
    {
        ir = (IR*)(node->val);
        if(ir->kind == Fun) {
            // 排除main函数
            if(ir->target->u.no == 0)
                continue;
            func_jump[ir->target->u.no - 1].target = node;
            assert(func_index < func_count);
            func_index++;
        }
        else if(ir->kind == Label) {
            label_jump[ir->target->u.no - 1].target = node;
            assert(label_index < label_count);
            label_index++;
        }
        else if(ir->kind == Call) {
            func_jump[ir->target->u.no - 1].call_count++;
        }
        else if(ir->kind == Goto) {
            label_jump[ir->target->u.no - 1].goto_count++;
        }
        else if(ir->kind == GotoRel) {
            label_jump[ir->target->u.no - 1].goto_rel_count++;
        }
    }
    list_iterator_destroy(it);
}

// 控制流优化
void peep_hole_control(list_node_t *cur_node)
{
    IR *ir = (IR*)(cur_node->val);
    list_node_t *n_n_node;
    IR *n_n_ir = NULL;
    if(ir->kind == Goto) 
    {
        // remove ir whose kind is not Label
        if(cur_node->next != NULL) 
        {
            list_node_t *n_node, *rm_node;
            n_node = rm_node = cur_node->next;
            IR *n_ir = (IR*)(n_node->val);
            while(n_ir->kind != Label) 
            {
                n_node = n_node->next;
                list_remove(IR_list, rm_node);
                if(n_node == NULL)
                    break;
                else
                    n_ir = (IR*)(n_node->val);
            }
        }
    }
    if(ir->kind == Goto || ir->kind == GotoRel)
    {
        do 
        {        
            if(n_n_ir != NULL) {
                ir->target->u.no = n_n_ir->target->u.no;
                ir->target->str = n_n_ir->target->str;
            }
            n_n_node = label_jump[ir->target->u.no - 1].target->next;
            if(n_n_node == NULL)
                break;
            n_n_ir = (IR*)(n_n_node->val);
        } while(n_n_ir->kind == Goto);
    }
}

void peep_hole()
{
    generate_example_ir();
    traverse_IR_list(print_IR);
    printf(">>>>>>>>>>>>>>>>>>>>\n");
    generate_jump_target(3, 0);
    traverse_IR_list(peep_hole_control);
    traverse_IR_list(print_IR);
    free(label_jump);
    free(func_jump);
}

void generate_example_ir()
{
    printf("*****************\n");
    del_IR_list();
    IR_list = new_IR_list();
    
    gen_IR(GotoRel, new_value(L, 1), new_value(V, 1), new_value(V, 2), "<");
    gen_IR(Label, new_value(L, 1));
    gen_IR(Goto, new_value(L, 2));
    gen_IR(Label, new_value(L, 2));
    gen_IR(Goto, new_value(L, 3));
    gen_IR(Write, new_value(V, 1));
    gen_IR(Label, new_value(L, 3));
    gen_IR(Calculate, new_value(V, 1), new_value(V, 2), new_value(V, 3), "*");
}