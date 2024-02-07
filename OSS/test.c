#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

void *a();
void *b();
int  count = 0;

#define COUNT_DONE  10

int main(){
    pthread_t tid, tid2;

    pthread_create( &tid, NULL, &a, NULL);
    pthread_create( &tid2, NULL, &b, NULL);

    pthread_join( tid, NULL);
    pthread_join( tid2, NULL);

    printf("Final count: %d\n",count);

    exit(EXIT_SUCCESS);

    // pthread_mutex_t mutex;
    // pthread_cond_t cond;

    // pthread_mutex_lock(mutex);
    // pthread_mutex_unlock(mutex);
    
}

void *a()
{
    while(1) {
       pthread_mutex_lock( &count_mutex );

       if( count % 2 == 0 )
       {
          // Condition of if statement has been met. 
          // Signal to free waiting thread by freeing the mutex.
          // Note: functionCount1() is now permitted to modify "count".
          pthread_cond_signal( &condition_var );
       }
       else
       {
          count++;
          printf("Counter value a: %d\n",count);
       }

       pthread_mutex_unlock( &count_mutex );

       if(count >= COUNT_DONE) return(NULL);
    }

}


void *b()
{
    while(1) {
       pthread_mutex_lock( &count_mutex );

       if( count % 2 == 1 )
       {
          // Condition of if statement has been met. 
          // Signal to free waiting thread by freeing the mutex.
          // Note: functionCount1() is now permitted to modify "count".
          pthread_cond_signal( &condition_var );
       }
       else
       {
          count++;
          printf("Counter value b: %d\n",count);
       }

       pthread_mutex_unlock( &count_mutex );

       if(count >= COUNT_DONE) return(NULL);
    }

}
