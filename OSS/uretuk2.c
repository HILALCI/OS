#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>





pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  sayac = 0, size= 10;

int uretici, tuketici, ret, ret2, sayac;

char buf[10];
char buf2[10];
char buf3[10];


int pd[2], pd2[2], pd3[2];

pthread_t tid[5], tid2[3], tid3[3];

void *producer_ptask(int *sayi){
    close(pd[0]);

    char result [sizeof(int)*8+1];
    
    sprintf(result, "%d", *sayi);
    write(pd[1], result, 3);
    printf("Ureten Ebeveyn yazdi %d = %s \n", getpid(), result);
    sleep(1);
    
}


void *producer_ctask(){

    close(pd[1]);
            
    read(pd[0], buf, 3);
    printf("Ureten Cocuk Okudu %d = %s \n", getpid(), buf);

    close(pd2[0]);
    write(pd2[1], buf, 3);
    printf("Ureten Cocuk yazdi %d = %s \n", getpid(), buf);

}

void *consumer_ptask(){

    close(pd3[1]);
    read(pd3[0], buf3, 20);
    printf("Tuketen Parent Okudu %d = %s \n", getpid(), buf3);
}

void *consumer_ctask(){
    close(pd2[1]);
    read(pd2[0], buf2, 20);
    printf("Tuketen Parent Okudu %d = %s \n", getpid(), buf2);

    close(pd3[0]);
    write(pd3[1], buf2, 3);
    printf("Tuketen Cocuk yazdi %d = %s \n", getpid(),buf2);
}

// pthread_t tidp[10], tidc[10];

int main() {

    ret = pipe(pd);
    ret2 = pipe(pd2);


    if (ret < 0 || ret2) {
        printf("Pipe Hatali");
        exit(1);
    }

    uretici = fork();

    pthread_mutex_lock( &mutex1 );

    while(1){

        if (uretici > 0){
            // int i = 0;
            for (sayac = 1; sayac<=10; sayac++){
                pthread_create(&tid[sayac], NULL, (void *) &producer_ptask, &sayac);
                pthread_join(tid[sayac], NULL);
            }

        }

        else if (uretici == 0){
            
            pthread_create(&tid2[1], NULL, (void *) &producer_ctask, NULL);
            pthread_join(tid2[1], NULL);
        }

        // pthread_mutex_unlock( &mutex1 );

        // pthread_mutex_lock( &mutex1 );

        tuketici = fork();

        if (tuketici > 0){
            // wait(NULL);
            pthread_create(&tid3[1], NULL, (void *) &consumer_ptask, NULL);
            pthread_join(tid3[1], NULL);
        }

        else if(tuketici == 0) {
            // wait(NULL);
            pthread_create(&tid3[2], NULL, (void *) &consumer_ctask, NULL);
            pthread_join(tid3[2], NULL);
        }

        else if (uretici < 0 || tuketici){
            printf("Process Hata");
        }

        pthread_mutex_unlock( &mutex1 );
    
    }

}