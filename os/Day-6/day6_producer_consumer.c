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

#include <stdio.h>
#include <stdlib.h>

// Semaphore variables
int mutex = 1;    // Binary semaphore for mutual exclusion
int full = 0;     // Counting semaphore for full slots
int empty = 5;    // Counting semaphore for empty slots (buffer size = 5)
int x = 0;        // Item counter

// Semaphore wait operation (P operation / down operation)
int wait(int *s)
{
    return --(*s);
}

// Semaphore signal operation (V operation / up operation)
int signal(int *s)
{
    return ++(*s);
}

// Producer function
void producer()
{
    wait(&mutex);      // Enter critical section
    wait(&empty);      // Decrease empty count
    signal(&full);     // Increase full count
    
    x++;               // Produce item
    printf("Producer produces item %d\n", x);
    
    signal(&mutex);    // Exit critical section
}

// Consumer function
void consumer()
{
    wait(&mutex);      // Enter critical section
    wait(&full);       // Decrease full count
    signal(&empty);    // Increase empty count
    
    printf("Consumer consumes item %d\n", x);
    x--;               // Consume item
    
    signal(&mutex);    // Exit critical section
}



int main()
{
    int n, t;
    
    printf("║  PRODUCER-CONSUMER PROBLEM SIMULATOR  ║\n");
    printf("║     Using Semaphores (50 iterations)   ║\n");
    
    for(t = 0; t < 50; t++)
    {
        int i = rand() % 100;
        n = i % 2;
        
        switch (n) 
        {
            case 0:  // Try to produce
                if ((mutex == 1) && (empty != 0)) 
                {
                    producer();
                }
                else 
                {
                    printf("Buffer is full! Cannot produce.\n");
                }
                break;

            case 1:  // Try to consume
                if ((mutex == 1) && (full != 0)) 
                {
                    consumer();
                }
                else 
                {
                    printf("Buffer is empty! Cannot consume.\n");
                }
                break;
        } 
    }
    
    printf("\n========================================\n");
    printf("Simulation completed!\n");
    printf("Final Semaphore Values:\n");
    printf("  mutex = %d\n", mutex);
    printf("  empty = %d\n", empty);
    printf("  full  = %d\n", full);
    printf("  Items in buffer = %d\n", x);
    printf("========================================\n");
    
    return 0;
}