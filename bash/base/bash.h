#include <unistd.h>
#include "tokenizer.h"
#include "sys/wait.h"

void Exec(struct Tokenizer* tokenizer) {
    if (tokenizer->token_count == 0) {
        return;
    }

    char** ARGV = malloc(sizeof(char *) * (tokenizer->token_count + 1));

    size_t token_num = 0;
    struct Token* cur_token = tokenizer->head;

    while (cur_token) {
        cur_token->start[cur_token->len] = '\0';
        ARGV[token_num++] = cur_token->start;
        cur_token = cur_token->next;
    }

    ARGV[tokenizer->token_count] = NULL;

    pid_t cur_pid = fork();

    if (cur_pid < 0) {
        free(ARGV);
        return;
    } else if (cur_pid == 0) {
        execvp(ARGV[0], ARGV);
        printf("Command not found\n");
        fflush(stdout);
        _exit(1);
    } else {
        wait(NULL);
    }

    free(ARGV);
}
