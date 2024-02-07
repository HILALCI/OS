#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

//gcc urtuk.c -lpthread


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int  sayac = 0, size= 10;

int uretici, tuketici, ret, ret2, sayac;

int pd[2], pd2[2];

char buf[10];
char result [sizeof(int)*8+1];


pthread_t tidp[10], tidc[10];
// pthread_attr_t attr, attr2;


// pthread_attr_init(&attr);
// pthread_attr_init(&attr2);

void taskp(int sayi){

    // close(pd[0]);
    char syaz [sizeof(int)*8+1];
    sprintf(syaz, "%d", sayi);
    write(pd[1], syaz, 11);
    printf("Yazan %d = %s \n", getpid(), syaz);

}

void taskc(){

    char buf[size];
    // close(pd[1]);
    read(pd[0], buf, size+1);
    printf("Okuyan %d = %s \n", getpid(),buf);

    // close(pd2[0]);
    char *gonder;
    write(pd2[1], gonder, 11);
    printf("Tuketici Yavru Gonderdi %d = %s \n", getpid(), gonder);

}


void producer(char *yaz){
    pthread_mutex_lock( &mutex1 );

    // close(pd[0]);
    pthread_create(&tidp[atoi(*yaz)], NULL, (void *) &taskp, atoi(*yaz));
    pthread_join(tidp[atoi(*yaz)], NULL);
    sleep(1);

    //pthread_exit(0);

    pthread_mutex_unlock( &mutex1 );
}

void consumer(){
    pthread_mutex_lock( &mutex1 );

    // close(pd[1]);

    for(sayac = 1; sayac<=size; sayac++){

        pthread_create(&tidc[sayac], NULL, (void *) &taskc, NULL);
        pthread_join(tidc[sayac], NULL);
        sleep(1);
    }

    
    //pthread_exit(0);

    pthread_mutex_unlock( &mutex1 );

}

int main() {
    ret = pipe(pd);
    ret2 = pipe(pd2);

    if (ret < 0 || ret2 < 0) {

        printf("Pipe Hatali \n");
        exit(1);
    }

    uretici = fork();
    tuketici = fork();


    while(1){

        pthread_t tid[2];
        

        if (uretici > 0){
            int syaz = 1;
            char result [sizeof(int)*8+1];
            close(pd[0]);
            sprintf(result, "%d", syaz);
            write(pd[1], result, 11);
            printf("Parent Yazilacak Sayiyi Gonderdi %d = %s \n", getpid(), result);
        }

        else if (uretici == 0){
            close(pd[1]);
            read(pd[0], buf, size+1);
            printf("Parenttan Yazilacak Aldi %d = %s \n", getpid(),buf);

            pthread_create(&tid[1], NULL, (void *) &producer, &buf);
            pthread_join(tid[1], NULL);


        }

        if(tuketici > 0){
            
            close(pd2[1]);
            read(pd2[0], buf, size+1);
            printf("Tuketici Parent Okudu %d = %s \n", getpid(), buf);

        }

        else if (tuketici == 0){

            pthread_create(&tid[0], NULL, (void *) &consumer, NULL);
            pthread_join(tid[0], NULL);
        }


        else if (uretici < 0 || tuketici < 0){
            printf("Process Hatali \n");
        }

        //pthread_exit(0);

    }
    
}