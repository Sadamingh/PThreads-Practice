#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <mutex>
#define NUM_THREADS 4
#define EXE_TIMES 5
using namespace std;
mutex mu;

void *thread(void *ptr) {
    int *p = (int *) ptr;
    int num = *p;
    mu.lock();
    cout << "Thread No." << num << " has ID: " << pthread_self() << endl;
    mu.unlock();
    return 0;
}

int main() {
    int i, j;
    int nums[NUM_THREADS];

    for (j = 1; j <= EXE_TIMES; j++) {
        
        cout << "======== " << j << "-th trial ========" << endl;

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
    }

    return 0;
}