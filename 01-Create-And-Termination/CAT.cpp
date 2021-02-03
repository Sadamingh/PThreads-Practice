#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
using namespace std;

void *thread(void *ptr)
{   
    cout << "PThead: This is a pthread." << endl;
    sleep(1);
    return 0;
}

int main() {
    // Create a thread.
    cout << "Creating a PThread..." << endl;
    pthread_t hThread;
    if (pthread_create(&hThread, NULL, thread, NULL)) {    // eqvivalent to thread1 = fork(proc, args)
        perror("ERROR");
        exit(0);
    } else {
        cout << "Successfully created!" << endl;
    }

    // Terminate the thread.
    cout << "Block the current thread..." << endl;
    pthread_join(hThread, NULL);       // eqvivalent to join()
    cout << "End of execution." << endl;

    return 0;
}