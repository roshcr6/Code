/*
 * Day 6: Producer-Consumer Problem using Semaphores
 * 
 * This program simulates the classic Producer-Consumer problem where:
 * - Producer produces items and puts them in a buffer
 * - Consumer consumes items from the buffer
 * - Semaphores ensure synchronization between producer and consumer
 * 
 * Semaphore Operations:
 * - wait(S): Decrements semaphore S (blocks if S <= 0)
 * - signal(S): Increments semaphore S
 * 
 * The program runs 50 random iterations of producer/consumer operations
 */

#include <stdio.h>      // For input/output functions like printf, scanf
#include <stdlib.h>     // For rand() function

// Semaphore variables
int mutex = 1;          // Binary semaphore for mutual exclusion (1 = available, 0 = locked)
int full = 0;           // Counting semaphore for full slots (initially 0, no items in buffer)
int empty = 5;          // Counting semaphore for empty slots (buffer size = 5, all empty initially)
int x = 0;              // Item counter to track produced items

// Semaphore wait operation (P operation / down operation)
int wait(int *s)        // Takes pointer to semaphore as parameter
{
    return --(*s);      // Decrements semaphore value by 1 and returns new value
}

// Semaphore signal operation (V operation / up operation)
int signal(int *s)      // Takes pointer to semaphore as parameter
{
    return ++(*s);      // Increments semaphore value by 1 and returns new value
}

// Producer function
void producer()         // Function to produce items and add to buffer
{
    wait(&mutex);       // Acquire mutex lock to enter critical section
    wait(&empty);       // Decrease empty slot count (one slot will be filled)
    signal(&full);      // Increase full slot count (one more item in buffer)
    
    x++;                // Increment item counter (produce new item)
    printf("Producer produces item %d\n", x);  // Display produced item number
    
    signal(&mutex);     // Release mutex lock to exit critical section
}

// Consumer function
void consumer()         // Function to consume items from buffer
{
    wait(&mutex);       // Acquire mutex lock to enter critical section
    wait(&full);        // Decrease full slot count (one item will be consumed)
    signal(&empty);     // Increase empty slot count (one slot becomes free)
    
    printf("Consumer consumes item %d\n", x);  // Display consumed item number
    x--;                // Decrement item counter (consume item)
    
    signal(&mutex);     // Release mutex lock to exit critical section
}



int main()              // Main function - program execution starts here
{
    int n, t;           // n = random choice (0 or 1), t = loop counter
    
    printf("║  PRODUCER-CONSUMER PROBLEM SIMULATOR  ║\n");  // Display program title
    printf("║     Using Semaphores (50 iterations)   ║\n");  // Display subtitle
    
    for(t = 0; t < 50; t++)  // Loop 50 times for simulation
    {
        int i = rand() % 100;  // Generate random number between 0-99
        n = i % 2;             // Convert to 0 or 1 (even=0=producer, odd=1=consumer)
        
        switch (n)             // Check which operation to perform
        {
            case 0:            // If n=0, try to produce
                if ((mutex == 1) && (empty != 0))  // Check if mutex available and buffer not full
                {
                    producer();  // Call producer function
                }
                else           // If buffer is full
                {
                    printf("Buffer is full! Cannot produce.\n");  // Display error message
                }
                break;         // Exit switch statement

            case 1:            // If n=1, try to consume
                if ((mutex == 1) && (full != 0))  // Check if mutex available and buffer not empty
                {
                    consumer();  // Call consumer function
                }
                else           // If buffer is empty
                {
                    printf("Buffer is empty! Cannot consume.\n");  // Display error message
                }
                break;         // Exit switch statement
        } 
    }
    
    printf("\n========================================\n");  // Display separator
    printf("Simulation completed!\n");                 // Display completion message
    printf("Final Semaphore Values:\n");               // Display final state header
    printf("  mutex = %d\n", mutex);                   // Display final mutex value
    printf("  empty = %d\n", empty);                   // Display final empty slots count
    printf("  full  = %d\n", full);                    // Display final full slots count
    printf("  Items in buffer = %d\n", x);             // Display final items in buffer
    printf("========================================\n");  // Display separator
    
    return 0;          // Return 0 to indicate successful program execution
}