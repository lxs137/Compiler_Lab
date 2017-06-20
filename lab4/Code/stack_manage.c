#include <string.h>
#include "MIPS_asm.h"
#include "stack_manage.h"
#include "Generation.h"

void prepare(Value *value, int num)
{}

void save(Value *value, int num)
{}

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
            p_asm("syscall");
            asm_mv(reg("t", 0), reg("a", 0));
            save(ir->target, 0);
            break;
        case Write:
            prepare(ir->target, 0);
            asm_mv(reg("a", 0), reg("t", 0));
            p_asm("li $v0, 1");
            p_asm("syscall");
            break;
    }
}
