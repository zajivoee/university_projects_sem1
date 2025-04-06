#include "backtrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define MAX_BT_SIZE 64

char *AddrToName(void *addr) {
    Dl_info info;
    if (dladdr(addr, &info) && info.dli_sname) {
        return (char *)info.dli_sname;
    }
    return NULL;
}

int Backtrace(void *backtrace[], int limit) {
    if (backtrace == NULL || limit <= 0) {
        return 0;
    }

    long long count = 0;
    long long max = limit;
    asm volatile(
            "mov %%rbp, %%rax\n"
            "1:\n"
            "cmp %2, %0\n"
            "je 2f\n"
            "mov 8(%%rax), %%rdi\n"
            "mov %1, %%rbx\n"
            "mov %%rdi, (%%rbx, %0, 8)\n"
            "mov (%%rax), %%rax\n"
            "inc %0\n"
            "cmpq $0, (%%rax)\n"
            "je 2f\n"
            "jmp 1b\n"
            "2:\n"
            : "+r" (count)
            : "r" (backtrace), "r" (max)
            : "rax", "rdi", "rbx"
            );
    return (int)count;
}

void PrintBt() {
    void *bt[MAX_BT_SIZE];
    int count = Backtrace(bt, MAX_BT_SIZE);

    printf("Стек вызовов (%d):\n", count);
    for (int i = 0; i < count; i++) {
        char *name = AddrToName(bt[i]);
        printf("#%d: %p %s\n", i, bt[i], name ? name : "??");
    }
}