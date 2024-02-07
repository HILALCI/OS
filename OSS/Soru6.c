#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int x = 5;

int main(){
    unsigned int i;
    fork();
    for (i = 0; i< 0xffff;i++);
    printf("Merhaba\n");
    fork();
    for (i = 0; i< 0xffff;i++);
    printf("Merhaba\n");

}