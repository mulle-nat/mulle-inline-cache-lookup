        .globl _call
                     # @const_call(void*, void*)

# %rdi : self
# %rsi : _param
# %rdx : unused

_call:
        movq    %rsi, %rax
        testq   %rdi, %rdi
        je      .LBB0_5

        movq    -8(%rdi), %rcx
        movq    (%rcx), %rdx
        movl    $407377992,%esi         # imm = 0x18481848
        movq    %rsi,%r9                # imm = 0x18481848
        andq    -8(%rdx), %r9
        cmpq    %rsi, (%rdx,%r9)          # imm = 0x18481848
        jne     .LBB0_3
        leaq    8(%rdx,%r9), %rcx
        jmp     .LBB0_4
.LBB0_3:                                # %select.mid
        addq    $8, %rcx
.LBB0_4:                                # %select.end
        movq    (%rcx), %rcx
        movq    %rax, %rdx
        jmpq    *%rcx                   # TAILCALL
.LBB0_5:                                # %call(void*, unsigned long, void*) [clone .exit]
        xorl    %eax, %eax
        retq


