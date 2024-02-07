#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include<fcntl.h>
#include <sys/wait.h>
#include <time.h>


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  sayac = 0, size= 10;

int pid, ret, sayac;

int pd[2];

pthread_t tidp[10];


void taskp(int *sayi){
    char result [sizeof(int)*8+1];

    sprintf(result, "%d", *sayi);
    write(pd[1], result, 11);
    printf("Yazan %d = %s \n", getpid(),result);

}

void producer(){
    pthread_mutex_lock( &mutex1 );

    close(pd[0]);

    for(sayac = 1; sayac<=size; sayac++){
        pthread_create(&tidp[sayac], NULL, (void *) &taskp, &sayac);
        pthread_join(tidp[sayac], NULL);
        sleep(1);
    }


    //pthread_exit(0);

    pthread_mutex_unlock( &mutex1 );
}

int main(){
    pid = fork();

    while(1){

        pthread_t tid[2];

        if (pid == 0){
            pthread_create(&tid[1], NULL, (void *) &producer, NULL);
            pthread_join(tid[1], NULL);


        }
        else if (pid < 0){
            printf("Hata");
        }


        //pthread_exit(0);

    }
}