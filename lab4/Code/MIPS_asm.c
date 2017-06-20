#include "MIPS_asm.h"

void free_var_info(void *info)
{
    if(info == NULL)
        return;
    VarInfo *var = (VarInfo*)info;
    free(var);
}

ASM_Block *new_asm_block(int offset)
{
    ASM_Block *block = (ASM_Block*)malloc(sizeof(ASM_Block));
    block->var_list = list_new(free_var_info);
    block->basis = offset;
    block->offset = 0;
    block->next = NULL;
}

void add_var(ASM_Block *block, int size, int no, int is_local)
{
    VarInfo *var = (VarInfo*)malloc(sizeof(VarInfo));
    var->no = no;
    var->is_local = is_local;
    if(is_local) 
    {
        var->offset = block->offset;
        block->offset += size;
        list_rpush(block->var_list, list_node_new(var));
    }
    else
        list_rpush(global_var_list, list_node_new(var));
}

VarInfo *find_var(ASM_Block *block, int no)
{
    list_node_t *node;
    list_iterator_t *it = list_iterator_new(global_var_list, LIST_HEAD);
    VarInfo *var;
    while ((node = list_iterator_next(it))) 
    {
        var = (VarInfo*)(node->val);
        if(var->no == no)
            return var;
    }
    list_iterator_destroy(it);
    it = list_iterator_new(block->var_list, LIST_HEAD);
    while((node = list_iterator_next(it)))
    {
        var = (VarInfo*)(node->val);
        if(var->no == no)
            return var;
    }
    list_iterator_destroy(it);
}