#include <stdio.h>
#include <pthread.h>

#define ELEMENTS 100000
#define THREADS 4

int a[ELEMENTS] = {0};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

volatile int spinlock1 = 0;

void lock(void) {
    while (__sync_lock_test_and_set(&spinlock1, 1))
        ;
}

void unlock(void) {
    __sync_synchronize(); // Memory barrier.
    spinlock1 = 0;
}

void *run(void *arg)
{
    (void)arg;

    lock();
    for (int i = 0; i < ELEMENTS; i++){
        // pthread_mutex_lock(&mutex);
        // lock();
        a[i]++;
        // unlock();
        // pthread_mutex_unlock(&mutex);
    }
    unlock();
    
    

    return NULL;
}

int main(void)
{
    pthread_t thread[THREADS];

    for (int i = 0; i < THREADS; i++)
        pthread_create(thread + i, NULL, run, NULL);

    for (int i = 0; i < THREADS; i++)
        pthread_join(thread[i], NULL);

    int expected = THREADS;

    for (int i = 0; i < ELEMENTS; i++)
        if (a[i] != expected)
            printf("a[%d] = %d, expected %d\n", i, a[i], expected);
}

//it is much faster having the locks on the outside of the loop because there much less values being checked and changed
//the spinlocjk is slower becasue i causes the cpu to spin more and instead of having a thread jsut sleep