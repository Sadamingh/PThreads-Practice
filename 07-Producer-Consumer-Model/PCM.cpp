#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <mutex>
#define BUFFER_SIZE 6
#define DATA 20
using namespace std;

int buffer[BUFFER_SIZE];
int num = 0;      // number of data in the buffer
int add = 0;      // buffer index for adding the next data
int rem = 0;      // buffer index for removing the next data

mutex mu;                                                // Mutex for cout
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;           // Create global mutex
pthread_cond_t Cond_prod = PTHREAD_COND_INITIALIZER;     // Produce signal for producer, send by consumer
pthread_cond_t Cond_cons = PTHREAD_COND_INITIALIZER;     // Consume signal for consumer, send by producer

void *produce(void *ptr);      // program counter for producer
void *consume(void *ptr);      // program counter for consumer

int main() {
    pthread_t producer, consumer;

    // Create producer thread
    if (pthread_create(&producer, NULL, produce, NULL)) {
        perror("ERROR");
        exit(0);
    }

    // Create consumer thread
    if (pthread_create(&consumer, NULL, consume, NULL)) {
        perror("ERROR");
        exit(0);
    }

    // Terminate threads
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    return 0;
}

void *produce(void *ptr) {
    for (int i = 1; i <= DATA; i++) {
        /* lock the mutex */
        pthread_mutex_lock(&m);

            // check if the buffer is overflow
            if (num > BUFFER_SIZE) {
                cout << "Error: Buffer Overflow." << endl;
                exit(1);
            }

            // check if the buffer is full
            while (num == BUFFER_SIZE) {
                pthread_cond_wait(&Cond_prod, &m);
            }

            buffer[add] = i;
            add = (add + 1) % BUFFER_SIZE;    // Consider the wrap around situation
            num++;                            // Increment for numbers in the buffer

        /* unlock the mutex */
        pthread_mutex_unlock(&m);

        // Send the condition variable to consumer
        pthread_cond_signal(&Cond_cons);

        // Output to show progress
        mu.lock();
        cout << "Successfully insert " << i << endl;
        mu.unlock();
    }

    // End of execution
    cout << "End of the producer." << endl;

    return NULL;
}

void *consume(void *ptr) {

    while(1) {
        /* lock the mutex */
        pthread_mutex_lock(&m);

            // check if the buffer is overflow
            if (num < 0) {
                cout << "Error: Buffer Overflow." << endl;
                exit(1);
            }

            // check if the buffer is empty
            while (num == 0) {
                pthread_cond_wait(&Cond_cons, &m);
            }

            // Read and then remove data from the buffer
            mu.lock();
            cout << "Successfully capture " << buffer[rem] << endl;
            mu.unlock();
            rem = (rem + 1) % BUFFER_SIZE;       // Consider the wrap around situation
            num--;                               // Reduction for numbers in the buffer
            
        /* unlock the mutex */
        pthread_mutex_unlock(&m);

        // Send the condition variable to consumer
        pthread_cond_signal(&Cond_prod);
    }

    return NULL;
}
