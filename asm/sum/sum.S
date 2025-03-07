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
    test %rsi, %rsi
    jz .end_sum_array

sum_array_loop:
    add (%rdi), %rax
    add $8, %rdi
    dec %rsi
    jnz sum_array_loop
.end_sum_array:
    ret

// input:
//    rdi: количество элементов на стеке (сразу после адреса возврата из функции)
//
// output:
//    rax: сумма элементов со стека
//
sum_args:
    xor %rax, %rax
    mov %rdi, %rcx
    lea 8(%rsp), %rdx
    test %rcx, %rcx
    jz .end_sum_args
sum_args_loop:
    cmp $0, %rdi
    jz .end_sum_array
    add $8, %rcx
    add %rcx, %rsp
    add (%rsp), %rax
    sub %rcx, %rsp
    dec %rdi
    jnz sum_args_loop
.end_sum_args:
    ret
