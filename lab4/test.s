.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
f1:
sub $sp, $sp, 28
li $t1, 1
move $t0, $t1
sw $t0, -16($fp)
lw $t0, -12($fp)
lw $t1, -16($fp)
beq $t0, $t1, l4
li $t1, 0
move $t0, $t1
sw $t0, -20($fp)
j l5
l4:
li $t1, 1
move $t0, $t1
sw $t0, -20($fp)
l5:
lw $t0, -20($fp)
li $t1, 0
beq $t0, $t1, l2
li $t1, 1
move $t0, $t1
sw $t0, -24($fp)
move $sp, $fp
lw $t0, -24($fp)
lw $fp, -4($sp)
move $v0, $t0
jr $ra
j l3
l2:
li $t1, 1
move $t0, $t1
sw $t0, -28($fp)
lw $t0, -12($fp)
lw $t1, -28($fp)
add $t2, $t0, $t1
sw $t2, -32($fp)
sw $fp, -4($sp)
lw $t0, -32($fp)
sw $t0, -12($sp)
sw $ra, -8($fp)
move $fp, $sp
sub $sp, $sp, 12
jal f1
sw $t0, -36($fp)
lw $ra, -8($fp)
lw $t0, -12($fp)
lw $t1, -36($fp)
add $t2, $t0, $t1
sw $t2, -40($fp)
move $sp, $fp
lw $t0, -40($fp)
lw $fp, -4($sp)
move $v0, $t0
jr $ra
l3:
main:
move $fp, $sp
sw $fp, -4($fp)
sub $sp, $sp, 8
sub $sp, $sp, 12
li $t1, 3
move $t0, $t1
sw $t0, -12($fp)
sw $fp, -4($sp)
lw $t0, -12($fp)
sw $t0, -12($sp)
sw $ra, -8($fp)
move $fp, $sp
sub $sp, $sp, 12
jal f1
sw $t0, -16($fp)
lw $ra, -8($fp)
lw $t0, -16($fp)
move $a0, $t0
li $v0, 1
syscall
li $t1, 1
move $t0, $t1
sw $t0, -20($fp)
move $sp, $fp
lw $t0, -20($fp)
lw $fp, -4($sp)
move $v0, $t0
jr $ra
