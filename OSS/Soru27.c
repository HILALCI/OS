#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    // int pid;
    pid_t pid,pid2;


    pid = fork();


    if (pid > 0){
        wait(NULL);
        printf("Parent PID : %d  getpid : %d \n", pid, getpid());
        printf("Merhaba ---> %d\n", getpid());
    }
    if (pid == 0){
        // wait(NULL);
        printf("Child PID : %d  getpid : %d \n", pid, getpid());
        pid2 = fork();
        if (pid2 > 0){
            wait(NULL);
            printf("Parent2 PID : %d  getpid : %d \n", pid, getpid());
            printf("Hi ---> %d\n", getpid());
        }
        if (pid2 == 0){
            // wait(NULL);
            printf("Child2 PID : %d  getpid : %d \n", pid, getpid());
            printf("Hello ---> %d\n", getpid());
            
        }
    }
    if (pid < 0){
        printf("Hata");
    }
}
