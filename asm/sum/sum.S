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
    // your code here
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
    // your code here
    ret

// input:
//    rdi: указатель на массив int64_t
//    rsi: количество элементов в массиве
//
// output:
//    rax: сумма элементов массива
//
sum_array:
    // your code here
    ret

// input:
//    rdi: количество элементов на стеке (сразу после адреса возврата из функции)
//
// output:
//    rax: сумма элементов со стека
//
sum_args:
    // your code here
    ret
