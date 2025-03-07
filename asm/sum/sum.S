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
    jz .sum_array_done
.sum_array_loop:
    add (%rdi), %rax
    add $8, %rdi
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
    mov %rdi, %rcx
    lea 8(%rsp), %rdx
    test %rcx, %rcx
    jz .sum_args_done
.sum_args_loop:
    add (%rdx), %rax
    add $8, %rdx
    dec %rcx
    jnz sum_args_loop
.sum_args_done:
    ret
