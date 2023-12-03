#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){
    pid_t pid , ppid , cpid ;
    ppid = getpid() ;
    pid = fork() ;
    if(pid > 0){
        printf("Inside Parent Process.\n") ;
        kill(ppid , SIGKILL) ;
        printf("The Parent process died.\n") ;
    }
    else if(pid == 0){
        printf("Inside Child Process and its process ID is: %d\n" , getpid()) ;
    }
    else{
        printf("Process Creation terminated.\n") ;
    }
    return 0 ;
}
