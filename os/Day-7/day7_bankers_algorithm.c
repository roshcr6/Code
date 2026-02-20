/*
 * Day 7: Banker's Algorithm for Deadlock Avoidance
 * 
 * This program implements the Banker's Algorithm which is used to avoid deadlock
 * by checking if a resource allocation request will lead to a safe state.
 * 
 * Key Concepts:
 * - Allocation: Currently allocated resources to each process
 * - Max: Maximum resources needed by each process
 * - Available: Currently available resources in the system
 * - Need: Remaining resources needed by each process (Max - Allocation)
 * 
 * The algorithm checks if granting a request keeps the system in a safe state.
 */

#include <stdio.h>      // For input/output functions like printf, scanf
#include <stdlib.h>     // For exit() function
#include <stdbool.h>    // For bool, true, false data types

#define MAX_PROCESSES 10   // Maximum number of processes that can be handled
#define MAX_RESOURCES 10   // Maximum number of resource types that can be handled

int n;  // Variable to store actual number of processes in the system
int m;  // Variable to store actual number of resource types in the system

int allocation[MAX_PROCESSES][MAX_RESOURCES];  // 2D array storing currently allocated resources for each process
int max[MAX_PROCESSES][MAX_RESOURCES];         // 2D array storing maximum resources needed by each process
int available[MAX_RESOURCES];                  // Array storing currently available resources
int need[MAX_PROCESSES][MAX_RESOURCES];        // 2D array storing remaining resources needed by each process

// Function to calculate the Need matrix (Need = Max - Allocation)
void calculateNeed() {                      // Function takes no parameters
    for (int i = 0; i < n; i++) {           // Loop through each process
        for (int j = 0; j < m; j++) {       // Loop through each resource type
            need[i][j] = max[i][j] - allocation[i][j];  // Calculate remaining need for process i, resource j
        }
    }
}

// Function to check if system is in safe state using Safety Algorithm
bool isSafe() {                                    // Returns true if safe, false if unsafe
    int work[MAX_RESOURCES];                       // Temporary array to track available resources during execution
    bool finish[MAX_PROCESSES] = {false};          // Array to track which processes have finished (all initialized to false)
    int safeSequence[MAX_PROCESSES];               // Array to store the safe sequence of process execution
    int count = 0;                                 // Counter for number of processes added to safe sequence
    
    // Initialize work with available resources
    for (int i = 0; i < m; i++) {                  // Loop through each resource type
        work[i] = available[i];                    // Copy available resources to work array
    }
    
    printf("\n--- Safety Algorithm Execution ---\n");  // Display header for safety check
    
    // Find a safe sequence by repeatedly finding processes that can complete
    while (count < n) {                            // Continue until all processes are in safe sequence
        bool found = false;                        // Flag to check if we found a process that can execute in this iteration
        
        for (int i = 0; i < n; i++) {              // Loop through each process
            if (!finish[i]) {                      // If process i has not finished yet
                // Check if process i can be allocated resources (Need <= Work)
                bool canAllocate = true;           // Assume process can be allocated resources
                for (int j = 0; j < m; j++) {      // Check each resource type
                    if (need[i][j] > work[j]) {    // If need exceeds available work resources
                        canAllocate = false;       // Process cannot be allocated
                        break;                     // No need to check further resources
                    }
                }
                
                if (canAllocate) {                 // If all needed resources are available
                    // Allocate resources to process i (simulate execution and release)
                    printf("Process P%d can be allocated. ", i);  // Display which process is being allocated
                    printf("Work: [");             // Display current work array
                    for (int j = 0; j < m; j++) {  // Loop through each resource
                        work[j] += allocation[i][j];  // Add back allocated resources (process finishes and releases)
                        printf("%d", work[j]);     // Display updated work value for this resource
                        if (j < m - 1) printf(", ");  // Add comma separator between resources
                    }
                    printf("]\n");                 // End of work array display
                    
                    safeSequence[count++] = i;     // Add process to safe sequence and increment counter
                    finish[i] = true;              // Mark process as finished
                    found = true;                  // Set flag that we found a process
                }
            }
        }
        
        if (!found) {                              // If no process could be allocated in this iteration
            printf("\nSystem is in UNSAFE state! Deadlock may occur.\n");  // System is unsafe
            return false;                          // Return false indicating unsafe state
        }
    }
    
    printf("\nSystem is in SAFE state!\n");        // All processes added to safe sequence
    printf("Safe Sequence: < ");                   // Display the safe sequence
    for (int i = 0; i < n; i++) {                  // Loop through safe sequence array
        printf("P%d", safeSequence[i]);            // Print process number
        if (i < n - 1) printf(", ");               // Add comma separator between processes
    }
    printf(" >\n");                                // End of safe sequence display
    
    return true;                                   // Return true indicating safe state
}

// Function to handle resource allocation requests from processes
void requestResources() {                         // Function to process a resource request
    int process;                                   // Variable to store process number making the request
    int request[MAX_RESOURCES];                    // Array to store requested amount for each resource
    
    printf("\nEnter process number (0 to %d): ", n - 1);  // Prompt for process number
    scanf("%d", &process);                         // Read process number from user
    
    if (process < 0 || process >= n) {             // Check if process number is valid
        printf("Invalid process number!\n");       // Display error message
        return;                                    // Exit function
    }
    
    printf("Enter resource request for P%d:\n", process);  // Prompt for resource amounts
    for (int i = 0; i < m; i++) {                  // Loop through each resource type
        printf("  Resource R%d: ", i);             // Prompt for specific resource
        scanf("%d", &request[i]);                  // Read requested amount
    }
    
    // Check if request is less than or equal to need (Request <= Need)
    printf("\n--- Checking Request Validity ---\n");  // Display validation header
    for (int i = 0; i < m; i++) {                  // Loop through each resource type
        if (request[i] > need[process][i]) {       // If request exceeds need
            printf("Error: Process P%d has exceeded its maximum claim!\n", process);  // Display error
            printf("Requested R%d: %d, but Need: %d\n", i, request[i], need[process][i]);  // Show details
            return;                                // Exit function (request denied)
        }
    }
    
    // Check if request is less than or equal to available (Request <= Available)
    for (int i = 0; i < m; i++) {                  // Loop through each resource type
        if (request[i] > available[i]) {           // If request exceeds available resources
            printf("Error: Resources not available!\n");  // Display error message
            printf("Requested R%d: %d, but Available: %d\n", i, request[i], available[i]);  // Show details
            printf("Process P%d must wait.\n", process);  // Process must wait
            return;                                // Exit function (request denied)
        }
    }
    
    // Try allocating resources temporarily to check if system remains safe
    printf("\nTrying to allocate resources temporarily...\n");  // Display allocation attempt message
    for (int i = 0; i < m; i++) {                  // Loop through each resource type
        available[i] -= request[i];                // Decrease available resources
        allocation[process][i] += request[i];      // Increase allocation to process
        need[process][i] -= request[i];            // Decrease need of process
    }
    
    // Check if system is in safe state after temporary allocation
    if (isSafe()) {                                // Call safety algorithm
        printf("\nRequest GRANTED! Resources allocated to P%d.\n", process);  // Request approved
    } else {                                       // If system becomes unsafe
        // Rollback the allocation (undo the temporary allocation)
        printf("\nRequest DENIED! Rolling back allocation.\n");  // Request rejected
        for (int i = 0; i < m; i++) {              // Loop through each resource type
            available[i] += request[i];            // Restore available resources
            allocation[process][i] -= request[i];  // Remove allocation from process
            need[process][i] += request[i];        // Restore need of process
        }
        printf("Process P%d must wait to avoid deadlock.\n", process);  // Process must wait message
    }
}

// Function to display current state of all matrices and available resources
void displayState() {                             // Function to print system state
    printf("\n========================================\n");  // Display separator
    printf("         CURRENT SYSTEM STATE\n");     // Display title
    printf("========================================\n");  // Display separator
    
    printf("\nAllocation Matrix:\n");              // Header for allocation matrix
    printf("Process  ");                           // Column header for process
    for (int i = 0; i < m; i++) printf("R%d  ", i);  // Column headers for each resource
    printf("\n");                                  // New line after headers
    for (int i = 0; i < n; i++) {                  // Loop through each process
        printf("P%d       ", i);                   // Print process number
        for (int j = 0; j < m; j++) {              // Loop through each resource type
            printf("%2d  ", allocation[i][j]);     // Print allocated amount (right-aligned, 2 digits)
        }
        printf("\n");                              // New line after each process row
    }
    
    printf("\nMax Matrix:\n");                     // Header for max matrix
    printf("Process  ");                           // Column header for process
    for (int i = 0; i < m; i++) printf("R%d  ", i);  // Column headers for each resource
    printf("\n");                                  // New line after headers
    for (int i = 0; i < n; i++) {                  // Loop through each process
        printf("P%d       ", i);                   // Print process number
        for (int j = 0; j < m; j++) {              // Loop through each resource type
            printf("%2d  ", max[i][j]);            // Print maximum need (right-aligned, 2 digits)
        }
        printf("\n");                              // New line after each process row
    }
    
    printf("\nNeed Matrix:\n");                    // Header for need matrix
    printf("Process  ");                           // Column header for process
    for (int i = 0; i < m; i++) printf("R%d  ", i);  // Column headers for each resource
    printf("\n");                                  // New line after headers
    for (int i = 0; i < n; i++) {                  // Loop through each process
        printf("P%d       ", i);                   // Print process number
        for (int j = 0; j < m; j++) {              // Loop through each resource type
            printf("%2d  ", need[i][j]);           // Print remaining need (right-aligned, 2 digits)
        }
        printf("\n");                              // New line after each process row
    }
    
    printf("\nAvailable Resources: ");             // Header for available resources
    for (int i = 0; i < m; i++) {                  // Loop through each resource type
        printf("R%d=%d  ", i, available[i]);       // Print resource number and available quantity
    }
    printf("\n");                                  // New line at end
}

// Function to input data manually from user
void inputData() {                                 // Function to get system data from user input
    printf("\n--- Enter System Information ---\n");  // Display input section header
    
    printf("Enter number of processes: ");         // Prompt for number of processes
    scanf("%d", &n);                               // Read number of processes into n
    
    printf("Enter number of resource types: ");    // Prompt for number of resource types
    scanf("%d", &m);                               // Read number of resource types into m
    
    printf("\n--- Enter Allocation Matrix ---\n"); // Header for allocation input
    for (int i = 0; i < n; i++) {                  // Loop through each process
        printf("Process P%d allocation:\n", i);    // Display which process we're entering data for
        for (int j = 0; j < m; j++) {              // Loop through each resource type
            printf("  Resource R%d: ", j);         // Prompt for specific resource
            scanf("%d", &allocation[i][j]);        // Read allocation value for process i, resource j
        }
    }
    
    printf("\n--- Enter Max Matrix ---\n");        // Header for max matrix input
    for (int i = 0; i < n; i++) {                  // Loop through each process
        printf("Process P%d maximum need:\n", i);  // Display which process we're entering data for
        for (int j = 0; j < m; j++) {              // Loop through each resource type
            printf("  Resource R%d: ", j);         // Prompt for specific resource
            scanf("%d", &max[i][j]);               // Read maximum need value for process i, resource j
        }
    }
    
    printf("\n--- Enter Available Resources ---\n");  // Header for available resources input
    for (int i = 0; i < m; i++) {                  // Loop through each resource type
        printf("Resource R%d: ", i);               // Prompt for specific resource
        scanf("%d", &available[i]);                // Read available quantity for resource i
    }
    
    calculateNeed();                               // Calculate need matrix (Need = Max - Allocation)
    printf("\nData entered successfully!\n");      // Display success message
}

// Function to load predefined example data for quick testing
void useExampleData() {                            // Function to load example data
    n = 5;  // Set number of processes to 5
    m = 3;  // Set number of resource types to 3
    
    // Predefined Allocation Matrix (currently allocated resources)
    int alloc[5][3] = {                            // 5 processes, 3 resource types
        {0, 1, 0},                                 // Process P0: 0 of R0, 1 of R1, 0 of R2
        {2, 0, 0},                                 // Process P1: 2 of R0, 0 of R1, 0 of R2
        {3, 0, 2},                                 // Process P2: 3 of R0, 0 of R1, 2 of R2
        {2, 1, 1},                                 // Process P3: 2 of R0, 1 of R1, 1 of R2
        {0, 0, 2}                                  // Process P4: 0 of R0, 0 of R1, 2 of R2
    };
    
    // Predefined Max Matrix (maximum resources needed)
    int maximum[5][3] = {                          // 5 processes, 3 resource types
        {7, 5, 3},                                 // Process P0 max: 7 of R0, 5 of R1, 3 of R2
        {3, 2, 2},                                 // Process P1 max: 3 of R0, 2 of R1, 2 of R2
        {9, 0, 2},                                 // Process P2 max: 9 of R0, 0 of R1, 2 of R2
        {2, 2, 2},                                 // Process P3 max: 2 of R0, 2 of R1, 2 of R2
        {4, 3, 3}                                  // Process P4 max: 4 of R0, 3 of R1, 3 of R2
    };
    
    // Predefined Available Resources
    int avail[3] = {3, 3, 2};                      // R0=3, R1=3, R2=2 available
    
    // Copy predefined data to global arrays
    for (int i = 0; i < n; i++) {                  // Loop through each process
        for (int j = 0; j < m; j++) {              // Loop through each resource type
            allocation[i][j] = alloc[i][j];        // Copy allocation value
            max[i][j] = maximum[i][j];             // Copy max value
        }
    }
    
    for (int i = 0; i < m; i++) {                  // Loop through each resource type
        available[i] = avail[i];                   // Copy available value
    }
    
    calculateNeed();                               // Calculate need matrix from max and allocation
    printf("\nExample data loaded successfully!\n");  // Display success message
}

int main() {                                       // Main function - program execution starts here
    int choice;                                    // Variable to store user's menu choice
    
    printf("\n╔════════════════════════════════════════╗\n");  // Display top border of title
    printf("║    BANKER'S ALGORITHM SIMULATOR        ║\n");    // Display program title
    printf("║    Deadlock Avoidance System           ║\n");    // Display subtitle
    printf("╚════════════════════════════════════════╝\n");    // Display bottom border of title
    
    while (1) {                                    // Infinite loop for menu system (exit with option 6)
        printf("\n========================================\n");  // Display menu separator
        printf("               MAIN MENU\n");       // Display menu title
        printf("========================================\n");  // Display menu separator
        printf("1. Enter data manually\n");         // Option 1: Manual data entry
        printf("2. Use example data\n");            // Option 2: Load predefined example data
        printf("3. Display current state\n");       // Option 3: Show all matrices and available resources
        printf("4. Check if system is in safe state\n");  // Option 4: Run safety algorithm
        printf("5. Request resources\n");           // Option 5: Process a resource request
        printf("6. Exit\n");                        // Option 6: Exit program
        printf("========================================\n");  // Display menu separator
        printf("Enter your choice: ");              // Prompt for user choice
        scanf("%d", &choice);                      // Read user's menu choice
        
        switch (choice) {                          // Check which option user selected
            case 1:                                // If user chose option 1
                inputData();                       // Call function to input data manually
                break;                             // Exit switch statement
                
            case 2:                                // If user chose option 2
                useExampleData();                  // Call function to load example data
                break;                             // Exit switch statement
                
            case 3:                                // If user chose option 3
                if (n == 0) {                      // Check if data has been entered (n initialized to 0)
                    printf("\nPlease enter data first (option 1 or 2).\n");  // Display error if no data
                } else {                           // If data exists
                    displayState();                // Call function to display current system state
                }
                break;                             // Exit switch statement
                
            case 4:                                // If user chose option 4
                if (n == 0) {                      // Check if data has been entered
                    printf("\nPlease enter data first (option 1 or 2).\n");  // Display error if no data
                } else {                           // If data exists
                    isSafe();                      // Call function to check if system is safe
                }
                break;                             // Exit switch statement
                
            case 5:                                // If user chose option 5
                if (n == 0) {                      // Check if data has been entered
                    printf("\nPlease enter data first (option 1 or 2).\n");  // Display error if no data
                } else {                           // If data exists
                    requestResources();            // Call function to process resource request
                }
                break;                             // Exit switch statement
                
            case 6:                                // If user chose option 6
                printf("\nExiting program. Thank you!\n");  // Display exit message
                exit(0);                           // Exit program with status code 0 (success)
                
            default:                               // If user entered invalid option
                printf("\nInvalid choice! Please try again.\n");  // Display error message
        }
    }
    
    return 0;                                      // Return 0 to indicate successful execution (unreachable due to infinite loop)
}
