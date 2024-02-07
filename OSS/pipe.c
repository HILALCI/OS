#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h>

int main() {
    int pid, ret;

    int pd[2];

    ret = pipe(pd);

    if (ret < 0) {
        printf("Pipe Error");
        exit(1);
    }

    pid = fork();

    if (pid > 0){
        close(pd[0]);

        char result [sizeof(int)*8+1];
        int num = 23;
        sprintf(result, "%d", num);
        write(pd[1], result, 11);
        printf("Ebeveyn yazdi.\n");
    }

    else if (pid == 0){
        close(pd[1]);
        char buf[10];
        read(pd[0], buf, 20);
        printf("Cocuk okudu.\n");
        printf("Okunan = %s \n", buf);
    }
    else if (pid < 0){
        printf("Hata");
    }
}