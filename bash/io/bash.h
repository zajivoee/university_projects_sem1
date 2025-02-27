#include <unistd.h>
#include <sys/file.h>
#include "tokenizer.h"
#include "sys/wait.h"
#include <stdbool.h>

//void close_file_descriptor(int oldIn, int oldOut, int newIn, int newOut) {
//    if (newIn != STDIN_FILENO) {
//        close(newIn);
//        dup2(newIn, STDIN_FILENO);
//    }
//
//    if (oldOut != STDOUT_FILENO) {
//        close(newOut);
//        dup2(newOut, STDOUT_FILENO);
//    }
//
//    close(oldIn);
//    close(oldOut);
//}

void Exec(struct Tokenizer* tokenizer) {
    if (tokenizer->token_count == 0) {
        return;
    }

    bool wasIn = false, wasOut = false;
    struct Token* cur = tokenizer->head;

    while (cur) {
        if (cur->type == TT_INFILE) {
            if (!cur->next || wasIn || cur->next->type != TT_WORD) {
                printf("Syntax error\n");
                return;
            }

            wasIn = true;
            cur = cur->next;
        } else if (cur->type == TT_OUTFILE) {
            if (!cur->next || wasOut || cur->next->type != TT_WORD) {
                printf("Syntax error\n");
                return;
            }

            wasOut = true;
            cur = cur->next;
        }
        cur = cur->next;
    }

    char** ARGV = malloc(sizeof(char *) * (tokenizer->token_count + 1));

    if (!ARGV) {
        return;
    }

    cur = tokenizer->head;
    size_t wordsCnt = 0;

    int in_fd = STDIN_FILENO, out_fd = STDOUT_FILENO;

    while (cur) {
        if (cur->type == TT_WORD) {
            cur->start[cur->len] = '\0';
            ARGV[wordsCnt++] = cur->start;
        } else if (cur->type == TT_INFILE) {
            cur = cur->next;

            cur->start[cur->len] = '\0';
            in_fd = open(cur->start, O_RDONLY);

            if (in_fd < 0) {
                printf("I/O error\n");
                free(ARGV);
                return;
            }
        } else if (cur->type == TT_OUTFILE) {
            cur = cur->next;

            cur->start[cur->len] = '\0';

            out_fd = open(cur->start, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_fd < 0) {
                printf("I/O error\n");
                close(out_fd);
                free(ARGV);
                return;
            }
        }
        cur = cur->next;
    }

    ARGV[wordsCnt] = NULL;

    pid_t pid = fork();
    if (pid < 0) {
        free(ARGV);
        return;
    } else if (pid == 0) {
        if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        execvp(ARGV[0], ARGV);
        printf("Command not found\n");
        free(ARGV);
        return;
    } else {
        if (in_fd != STDIN_FILENO)
            close(in_fd);
        if (out_fd != STDOUT_FILENO)
            close(out_fd);
        wait(NULL);
    }

    free(ARGV);
}
