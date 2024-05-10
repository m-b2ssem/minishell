#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>


void child_1() {
    signal(SIGINT, SIG_DFL);
    printf("Child 222\n");
}

void child() {
    printf("Child 111\n");
    child_1();
    signal(SIGINT, SIG_DFL);
    exit(0);
}


void sigint_handler(int sig_num) {
    (void)sig_num;
    printf("Caught SIGINT signal.\n");
    exit(0);
}

int main(int argc, char *argv[], char *env[]) {
    (void)argc;
    (void)argv;

    printf("Press Ctrl+C to send SIGINT signal.\n");
    //int i;
    char *str;
    while(1) {
        signal(SIGINT, sigint_handler);
        str = readline("minishell> ");
        if (str == NULL)
        {
            printf("exit\n");
            break;
        }
        /*i = fork();
        if (i == 0) {
            printf("Child process created.\n");
            child();
            signal(SIGINT, SIG_DFL);
        }*/
    }
    //waitpid(i, NULL, 0);
    return 0;
}