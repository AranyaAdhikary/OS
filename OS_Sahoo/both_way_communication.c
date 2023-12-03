#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int comm1[2], comm2[2];
    pid_t pid;
    if (pipe(comm1) == -1 && pipe(comm2) == -1)
    {
        printf("The Pipe creation is not possible.\n");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0)
    {
        printf("The Creation of process is unsuccessful.\n");
    }
    else if (pid == 0)
    {
        printf("Inside the child process with ID: %d\n" , getpid());
        close(comm1[1]);
        close(comm2[0]);
        char red[1024];
        int rd = read(comm1[0], red, sizeof(red));
        printf("------------------------------------------\n") ;
        printf("The Value of rd is : %d\n" , rd) ;
        if (rd > 0)
        {
            printf("The Message is: %s\n", red);
            char message[] = "I am Coding right now.\n" ;
            write(comm2[1], message, sizeof(message));
        }
        close(comm1[0]);
        close(comm2[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Inside the Parent process with ID: %d\n" , getpid());
        close(comm1[0]);
        close(comm2[1]);
        char message[] = "Supra overtakes Mustang GT.\n";
        write(comm1[1], message, sizeof(message));
        char red[1024];
        sleep(1) ;
        int rd = read(comm2[0], red, sizeof(red));
        printf("++++++++++++++++++++++++++++++++++++++++++\n") ;
        printf("The Value of rd is : %d\n" , rd) ;        
        if (rd > 0)
        {
            printf("The message is: %s\n", red);
        }
        close(comm2[0]) ;
        close(comm1[1]) ;
    }
    //printf("The Code has ended. for PID: %d\n" , getpid());
    return EXIT_SUCCESS;
}
