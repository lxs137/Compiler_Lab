#include "MIPS_asm.h"
#include "Generation.h"

void start_gen_asm()
{
    global_var_list = list_new(free_var_info);
    asm_block_list = list_new(free_asm_block);
}

void end_gen_asm()
{
    list_destroy(global_var_list);
    list_destroy(asm_block_list);
}

void free_asm_block(void *block)
{
    if(block == NULL)
        return;
    ASM_Block *asm_block = (ASM_Block*)block;
    if(asm_block->var_list == NULL) {
        free(asm_block);
        return;
    }
    list_node_t *node;
    list_iterator_t *it = list_iterator_new(asm_block->var_list, LIST_HEAD);
    VarInfo *var;
    while((node = list_iterator_next(it)))
    {
        var = (VarInfo*)(node->val);
        free(var);
    }
    list_iterator_destroy(it);
    free(asm_block);
}

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

VarInfo *find_var(int no, ASM_Block **block)
{
    list_node_t *node_var;
    list_iterator_t *it_var = list_iterator_new(global_var_list, LIST_HEAD);
    VarInfo *var;
    while ((node_var = list_iterator_next(it_var))) 
    {
        var = (VarInfo*)(node_var->val);
        if(var->no == no) {
            *block = NULL;
            return var;
        }
    }
    list_iterator_destroy(it_var);
    
    list_node_t *node_block;
    list_iterator_t *it_block = list_iterator_new(asm_block_list, LIST_HEAD);
    ASM_Block *cur_block;
    while((node_block = list_iterator_next(it_block)))
    {
        cur_block = (ASM_Block*)(node_block->val);
        it_var = list_iterator_new(cur_block->var_list, LIST_HEAD);
        while((node_var = list_iterator_next(it_var)))
        {
            var = (VarInfo*)(node_var->val);
            if(var->no == no) {
                *block = cur_block;
                return var;
            }
        }
        list_iterator_destroy(it_var);      
    }
    list_iterator_destroy(it_block);
}

void gen_asm_code(list_node_t *node)
{
    IR *ir = (IR*)(node->val);
    switch(ir->kind)
    {
        case 
    }
}