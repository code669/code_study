#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mute;

int value = 0;

#define NUM_MAX  100*10000

void *productor(void *arg){

    while(value < NUM_MAX) {
        pthread_mutex_lock(&mute);

        ++value;
        //printf("productor value=%d\n", value);

        pthread_mutex_unlock(&mute);
    }
}


void *customer(void *arg){
    int i = 0;

    while(i < NUM_MAX) {
        pthread_mutex_lock(&mute);

        i = value;
        //printf("customer i=%d\n", i);

        pthread_mutex_unlock(&mute);
    }
}


int main(){
 
    pthread_t th_productor, th_customer;
    int id_productor = 1;
    int id_customer = 2;

    pthread_mutex_init(&mute, NULL);

    pthread_create(&th_productor, NULL, productor, (void *)&id_productor);

    pthread_create(&th_customer, NULL, customer, (void *)&id_customer);

    pthread_join(th_productor, NULL);
    pthread_join(th_customer, NULL);

    pthread_mutex_destroy(&mute);
    return 0;
}
