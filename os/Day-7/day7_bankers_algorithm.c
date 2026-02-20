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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n; // Number of processes
int m; // Number of resource types

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to calculate the Need matrix
void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if system is in safe state
bool isSafe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int count = 0;
    
    // Initialize work with available resources
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    
    printf("\n--- Safety Algorithm Execution ---\n");
    
    // Find a safe sequence
    while (count < n) {
        bool found = false;
        
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                // Check if process i can be allocated resources
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                
                if (canAllocate) {
                    // Allocate resources to process i
                    printf("Process P%d can be allocated. ", i);
                    printf("Work: [");
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                        printf("%d", work[j]);
                        if (j < m - 1) printf(", ");
                    }
                    printf("]\n");
                    
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        
        if (!found) {
            printf("\nSystem is in UNSAFE state! Deadlock may occur.\n");
            return false;
        }
    }
    
    printf("\nSystem is in SAFE state!\n");
    printf("Safe Sequence: < ");
    for (int i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);
        if (i < n - 1) printf(", ");
    }
    printf(" >\n");
    
    return true;
}

// Function to request resources
void requestResources() {
    int process;
    int request[MAX_RESOURCES];
    
    printf("\nEnter process number (0 to %d): ", n - 1);
    scanf("%d", &process);
    
    if (process < 0 || process >= n) {
        printf("Invalid process number!\n");
        return;
    }
    
    printf("Enter resource request for P%d:\n", process);
    for (int i = 0; i < m; i++) {
        printf("  Resource R%d: ", i);
        scanf("%d", &request[i]);
    }
    
    // Check if request is less than or equal to need
    printf("\n--- Checking Request Validity ---\n");
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process P%d has exceeded its maximum claim!\n", process);
            printf("Requested R%d: %d, but Need: %d\n", i, request[i], need[process][i]);
            return;
        }
    }
    
    // Check if request is less than or equal to available
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            printf("Error: Resources not available!\n");
            printf("Requested R%d: %d, but Available: %d\n", i, request[i], available[i]);
            printf("Process P%d must wait.\n", process);
            return;
        }
    }
    
    // Try allocating resources temporarily
    printf("\nTrying to allocate resources temporarily...\n");
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    
    // Check if system is in safe state
    if (isSafe()) {
        printf("\nRequest GRANTED! Resources allocated to P%d.\n", process);
    } else {
        // Rollback the allocation
        printf("\nRequest DENIED! Rolling back allocation.\n");
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Process P%d must wait to avoid deadlock.\n", process);
    }
}

// Function to display current state
void displayState() {
    printf("\n========================================\n");
    printf("         CURRENT SYSTEM STATE\n");
    printf("========================================\n");
    
    printf("\nAllocation Matrix:\n");
    printf("Process  ");
    for (int i = 0; i < m; i++) printf("R%d  ", i);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("P%d       ", i);
        for (int j = 0; j < m; j++) {
            printf("%2d  ", allocation[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMax Matrix:\n");
    printf("Process  ");
    for (int i = 0; i < m; i++) printf("R%d  ", i);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("P%d       ", i);
        for (int j = 0; j < m; j++) {
            printf("%2d  ", max[i][j]);
        }
        printf("\n");
    }
    
    printf("\nNeed Matrix:\n");
    printf("Process  ");
    for (int i = 0; i < m; i++) printf("R%d  ", i);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("P%d       ", i);
        for (int j = 0; j < m; j++) {
            printf("%2d  ", need[i][j]);
        }
        printf("\n");
    }
    
    printf("\nAvailable Resources: ");
    for (int i = 0; i < m; i++) {
        printf("R%d=%d  ", i, available[i]);
    }
    printf("\n");
}

// Function to input data
void inputData() {
    printf("\n--- Enter System Information ---\n");
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    
    printf("\n--- Enter Allocation Matrix ---\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d allocation:\n", i);
        for (int j = 0; j < m; j++) {
            printf("  Resource R%d: ", j);
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("\n--- Enter Max Matrix ---\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d maximum need:\n", i);
        for (int j = 0; j < m; j++) {
            printf("  Resource R%d: ", j);
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("\n--- Enter Available Resources ---\n");
    for (int i = 0; i < m; i++) {
        printf("Resource R%d: ", i);
        scanf("%d", &available[i]);
    }
    
    calculateNeed();
    printf("\nData entered successfully!\n");
}

// Function to use example data
void useExampleData() {
    n = 5; // 5 processes
    m = 3; // 3 resource types
    
    // Allocation Matrix
    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    
    // Max Matrix
    int maximum[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    
    // Available Resources
    int avail[3] = {3, 3, 2};
    
    // Copy data
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            allocation[i][j] = alloc[i][j];
            max[i][j] = maximum[i][j];
        }
    }
    
    for (int i = 0; i < m; i++) {
        available[i] = avail[i];
    }
    
    calculateNeed();
    printf("\nExample data loaded successfully!\n");
}

int main() {
    int choice;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║    BANKER'S ALGORITHM SIMULATOR        ║\n");
    printf("║    Deadlock Avoidance System           ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    while (1) {
        printf("\n========================================\n");
        printf("               MAIN MENU\n");
        printf("========================================\n");
        printf("1. Enter data manually\n");
        printf("2. Use example data\n");
        printf("3. Display current state\n");
        printf("4. Check if system is in safe state\n");
        printf("5. Request resources\n");
        printf("6. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                inputData();
                break;
                
            case 2:
                useExampleData();
                break;
                
            case 3:
                if (n == 0) {
                    printf("\nPlease enter data first (option 1 or 2).\n");
                } else {
                    displayState();
                }
                break;
                
            case 4:
                if (n == 0) {
                    printf("\nPlease enter data first (option 1 or 2).\n");
                } else {
                    isSafe();
                }
                break;
                
            case 5:
                if (n == 0) {
                    printf("\nPlease enter data first (option 1 or 2).\n");
                } else {
                    requestResources();
                }
                break;
                
            case 6:
                printf("\nExiting program. Thank you!\n");
                exit(0);
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
