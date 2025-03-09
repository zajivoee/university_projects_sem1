#include "syscall.h"

int open(const char* pathname, int flags) {
    int fd;

    asm volatile (
            "mov $2, %%rax\n"
            "mov %1, %%rdi\n"
            "mov %2, %%rsi\n"
            "syscall\n"
            "mov %%eax, %0"
            : "=rm" (fd)
            : "rm" (pathname), "rm" (flags)
            : "rax", "rdi", "rsi", "rcx"
            );

    return fd;
}

ssize_t read(int fd, void* buf, size_t count) {
    ssize_t count_bytes;

    asm volatile (
            "mov $0, %%eax\n"
            "mov %1, %%edi\n"
            "mov %2, %%rsi\n"
            "mov %3, %%rdx\n"
            "syscall\n"
            "mov %%rax, %0"
            : "=rm" (count_bytes)
            : "rm" (fd), "rm" (buf), "rm" (count)
            : "eax", "edi", "rsi", "rdx"
            );

    return count_bytes;
}

ssize_t write(int fd, const void* buf, ssize_t count) {
    ssize_t count_bytes;

    asm volatile (
            "mov $1, %%eax\n"
            "mov %1, %%rdi\n"
            "mov %2, %%rsi\n"
            "mov %3, %%rdx\n"
            "syscall\n"
            "mov %%rax, %0"
            : "=rm" (count_bytes)
            : "rm" (fd), "rm" (buf), "rm" (count)
            : "eax", "rdi", "rsi"
            );

    return count_bytes;
}

int pipe(int pipefd[2]) {
    int res;

    asm volatile (
            "mov $22, %%eax\n"
            "mov %1, %%rdi\n"
            "syscall\n"
            "mov %%eax, %0"
            : "=rm" (res)
            : "rm" (pipefd)
            : "eax", "rdi", "rcx"
            );

    return res;
}

int close(int fd) {
    int res;

    asm volatile (
            "mov $3, %%eax\n"
            "mov %1, %%rdi\n"
            "syscall\n"
            "mov %%eax, %0"
            : "=rm" (res)
            : "rm" (fd)
            : "eax", "rdi", "rcx"
            )
            ;
    return res;
}

int dup(int oldfd) {
    int newfd;

    asm volatile (
            "mov $32, %%eax\n"
            "mov %1, %%rdi\n"
            "syscall\n"
            "mov %%eax, %0"
            : "=rm" (newfd)
            : "rm" (oldfd)
            : "eax", "rdi", "rcx"
            );

    return newfd;
}

void exit(int status) {
    asm volatile (
            "mov $60, %%eax\n"
            "mov %0, %%rdi\n"
            "syscall\n"
            :
            : "rm" (status)
            : "eax", "rdi", "rcx", "r11"
            );

    __builtin_unreachable();
}

pid_t fork() {
    pid_t pid;

    asm volatile (
            "mov $57, %%eax\n"
            "syscall\n"
            "mov %%eax, %0"
            : "=rm" (pid)
            :
            : "eax", "rcx", "r11"
            );

    return pid;
}

pid_t waitpid(pid_t pid, int* wstatus, int options) {
    pid_t res;

    asm volatile (
            "mov $61, %%eax\n"
            "mov %1, %%rdi\n"
            "mov %2, %%rsi\n"
            "mov %3, %%rdx\n"
            "syscall\n"
            "mov %%eax, %0"
            : "=rm" (res)
            : "rm" (pid), "rm" (wstatus), "rm" (options)
            : "eax", "rdi", "rsi", "rdx"
            );
    
    return res;
}


int execve(const char* filename, char* const argv[], char* const envp[]) {
    int res;

    asm volatile (
            "mov $59, %%eax\n"
            "mov %1, %%rdi\n"
            "mov %2, %%rsi\n"
            "mov %3, %%rdx\n"
            "syscall\n"
            "mov %%eax, %0"
            : "=rm" (res)
            : "rm" (filename), "rm" (argv), "rm" (envp)
            : "eax", "rdi", "rsi", "rdx"
            );
    
    return res;
}