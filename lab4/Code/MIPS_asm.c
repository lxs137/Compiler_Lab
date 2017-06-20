#include "MIPS_asm.h"

void test_output()
{
    asm_add(reg_sp(), reg_sp(), imm(4));
    asm_lw(reg_ra(), addr_im(5));
    asm_lw(reg("a", 2), addr_im_reg(imm(4), reg_fp()));
    asm_mv(reg("t", 3), reg("v", 2));
    asm_li(reg("s", 2), imm(4));
    asm_more_equal(reg("v", 3), reg_0(), 2);
}