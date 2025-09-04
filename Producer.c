#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // Buffer size

int mutex = 1;         // Binary semaphore for mutual exclusion
int full = 0;          // Count of full slots
int empty = SIZE;      // Count of empty slots
int buffer[SIZE];      // Shared buffer
int in = 0, out = 0;   // Pointers for producer and consumer

// Function to simulate wait operation on semaphore
int wait(int s) {
    return (--s);
}

// Function to simulate signal operation on semaphore
int signal(int s) {
    return (++s);
}

// Producer function
void producer() {
    int item;
    if ((mutex == 1) && (empty != 0)) {
        printf("Enter the value: ");
        scanf("%d", &item);

        // Critical section
        mutex = wait(mutex);
        empty = wait(empty);

        buffer[in] = item;
        in = (in + 1) % SIZE;

        full = signal(full);
        mutex = signal(mutex);

        printf("Item produced: %d\n", item);
    } else {
        printf("Buffer is Full\n");
    }
}

// Consumer function
void consumer() {
    if ((mutex == 1) && (full != 0)) {
        // Critical section
        mutex = wait(mutex);
        full = wait(full);

        int item = buffer[out];
        out = (out + 1) % SIZE;

        empty = signal(empty);
        mutex = signal(mutex);

        printf("The consumed value is %d\n", item);
    } else {
        printf("Buffer is Empty\n");
    }
}

int main() {
    int choice;
    printf("\n--- Producer Consumer Problem Simulation ---\n");
    while (1) {
        printf("\n1. Produce  2. Consume  3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
