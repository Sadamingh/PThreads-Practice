#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#define NUM_THREADS 2
using namespace std;

void *foo(void *ptr) {
    cout << pthread_self() << ": This is a pthread." << endl;
    sleep(1);   // does not work because DETACHED
    return 0;
}

void *thread(void *ptr)
{   
    cout << pthread_self() << ": This is a pthread." << endl;
    sleep(1);   // works because JOINABLE

    cout << pthread_self() << ": Creating a PThread..." << endl;
    pthread_t hThread;
    if (pthread_create(&hThread, NULL, foo, NULL)) {    // eqvivalent to thread1 = fork(proc, args)
        perror("ERROR");
        exit(0);
    } else {
        cout << pthread_self() << ": Successfully created!" << endl;
    }

    // Terminate the thread.
    cout << pthread_self() << ": Block the current thread..." << endl;
    pthread_join(hThread, NULL);       // eqvivalent to join()
    cout << pthread_self() << ": End of execution." << endl;

    return 0;
}

int main() {
    int i;

    // Create threads.
    cout << pthread_self() << ": Creating a PThread..." << endl;
    pthread_t hThreads[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++){
        if (pthread_create(&hThreads[i], NULL, thread, NULL)) {    // eqvivalent to thread1 = fork(proc, args)
            perror("ERROR");
            exit(0);
        } else {
            cout << pthread_self() << ": Successfully created!" << endl;
        }
    }

    // Terminate threads.
    for (i = 0; i < NUM_THREADS; i++){
        cout << pthread_self() << ": Block the current thread..." << endl;
        pthread_join(hThreads[i], NULL);       // eqvivalent to join()
        cout << pthread_self() << ": End of execution." << endl;
    }

    return 0;
}