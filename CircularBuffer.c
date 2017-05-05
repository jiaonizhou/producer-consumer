#include <stdlib.h>
#include <pthread.h>

#define BUFFER_MAX_LEN      20

static int buffer[BUFFER_MAX_LEN];

static unsigned int head;
static unsigned int size;

static pthread_mutex_t bufferLock;
static pthread_cond_t empty, full;

void initBuffer() {
    head = 0;
    size = 0;
    pthread_mutex_init(&bufferLock, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);
}

void addToBuffer(int val) {
    pthread_mutex_lock(&bufferLock);
    while(size >= BUFFER_MAX_LEN) {
        pthread_cond_wait(&full, &bufferLock);
    }

    int index = head + size >= BUFFER_MAX_LEN ? head + size - BUFFER_MAX_LEN : head + size;

    buffer[index] = val;
    size++;

    pthread_cond_signal(&empty);

    pthread_mutex_unlock(&bufferLock);
}

int removeFromBuffer() {
    int val;
    pthread_mutex_lock(&bufferLock);
    while(size == 0) {
        pthread_cond_wait(&empty, &bufferLock);
    }

    val = buffer[head];

    if (val != -1) {
        size--;
        head++;
    }

    if (head >= BUFFER_MAX_LEN) {
        head -= BUFFER_MAX_LEN;
    }

    pthread_cond_signal(&full);

    pthread_mutex_unlock(&bufferLock);

    return val;
}
