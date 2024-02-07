#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include<fcntl.h>
#include <sys/wait.h>
#include <sys/shm.h>


void producer(){
    int pid, ret;

    int pd[2];

    ret = pipe(pd);

    srand(time(NULL));


    if (ret < 0) {
        printf("Pipe Error");
        exit(1);
    }

    pid = fork();

    if (pid > 0){
        //printf("Ebeveyn cocuk process emir verdi.");
    }

    else if (pid == 0){
        close(pd[0]);
        int rand_sayi = rand() %10;
        char result [sizeof(int)*8+1];
        sprintf(result, "%d", rand_sayi);
        write(pd[1], result, 3);
    }
    else if (pid < 0){
        printf("Hata");
    }

}

void consumer(){
    int pid, ret;

    int pd[2], pd2[2];

    ret = pipe(pd);

    if (ret < 0) {
        printf("Pipe Error");
        exit(1);
    }

    pid = fork();

    if (pid > 0){
        close(pd2[1]);
        char buf2[10];
        read(pd[0], buf2, 20);
        printf("Ebeveyn Okudu = %s \n", buf2);

    }

    else if (pid == 0){
        close(pd[1]);
        char buf[10];
        read(pd[0], buf, 20);
        printf("Cocuk okudu = %s \n", buf);

        close(pd2[0]);
        write(pd2[1], buf, 20);
    }
    else if (pid < 0){
        printf("Hata");
    }

}

int main(){

    producer();
    consumer();

    return 0;
}