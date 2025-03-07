        .global savectx
        .global jumpctx

savectx:
    mov (%rsp), %rcx
    mov %rcx, (%rdi)
    mov %rsp, 8(%rdi)
    mov %rbp, 16(%rdi)
    xor %rax, %rax
    ret

jumpctx:
    mov 8(%rdi), %rsp
    mov (%rdi), %rcx
    mov %rcx, (%rsp)
    mov 16(%rdi), %rbp
    mov $1, %rax
    ret
