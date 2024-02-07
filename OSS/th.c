#include <stdio.h>
#include <pthread.h>

void task(int *x) {
    printf("%d\n", *x);
    pthread_exit(0);
}


int main(){
    pthread_t tid[5];
    pthread_attr_t attr;

    int i,j;

    pthread_attr_init(&attr);

    for(i = 0; i<5; i++){
        pthread_create(&tid[i], &attr, (void *) &task, &i);

    }

    for(j = 0; j<5; j++)
        pthread_join(tid[i], NULL);

    
    pthread_exit(0);

}