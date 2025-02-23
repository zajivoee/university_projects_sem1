#include "syscall.h"

int open(const char* pathname, int flags) {
    // your code here
}
int close(int fd) {
    // your code here
}

ssize_t read(int fd, void* buf, size_t count) {
    // your code here
}

ssize_t write(int fd, const void* buf, ssize_t count) {
    // your code here
}

int pipe(int pipefd[2]) {
    // your code here
}

int dup(int oldfd) {
    // your code here
}

pid_t fork() {
    // your code here
}

pid_t waitpid(pid_t pid, int* wstatus, int options) {
    // your code here
}

int execve(const char* filename, char* const argv[], char* const envp[]) {
    // your code here
}

void exit(int status) {
    // your code here
}
