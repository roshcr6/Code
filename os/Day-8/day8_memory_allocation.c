/*
 * Day 8: Memory Allocation Methods for Fixed Partition using Linked List
 * 
 * This program implements three memory allocation strategies:
 * a. First Fit - Allocate the first block that is big enough
 * b. Worst Fit - Allocate the largest available block
 * c. Best Fit - Allocate the smallest block that is big enough
 */

#include <stdio.h>      // For input/output functions like printf, scanf
#include <stdlib.h>     // For malloc() function and memory management
#include <stdbool.h>    // For bool, true, false data types (used in while loop)

// Structure to represent a memory block (node in linked list)
struct Block {              // Structure definition for memory block
    int block_id;           // Unique identifier for the memory block
    int block_size;         // Total size of the memory block in KB
    int allocated;          // Flag: 1 if allocated to a process, 0 if free
    int process_id;         // ID of process allocated to this block (-1 if not allocated)
    int process_size;       // Size of process allocated to this block (0 if not allocated)
    int internal_frag;      // Internal fragmentation (leftover space in block)
    struct Block* next;     // Pointer to next block in linked list
};
struct Block* head = NULL;  // Global pointer to first node of linked list (initially NULL)

// Function to create n memory blocks as a linked list
void createBlocks(int n) {              // Takes number of blocks as parameter
    struct Block *temp, *newNode;       // temp: for traversal, newNode: for new block
    int size;                           // Variable to store block size input from user
    for(int i = 1; i <= n; i++) {       // Loop to create n blocks
        newNode = (struct Block*)malloc(sizeof(struct Block));  // Allocate memory for new block
        printf("Enter size of Block %d: ", i);  // Prompt user for block size
        scanf("%d", &size);             // Read block size from user
        newNode->block_id = i;          // Assign block ID (starting from 1)
        newNode->block_size = size;     // Store the block size
        newNode->allocated = 0;         // Initially block is not allocated (free)
        newNode->process_id = -1;       // No process allocated yet (-1 indicates empty)
        newNode->process_size = 0;      // No process size yet (0 indicates empty)
        newNode->internal_frag = 0;     // No fragmentation initially
        newNode->next = NULL;           // Last node points to NULL
        if(head == NULL)                // If this is the first block
            head = newNode;             // Make it the head of linked list
        else {                          // If list already has blocks
            temp = head;                // Start from head
            while(temp->next != NULL)   // Traverse to the last node
                temp = temp->next;      // Move to next node
            temp->next = newNode;       // Link new node at the end
        }
    }
}

// Function to reset all blocks to free state (for reusing in different algorithms)
void resetBlocks() {                    // Function takes no parameters
    struct Block* temp = head;          // Start from head of linked list
    while(temp != NULL) {               // Loop through all blocks
        temp->allocated = 0;            // Mark block as free
        temp->process_id = -1;          // Reset process ID to -1
        temp->process_size = 0;         // Reset process size to 0
        temp->internal_frag = 0;        // Reset internal fragmentation to 0
        temp = temp->next;              // Move to next block
    }
}

// Function to display allocation results in a formatted table
void display() {                        // Function takes no parameters
    struct Block* temp = head;          // Start from head of linked list
    int total_frag = 0;                 // Variable to accumulate total internal fragmentation
    // Print table header with column labels (%-10s means left-aligned, 10 characters wide)
    printf("\n\n%-10s %-10s %-15s %-15s %-20s\n", 
           "Process", "Block", "Process Size", "Block Size", "Internal Frag");
    printf("-----------------------------------------------------------------------\n");  // Separator line
    while(temp != NULL) {               // Loop through all blocks in linked list
        if(temp->allocated) {           // Only display blocks that have been allocated
            // Print process details in formatted table row (%-Nd means left-aligned, N digits)
            printf("P%-9d %-10d %-15d %-15d %-20d\n",
                   temp->process_id,    // Process ID (P1, P2, etc.)
                   temp->block_id,      // Block ID where process is allocated
                   temp->process_size,  // Size of process in KB
                   temp->block_size,    // Size of block in KB
                   temp->internal_frag);  // Internal fragmentation in KB
            total_frag += temp->internal_frag;  // Add to total fragmentation
        }
        temp = temp->next;              // Move to next block
    }
    printf("-----------------------------------------------------------------------\n");  // Separator line
    printf("Total Internal Fragmentation: %d KB\n", total_frag);  // Display sum of all fragmentation
}

// First Fit Algorithm: Allocate first block that is large enough
void firstFit(int processes[], int m) {  // Takes array of process sizes and count
    printf("\n========== FIRST FIT ==========\n");  // Display algorithm name
    for(int i = 0; i < m; i++) {        // Loop through each process
        struct Block* temp = head;      // Start from head of linked list
        int allocated = 0;              // Flag to track if process was allocated
        while(temp != NULL) {           // Loop through all blocks
            if(temp->allocated == 0 &&  // Check if block is free AND
               temp->block_size >= processes[i]) {  // block size is sufficient
                temp->allocated = 1;    // Mark block as allocated
                temp->process_id = i+1; // Assign process ID (i+1 for 1-based indexing)
                temp->process_size = processes[i];  // Store process size
                temp->internal_frag =   // Calculate internal fragmentation
                    temp->block_size - processes[i];  // Block size minus process size
                allocated = 1;          // Set flag that process was allocated
                break;                  // Exit loop (first fit found)
            }
            temp = temp->next;          // Move to next block
        }
        if(!allocated)                  // If process was not allocated
            printf("Process P%d (%d KB) not allocated\n", i+1, processes[i]);  // Display error message
    }
    display();                          // Display results in table format
}

// Best Fit Algorithm: Allocate smallest block that is large enough
void bestFit(int processes[], int m) {  // Takes array of process sizes and count
    printf("\n========== BEST FIT ==========\n");  // Display algorithm name
    for(int i = 0; i < m; i++) {        // Loop through each process
        struct Block* temp = head;      // Start from head of linked list
        struct Block* best = NULL;      // Pointer to best fit block (initially NULL)
        int min = 999999;               // Variable to track minimum difference (initialized to large value)
        while(temp != NULL) {           // Loop through all blocks
            if(temp->allocated == 0 &&  // Check if block is free AND
               temp->block_size >= processes[i]) {  // block size is sufficient
                int diff = temp->block_size - processes[i];  // Calculate wasted space
                if(diff < min) {        // If this is a better fit (less waste)
                    min = diff;         // Update minimum difference
                    best = temp;        // Update best fit block pointer
                }
            }
            temp = temp->next;          // Move to next block
        }
        if(best != NULL) {              // If a suitable block was found
            best->allocated = 1;        // Mark block as allocated
            best->process_id = i+1;     // Assign process ID
            best->process_size = processes[i];  // Store process size
            best->internal_frag =       // Calculate internal fragmentation
                best->block_size - processes[i];  // Block size minus process size
        } else {                        // If no suitable block was found
            printf("Process P%d (%d KB) not allocated\n", i+1, processes[i]);  // Display error message
        }
    }
    display();                          // Display results in table format
}

// Worst Fit Algorithm: Allocate largest available block
void worstFit(int processes[], int m) { // Takes array of process sizes and count
    printf("\n========== WORST FIT ==========\n");  // Display algorithm name
    for(int i = 0; i < m; i++) {        // Loop through each process
        struct Block* temp = head;      // Start from head of linked list
        struct Block* worst = NULL;     // Pointer to worst fit block (initially NULL)
        int max = -1;                   // Variable to track maximum difference (initialized to -1)
        while(temp != NULL) {           // Loop through all blocks
            if(temp->allocated == 0 &&  // Check if block is free AND
               temp->block_size >= processes[i]) {  // block size is sufficient
                int diff = temp->block_size - processes[i];  // Calculate leftover space
                if(diff > max) {        // If this has more leftover space (worse fit)
                    max = diff;         // Update maximum difference
                    worst = temp;       // Update worst fit block pointer
                }
            }
            temp = temp->next;          // Move to next block
        }
        if(worst != NULL) {             // If a suitable block was found
            worst->allocated = 1;       // Mark block as allocated
            worst->process_id = i+1;    // Assign process ID
            worst->process_size = processes[i];  // Store process size
            worst->internal_frag =      // Calculate internal fragmentation
                worst->block_size - processes[i];  // Block size minus process size
        } else {                        // If no suitable block was found
            printf("Process P%d (%d KB) not allocated\n", i+1, processes[i]);  // Display error message
        }
    }
    display();                          // Display results in table format
}
           
int main() {                            // Main function - program execution starts here
    int n, m, choice;                   // n: number of blocks, m: number of processes, choice: menu option
    printf("Enter number of memory blocks: ");  // Prompt for number of memory blocks
    scanf("%d", &n);                    // Read number of blocks from user
    createBlocks(n);                    // Call function to create n memory blocks as linked list
    printf("\nEnter number of processes: ");  // Prompt for number of processes
    scanf("%d", &m);                    // Read number of processes from user
    int processes[m];                   // Declare array to store process sizes
    for(int i = 0; i < m; i++) {        // Loop to input size of each process
        printf("Enter size of Process P%d: ", i+1);  // Prompt for process size (1-based indexing)
        scanf("%d", &processes[i]);     // Read process size into array
    }
    
    while(true) {                       // Infinite loop for menu system (until user exits)
        printf("\n========================================\n");  // Display menu separator
        printf("             MAIN MENU\n");  // Display menu title
        printf("========================================\n");  // Display menu separator
        printf("1. First Fit\n");       // Option 1: Run First Fit algorithm
        printf("2. Best Fit\n");        // Option 2: Run Best Fit algorithm
        printf("3. Worst Fit\n");       // Option 3: Run Worst Fit algorithm
        printf("4. Exit\n");            // Option 4: Exit program
        printf("========================================\n");  // Display menu separator
        printf("Enter your choice: ");  // Prompt for user choice
        scanf("%d", &choice);           // Read user's menu choice
        
        resetBlocks();                  // Reset all blocks to free state before running algorithm
        
        switch(choice) {                // Check which option user selected
            case 1:                     // If user chose First Fit
                firstFit(processes, m); // Call First Fit function with process array and count
                break;                  // Exit switch statement
            case 2:                     // If user chose Best Fit
                bestFit(processes, m);  // Call Best Fit function with process array and count
                break;                  // Exit switch statement
            case 3:                     // If user chose Worst Fit
                worstFit(processes, m); // Call Worst Fit function with process array and count
                break;                  // Exit switch statement
            case 4:                     // If user chose Exit
                printf("\nExiting program. Thank you!\n");  // Display exit message
                return 0;               // Exit main function (terminates program)
            default:                    // If user entered invalid option
                printf("Invalid Choice\n");  // Display error message
        }
    }   
    return 0;                           // Return 0 to indicate successful execution (unreachable)
}