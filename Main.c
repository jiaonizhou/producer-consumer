#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#include "CircularBuffer.h"

static void *producer(void *args) {
    int value = *(int *)args;
    for (int i = 0; i < value; i++) {
        addToBuffer(i);
        //printf("integer %d is added\n", i);
    }
    // lastly, add -1 to the buffer to indicate all values have been added
    addToBuffer(-1);
    //printf("producer is done\n");
    return NULL;
}

static void *consumer(void *args) {
    int val;
    char *threadName = (char *)args;
    while((val = removeFromBuffer()) != -1) {
        printf("%s %d\n", threadName, val);
    }
    // when a consumer thread hits -1, meaning all values have been removed
    //printf("%s consumer is done\n", threadName);
    return NULL;
}

int main(int argc, char **argv) {
    int numConsumers = 2;
    int maxValue = 1000;

    // main() takes in two arguments, 1st is the number of consumer threads to be created, 
    // 2nd is the number of values to be added to the buffer and then to be printed out
    if (argc == 2) {
        numConsumers = atoi(argv[1]);
    }

    if (argc >= 3) {
        numConsumers = atoi(argv[1]);
        maxValue = atoi(argv[2]);
    }

    // initiate circular buffer
    initBuffer();
    pthread_t producerThread, consumerThread[numConsumers];

    // create producer thread
    if (pthread_create(&producerThread, NULL, producer, &maxValue) == -1) {
        perror("pthread_create producer");
        exit(-1);
    }

    // create consumer threads
    char threadName[numConsumers][10];
    for (int i = 0; i < numConsumers; ++i) {
        snprintf(threadName[i], 10, "Thread%d", i);
        if (pthread_create(&consumerThread[i], NULL, consumer, threadName[i]) == -1) {
            perror("pthread_create consumer");
            exit(-1);
        }
    }

    // wait for producer and consumers to finish
    pthread_join(producerThread, NULL);

    for (int i = 0; i < numConsumers; ++i) {
        pthread_join(consumerThread[i], NULL);
    }

    exit(0);
}
