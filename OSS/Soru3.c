#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    // int pid; 
    pid_t pid;

    pid = fork();

    if (pid > 0){
        printf("Parent PID : %d \n",getpid());
    }
    if (pid == 0){
        printf("Child PID : %d \n",getpid());
    }
    if (pid < 0){
        printf("Hata");
    }
}
