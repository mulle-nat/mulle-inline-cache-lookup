        .globl _call
                     # @const_call(void*, void*)
_call:
        testq   %rdi, %rdi
        je      .L2

        movq    -8(%rdi), %r9
        movq    (%r9), %rax
        movq    -8(%rax), %rcx
        movl    $407377992,%esi
        andl    %esi, %ecx
        addq    %rcx, %rax
        cmpq    %rsi, (%rax)
        cmove   %rax,%r9
        movq    8(%r9), %rax
        jmp     *%rax
.L2:
        xorl    %eax, %eax
        ret