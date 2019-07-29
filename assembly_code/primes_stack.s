#Casey Haynes
.section .data
output:
        .asciz "%d\n"
.section .bss

.section .text
.globl _start
_start:

allocate:
        movq $100, %r14 # n = 100
        leaq (, %r14, 4), %r15 #calculate number of bytes needed on stack
        and $-16, %r15 #align r15 to 16
        subq %r15, %rsp #byte align stack pointer. Array begins here.

        movq $2, %r13 #set p to 2
        movq %r13, %r11 # preserve p at %r11

initialize:
        movq %r13, -16(%rsp, %r13, 8) #Fill current element with current value of p. Offset -16 to be at 0 array elem.
        incq %r13
        cmp %r14, %r13
        jl initialize
        movq %r11, %r13 #restore value of p to 2
        #NOTE: r11 is used as coefficient of p in mark label code

mark:
        movq %r11, %rax #move co-p to rax
        mulq %r13 #multiply p by co-p (in rax), store in rax
        movq $0, -16(%rsp, %rax, 8)
        incq %r11 #increment co-p
        cmp %r14, %rax
        jl mark

find_newp:
        movq $2, %r11
        incq %r13 #increment p
        cmp $0, -16(%rsp, %r13, 8) #see if that p has already been marked
        je find_newp #if it already has, run loop again
        cmp %r14, %r13 #if max n
        jge pre_continue #break
        cmp $0, -16(%rsp, %r13, 8) #check for marking again
        jne mark #if it hasn't been marked, jump to mark
pre_continue:
        movq $-1, %r15
        subq $2, %r14
continue:
        incq %r15
        cmp $0, (%rsp, %r15, 8)
        jne print
        je continue
print:

        lea output(%rip), %rdi
        mov (%rsp, %r15, 8), %rsi
        xor %rax, %rax
        call printf
        cmp %r14, %r15
        jle continue


end:
        call exit
