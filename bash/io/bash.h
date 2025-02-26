#include <unistd.h>
#include <sys/file.h>
#include "tokenizer.h"
#include "sys/wait.h"
#include <stdbool.h>

void Exec(struct Tokenizer* tokenizer) {
    if (tokenizer->token_count == 0) {
        return;
    }

    bool was_in = false, was_out = false;
    char *in_ptr = NULL, *out_ptr = NULL;

    struct Token* cur_token = tokenizer->head;

    size_t words_cnt = 0;

    while (cur_token) {
        if (cur_token->type == TT_INFILE) {
            if (was_in) {
                printf("Syntax error\n");
                return;
            }
            
            was_in = true;
            
            if (cur_token->next == NULL || cur_token->next->type != TT_WORD) {
                printf("Syntax error\n");
                return;
            }

            in_ptr = cur_token->next->start;
            cur_token = cur_token->next;
        } else if (cur_token->type == TT_OUTFILE) {
            if (was_out) {
                printf("Syntax error\n");
                return;
            }
            
            was_out = true;
            
            if (cur_token->next == NULL || cur_token->next->type != TT_WORD) {
                printf("Syntax error\n");
                return;
            }

            out_ptr = cur_token->next->start;
            cur_token = cur_token->next;
        } else {
            words_cnt++;
            cur_token = cur_token->next;
        }
    }

    char** ARGV = malloc(sizeof(char *) * (tokenizer->token_count + 1));

    if (!ARGV) {
        return;
    }

    size_t token_num = 0;
    cur_token = tokenizer->head;

    while (cur_token) {
        if (cur_token->type == TT_INFILE || cur_token->type == TT_OUTFILE) {
            cur_token = cur_token->next;

        } else {
            cur_token->start[cur_token->len] = '\0';
            ARGV[token_num++] = cur_token->start;
            cur_token = cur_token->next;
        }
    }

    if (ARGV[0] == NULL) {
        printf("Syntax Error\n");
        return;
    }

    ARGV[token_num] = NULL;

    int in = -1, out = -1;
    if (in_ptr != NULL) {
        in = open(in_ptr, O_RDONLY);
        if (in < 0) {
            printf("I/O error\n");
            free(ARGV);
            return;
        }
    }

    if (out_ptr != NULL) {
        out = open(out_ptr, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out < 0) {
            printf("I/O error\n");
            free(ARGV);
            return;
        }
    }

    pid_t pid = fork();
    if (pid < 0) {
        free(ARGV);
        return;
    } else if (pid == 0) {
        if (in != -1) {
            dup2(in, STDIN_FILENO);
            close(in);
        }

        if (out != -1) {
            dup2(out, STDOUT_FILENO);
            close(out);
        }

        execvp(ARGV[0], ARGV);

        printf("Command not found\n");
        fflush(stdout);
        _exit(1);
    } else {
        wait(NULL);
    }

    free(ARGV);
}
