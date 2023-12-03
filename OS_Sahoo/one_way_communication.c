#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fds[2];
    pid_t pid;
    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        close(pipe_fds[0]);
        printf("Reading from Child Process.\n") ;
        char message[] = "Hello, world!\n";
        write(pipe_fds[1], message, sizeof(message));
        close(pipe_fds[1]);
        exit(EXIT_SUCCESS);
    }
    else {
        close(pipe_fds[1]);
        printf("Reading from Parent Process.\n") ;
        char buffer[1024];
        int bytes_read = read(pipe_fds[0], buffer, sizeof(buffer));
        if (bytes_read > 0) {
            printf("%s", buffer);
        }
        close(pipe_fds[0]);
        sleep(2) ;
    }

    return EXIT_SUCCESS;
}
