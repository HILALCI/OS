#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include<fcntl.h>
#include <sys/wait.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  sayac = 0, size= 10;

int pid, ret, sayac;

int pd[2];

pthread_t tidc[10];

void taskc(){
    char buf[size];

    read(pd[0], buf, size+1);
    printf("Okuyan %d = %s \n", getpid(),buf);

}

void consumer(){
    pthread_mutex_lock( &mutex1 );

    close(pd[1]);

    for(sayac = 1; sayac<=size; sayac++){
        pthread_create(&tidc[sayac], NULL, (void *) &taskc, NULL);
        pthread_join(tidc[sayac], NULL);
        sleep(1);
    }

    
    //pthread_exit(0);

    pthread_mutex_unlock( &mutex1 );

}

int main(){
    pid = fork();

    while(1){

        pthread_t tid[2];

        if (pid > 0){
            pthread_create(&tid[0], NULL, (void *) &consumer, NULL);
            pthread_join(tid[0], NULL);

        }

        else if (pid < 0){
            printf("Hata");
        }


        //pthread_exit(0);

    }
}