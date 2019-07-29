#Casey Haynes
#NOTE: The program outputs up to the correct last prime for this range, but redirecting into
#a text file cuts off the last hundred or so. Not sure why.
#please just run the program to see all primes

#Probably because buffer is not being flushed, because of segmentation fault at end
.section .data
output:
        .asciz " %d\n"
arraylen:
        .int 100000000
.section .bss
        .comm Array, 800000000
.section .text
.globl _start
_start:

        movq $3, %r13 #set p to 3 .......(refinement)........
        movq %r13, %r11 # preserve p at %r11

initialize:
        movq %r13, Array-16(, %r13, 8) #Fill current element with current value of p. Offset -16 to be at 0 array elem.
        incq %r13
        cmp arraylen, %r13
        jl initialize
        movq %r11, %r13 #restore value of p to 2
        #NOTE: r11 is used as coefficient of p in mark label code

mark:
        movq %r11, %rax #move co-p to rax
        mulq %r13 #multiply p by co-p (in rax), store in rax
        cmp arraylen, %rax
        jle interim
        jg find_newp
interim:
        movq $0, Array-16(, %rax, 8)
        incq %r11 #increment co-p
        jmp mark


find_newp:

        incq %r13 #increment p
        movq %r13, %r11 #...refinement...
        cmp arraylen, %r13 #if max n
        jge pre_continue #break
        cmp $0, Array-16(, %r13, 8) #see if that p has already been marked
        je find_newp #if it already has, run loop again
        cmp $0, Array-16(, %r13, 8) #check for marking again
        jne mark #if it hasn't been marked, jump to mark
pre_continue:
        movq $-1, %r15
        subq $2, arraylen
continue:
        incq %r15
        cmp $0, Array(, %r15, 8)
        jne print
        je continue
print:

        lea output(%rip), %rdi
        mov Array(, %r15, 8), %rsi
        xor %rax, %rax
        call printf
        cmp arraylen, %r15
        jle continue


end:
        call exit
