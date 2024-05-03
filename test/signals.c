#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>


void child_1() {
    signal(SIGINT, SIG_DFL);
    printf("Child 222\n");
}

void child() {
    while(1) {
        printf("Child 111\n");
        child_1();
        signal(SIGINT, SIG_DFL);
        sleep(1);
    }
}


void sigint_handler(int sig_num) {
    (void)sig_num;
    printf("Caught SIGINT signal.\n");
    exit(0);
}

int main() {
    
    printf("Press Ctrl+C to send SIGINT signal.\n");
    int i;
    char *str;
    while(1) {
        signal(SIGINT, sigint_handler);

        i = fork();
        str = readline("minishell> ");
        if (str = NULL)
        {
            printf("exit\n");
        }
        if (i == 0) {
            printf("Child process created.\n");
            child();
            signal(SIGINT, SIG_DFL);
        }
        printf("Running infinite loop.\n");
        sleep(1);
    }
    waitpid(i, NULL, 0);
    return 0;
}