#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){
    pid_t pid , f_pid ;
    pid = getpid() ;
    f_pid = fork() ;
    if(f_pid > 0){
       printf("We are inside the parent process.\n") ;
       while(1){
          usleep(50000) ;
          printf("Inside a process with ID: %d\n" , pid) ;
       }
    }
    else if(f_pid == 0){
       kill(pid , SIGSTOP) ;
       sleep(2) ;
       kill(pid , SIGCONT) ;
       sleep(2) ;
       kill(pid , SIGKILL) ;
       //wait(NULL) ;
    }
    else
    printf("Process Creation error.\n") ;
    printf("Hello World.\n") ;
    return 0 ;
}
