#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#include "CircularBuffer.h"

#define MAX_VALUE           1000

static void *producer(void *args) {
    for (int i = 0; i < MAX_VALUE; i++) {
        addToBuffer(i);
    }
    addToBuffer(-1);
    return NULL;
}

static void *consumer(void *args) {
    int val;
    char *threadName = (char *)args;
    while((val = removeFromBuffer()) != -1) {
        printf("%s %d\n", threadName, val);
    }
    printf("consumer is done");
    return NULL;
}

int main(int argc, char **argv) {
    int numConsumers = 2;

    if (argc >= 2) {
        numConsumers = atoi(argv[1]);
    }

    initBuffer();
    pthread_t producerThread, consumerThread[numConsumers];

    if (pthread_create(&producerThread, NULL, producer, NULL) == -1) {
        perror("pthread_create producer");
        exit(-1);
    }

    char threadName[numConsumers][10];
    for (int i = 0; i < numConsumers; ++i) {
        snprintf(threadName[i], 10, "Thread%d", i);
        if (pthread_create(&consumerThread[i], NULL, consumer, threadName[i]) == -1) {
            perror("pthread_create consumer");
            exit(-1);
        }
    }

    pthread_join(producerThread, NULL);
    for (int i = 0; i < numConsumers; ++i) {
        pthread_join(consumerThread[i], NULL);
    }
}
