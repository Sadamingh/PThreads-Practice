#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
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
    
    // Configure the attributes.
    pthread_attr_t attr;
    pthread_attr_init(&attr); /* must require */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);   // set a detached thread
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);           // set the system scope
    pthread_attr_setstacksize(&attr, 512);                          // set the stack size

    cout << pthread_self() << ": Creating a PThread..." << endl;
    pthread_t hThread;
    if (pthread_create(&hThread, &attr, foo, NULL)) {    // eqvivalent to thread1 = fork(proc, args)
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
    // Create a thread.
    cout << pthread_self() << ": Creating a PThread..." << endl;
    pthread_t hThread;
    if (pthread_create(&hThread, NULL, thread, NULL)) {    // eqvivalent to thread1 = fork(proc, args)
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