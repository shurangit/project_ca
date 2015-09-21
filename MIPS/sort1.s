.data
newline:
.asciiz "\n"
space:
.asciiz "\t"
number:
.word 10
sortstring:.asciiz "the array after sort is"
bfsortstring:.asciiz "the array before sort is"


.text
main:
# Function prologue -- even main has one
subu $sp, $sp, 120 # allocate stack space -- default of 24
sw $ra, 104($sp) # save return address
sw $fp, 100($sp) # save frame pointer of caller
addiu $fp, $sp, 20 # setup frame pointer for main
la $t4,number
lw $t4,0($t4)
li $t3,0
loop:
beq $t3,$t4,LoopEnd #read
li $v0,5
syscall
mul $t1,$t3,4
addu $a1,$sp,$t1
sw $v0,0($a1)
addiu $t3,$t3,1
j loop
LoopEnd:

li $t3,0  #write before
la $a0,bfsortstring
li $v0,4
syscall

la $a0,newline
syscall

loopwrite1: 
beq $t3,$t4,LoopEndwrite1 
mul $t1,$t3,4
addu $a1,$sp,$t1
#lw $v0,0($a1)
lw $a0,0($a1)
li $v0,1
syscall
la $a0,space
li $v0,4
syscall
addiu $t3,$t3,1
j loopwrite1
LoopEndwrite1:
la $a0,newline
li $v0,4
syscall

addi $t0,$zero,0
loopi:
beq $t0,$t4,loopiend
addi $t1,$zero,0
sub $t2,$t4,$t0
sub $t2,$t2,1
loopj:
beq $t1,$t2,loopjend

mul $t5,$t1,4
addi $t6,$t5,4
add $t5,$t5,$sp
add $t6,$t6,$sp
lw $t5,0($t5)
lw $t6,0($t6)
ble $t5,$t6,swapend
addi $t7,$t5,0
addi $t5,$t6,0
addi $t6,$t7,0
mul $t7,$t1,4
add $t7,$sp,$t7
sw $t5,0($t7)
addi $t7,$t7,4
sw $t6,0($t7)

swapend:
addi $t1,$t1,1
j loopj
loopjend:
addi $t0,$t0,1
j loopi
loopiend:



li $t3,0  #write
loopwrite:
beq $t3,$t4,LoopEndwrite 
mul $t1,$t3,4
addu $a1,$sp,$t1
#lw $v0,0($a1)
lw $a0,0($a1)
li $v0,1
syscall
la $a0,space
li $v0,4
syscall
addiu $t3,$t3,1
j loopwrite
LoopEndwrite:


lw $ra, 104($sp) # get return address from stack
lw $fp, 100($sp) # restore frame pointer of caller
addiu $sp, $sp, 120 # restore stack pointer of caller!

