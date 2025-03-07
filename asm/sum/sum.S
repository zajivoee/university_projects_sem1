        .global sum
        .global sum_struct
        .global sum_array
        .global sum_args

// input:
//    rdi: первое int64_t число
//    rsi: второе int64_t число
//
// output:
//    rax: сумма чисел
//
sum:
    mov %rdi, %rax
    add %rsi, %rax
    ret

// input:
//    rdi: указатель на структуру
//
// struct {
//     int64_t a;
//     int64_t b;
//     int64_t sum;
// };
//
// output:
//    в поле sum нужно записать сумму a и b
//
sum_struct:
    mov (%rdi), %rax
    add 8(%rdi), %rax
    mov %rax, 16(%rdi)
    ret

// input:
//    rdi: указатель на массив int64_t
//    rsi: количество элементов в массиве
//
// output:
//    rax: сумма элементов массива
//
sum_array:
    xor %rax, %rax
    cmp $0, %rsi
    jz .end_sum_array
    add (%rdi), %rax
    dec %rsi
.sum_array_loop:
    cmp $0, %rsi
    jle .end_sum_array
    add $8, %rdi
    add (%rdi), %rax
    dec %rsi
    jnz sum_array_loop
.sum_array_done:
    ret

// input:
//    rdi: количество элементов на стеке (сразу после адреса возврата из функции)
//
// output:
//    rax: сумма элементов со стека
//
sum_args:
    xor %rax, %rax
    xor %rcx, %rcx
.sum_args_loop:
    cmp $0, %rdi
    jz .end_sum_array
    add $8, %rcx
    add %rcx, %rsp
    add (%rsp), %rax
    sub %rcx, %rsp
    dec %rdi
    jnz sum_args_loop
.sum_args_done:
    ret
