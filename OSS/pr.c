#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include<fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    int rand_sayi = rand() %10;
    char buffer [sizeof(int)*8+1];
    itoa(rand_sayi, buffer, DECIMAL);
    printf("Sayi = %s ", buffer);


}