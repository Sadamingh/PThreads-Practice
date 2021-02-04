#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#define NUM_THREADS 5
#define BUFFER_SIZE 5
using namespace std;

int buffer[BUFFER_SIZE];
int num = 0;
int add = 0;
int rem = 0;

void *thread(void *ptr) {
        int *p = (int *) ptr;
        int val = *p;
        buffer[add] = val;
        add++;
        num++;
        if (num > BUFFER_SIZE){
            cout << "ERROR: Overflow" << endl;
            exit(1);
        }
    return 0;
}

int main() {
    int i;
    int nums[NUM_THREADS];

    // Create threads.
    pthread_t hThreads[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++){
        nums[i] = i;
        if (pthread_create(&hThreads[i], NULL, thread, &nums[i])) {    // eqvivalent to thread1 = fork(proc, args)
            perror("ERROR");
            exit(0);
        }
    }

    // Terminate threads.
    for (i = 0; i < NUM_THREADS; i++){
        pthread_join(hThreads[i], NULL);       // eqvivalent to join()
    }

    for (i = 0; i < BUFFER_SIZE; i++){
        cout << buffer[i] << endl;
    }

    return 0;
}