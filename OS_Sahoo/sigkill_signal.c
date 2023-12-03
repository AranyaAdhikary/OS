#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void kill_signal(){
    printf("The process that is being killed is: %d\n" , getpid()) ;
    kill(getpid() , SIGKILL) ;
}
int main(){
    //int pid = fork() ;
    printf("A process is running.\n") ;
    kill_signal() ;
    printf("The Process has been killed.\n") ;
    return 0 ;
}
