#include <string.h>
#include "MIPS_asm.h"
#include "stack_manage.h"
#include "Generation.h"
#include "MIPS_asm.h"

void prepare(Value *value, int num)
{
    if(value == NULL)
        return;
    if(value->kind == Const) {
        asm_li(reg("t", num), value->u.value);
        return;
    }
    ASM_Block *block = NULL;
    VarInfo *var = find_var(value->u.no, &block);
    if(var == NULL)
        return;
    int offset = block->basis + var->offset;
    if(value->kind == V) {
        asm_lw(reg("t", num), addr_im_reg(-offset, reg_sp()));
    }
    else if(value->kind == Address) {
        asm_la(reg("t", num), addr_im_reg(-offset, reg_sp()));
    }
    else if(value->kind == Content) {
        asm_lw(reg("t", num), addr_im_reg(-offset, reg_sp()));
        asm_lw(reg("t", num), addr_reg(reg("t", num)));
    }
}

void save(Value *value, int num)
{
    if(value == NULL)
        return;
    ASM_Block *block = NULL;
    VarInfo *var = find_var(value->u.no, &block);
    if(var == NULL) {
        var = add_var(4, value->u.no);
        block = asm_block_stack->top;
    }
    if(block == NULL)
        return;
    int offset = block->basis + var->offset;
    if(value->kind == V) {
        asm_sw(reg("t", num), addr_im_reg(-offset, reg_sp()));
    }
    else if(value->kind == Content) {
        asm_lw(reg("t", 3), addr_im_reg(-offset, reg_sp()));
        asm_sw(reg("t", num), addr_reg(reg("t", 3)));
    }

}

void genAsm(list_node_t *node)
{
    IR *ir = (IR *)(node->val);
    switch(ir->kind)
    {
        case Label:
            p_asm("l%d:\n", ir->target->u.no);
            break;
        case Fun:
            p_asm("f%d:\n", ir->target->u.no);
            break;
        case Return:
            asm_mv(reg_sp(), reg_fp());
            asm_lw(addr_im_reg(imm(-4), reg_sp()), reg_fp());
            p_asm("jr $ra");
            break;
        case Call:
            asm_sw(reg_fp(), addr_im_reg(imm(-4), reg_sp()));
            asm_sw(reg_ra(), addr_im_reg(imm(-8), reg_sp()));
            list_node_t *tmp = node->prev;
            int i = 1;
            while (((IR *)node->val)->kind == Arg)
            {
                prepare(((IR *)node->val)->target, 0);
                asm_sw(reg("t", 0), addr_im_reg(imm(-4 - i * 4), reg_sp()));
                tmp = tmp->prev;
                i++;
            }
            asm_mv(reg_fp(), reg_sp());
            asm_sub(reg_sp(), reg_sp(), 4 * (i + 1));
            break;
        case Calculate:
            prepare(ir->arg1, 0);
            prepare(ir->arg2, 1);
            asm_add(reg("t", 2), reg("t", 0), reg("t", 1));
            /* asm_sw(reg("t", 2), ir->target->u.value); */
            save(ir->target, 2);
            break;
        case Assign:
            break;
        case Goto:
            asm_j(ir->target->u.value);
            break;
        case GotoRel:
            prepare(ir->arg1, 0);
            prepare(ir->arg2, 1);
            if (!strcmp(ir->u.relop, ">="))
            {
                asm_more_equal(reg("t", 0), reg("t", 1), ir->target->u.value);
            }
            else if (!strcmp(ir->u.relop, ">"))
            {
                asm_more(reg("t", 0), reg("t", 1), ir->target->u.value);
            }
            else if (!strcmp(ir->u.relop, "<="))
            {
                asm_less_equal(reg("t", 0), reg("t", 1), ir->target->u.value);
            }
            else if (!strcmp(ir->u.relop, "<"))
            {
                asm_less_equal(reg("t", 0), reg("t", 1), ir->target->u.value);
            }
            else if (!strcmp(ir->u.relop, "=="))
            {
                asm_equal(reg("t", 0), reg("t", 1), ir->target->u.value);
            }
            else if (!strcmp(ir->u.relop, "!="))
            {
                asm_not_equal(reg("t", 0), reg("t", 1), ir->target->u.value);
            }
            break;
        case Read:
            p_asm("li $v0, 5");
            asm_sys();
            asm_mv(reg("t", 0), reg("a", 0));
            save(ir->target, 0);
            break;
        case Write:
            prepare(ir->target, 0);
            asm_mv(reg("a", 0), reg("t", 0));
            p_asm("li $v0, 1");
            asm_sys();
            break;
    }
}
