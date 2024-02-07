#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int producer(int buffer){
    int d[buffer];
    int i;
    srand(time(NULL));   // Initialization, should only be called once.

    for (i=0; i<buffer; i++){
        d[i] = rand() %10;
    }

    return d,buffer;
}

void consumer(int dizi, int buffer){
    int j;
    for (j=0; j<buffer; j++){
        printf("%d\n",d[j]);
        buffer--;
    }
}


int main(){
    int buff = 10;
    int d, b = producer(buff);
    
    //consumer(d,b);

    
}