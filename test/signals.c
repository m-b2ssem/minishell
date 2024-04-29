#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sigintHandler(int sig_num)
{
    printf("\n Termination signal received. Exiting...\n");
    exit(0);
}

int main ()
{

    while(1)
    {
        signal(SIGINT, sigintHandler);
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}