#ifndef MIP32_ASM_H
#define MIP32_ASM_H

#include <stdio.h>
#include "list.h"

#define p_asm(fmt, ...) printf(fmt, ##__VA_ARGS__)

#define imm(val) p_asm("%d", val)
#define val(val) p_asm("%s", val)

#define reg_0() p_asm("$0")
#define reg_sp() p_asm("$sp")
#define reg_fp() p_asm("$fp")
#define reg_ra() p_asm("$ra")
#define reg(type, no) p_asm("$%s%d", type, no)

#define addr_im(val) p_asm("%d", val)
#define addr_reg(reg) p_asm("("),reg,p_asm(")")
#define addr_im_reg(imm, reg) imm,p_asm("("),reg,p_asm(")") 

// add rd, rs, rt
// rd <-- rs + rt
#define asm_add(Rdest, Rsrc, rt) \
    p_asm("add "),Rdest,p_asm(", "),Rsrc,p_asm(", "),rt,p_asm("\n")
#define asm_sub(Rdest, Rsrc, rt) \
    p_asm("sub "),Rdest,p_asm(", "),Rsrc,p_asm(", "),rt,p_asm("\n")
#define asm_mul(Rdest, Rsrc, rt) \
    p_asm("mulo "),Rdest,p_asm(", "),Rsrc,p_asm(", "),rt,p_asm("\n")
#define asm_div(Rdest, Rsrc, rt) \
    p_asm("div "),Rdest,p_asm(", "),Rsrc,p_asm(", "),rt,p_asm("\n")
#define asm_neg(Rdest, Rsrc) \
    p_asm("neg "),Rdest,p_asm(", -"),Rsrc

// sw rt, addr
// store the word from $rt to address
#define asm_sw(Reg, addr) p_asm("sw "),Reg,p_asm(", "),addr,p_asm("\n")
// lw rd, addr
// load the word (32 bit value) at address into $rd
#define asm_lw(Rdest, addr) p_asm("lw "),Rdest,p_asm(", "),addr,p_asm("\n")
// la rd, addr
// load the address into $rd
#define asm_la(Rdest, addr) p_asm("la "),Rdest,p_asm(", "),addr.p_asm("\n")
// li rd, imm
#define asm_li(Rdest, imm) p_asm("li "),Rdest,p_asm(", "),imm,p_asm("\n")
// move rd, rs
#define asm_mv(Rdest, Rsrc) p_asm("move "),Rdest,p_asm(", "),Rsrc,p_asm("\n")


FILE *f_output;

void test_output();

#endif