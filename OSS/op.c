#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int x = 5;

int main(){
    printf("X start = %d\n", x);

    pid_t pid;


    pid = fork();

    printf("X in = %d\n", x);

    if (pid > 0){
        // wait(NULL);
        printf("Parent PID : %d  getpid : %d \n", pid, getpid());
        x = x + 10;
        printf("X changed parent = %d\n", x);

    }
    if (pid == 0){
        // wait(NULL);
        printf("Child PID : %d  getpid : %d \n", pid, getpid());
        x = x + 20;
        printf("X changed child = %d\n", x);
    }
    if (pid < 0){
        printf("Hata");
    }
    printf("X out = %d\n", x);

}