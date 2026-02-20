/*
 * Day 10: Disk Scheduling Algorithms Simulation
 * 
 * This program simulates three disk scheduling algorithms:
 * a. FCFS (First Come First Serve) - Service requests in order of arrival
 * b. SCAN - Move in one direction servicing requests, then reverse
 * c. C-SCAN (Circular SCAN) - Move in one direction, then jump back and continue
 * 
 * The program calculates total head movement and average seek time.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 50

// Function to display the sequence of requests serviced
void displaySequence(int sequence[], int count, int totalMovement) {
    printf("\nDisk Head Movement Sequence:\n");
    for (int i = 0; i < count; i++) {
        printf("%d", sequence[i]);
        if (i < count - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
    printf("Total Head Movement: %d cylinders\n", totalMovement);
    printf("Average Seek Time: %.2f cylinders\n", (float)totalMovement / (count - 1));
}

// Function to sort requests in ascending order
void sortRequests(int requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

// FCFS Disk Scheduling Algorithm
void fcfs(int requests[], int numRequests, int initialHead) {
    int sequence[MAX_REQUESTS + 1];
    int totalMovement = 0;
    int currentHead = initialHead;
    
    printf("\n========================================\n");
    printf("    FCFS DISK SCHEDULING SIMULATION\n");
    printf("========================================\n");
    printf("Initial Head Position: %d\n", initialHead);
    printf("========================================\n");
    
    sequence[0] = initialHead;
    
    printf("\nRequest Queue: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");
    
    printf("\n%-10s %-15s %-15s\n", "Request", "Head Move", "Total Move");
    printf("----------------------------------------------\n");
    
    for (int i = 0; i < numRequests; i++) {
        int movement = abs(requests[i] - currentHead);
        totalMovement += movement;
        
        printf("%-10d %-15d %-15d\n", requests[i], movement, totalMovement);
        
        sequence[i + 1] = requests[i];
        currentHead = requests[i];
    }
    
    printf("\n========================================\n");
    displaySequence(sequence, numRequests + 1, totalMovement);
    printf("========================================\n");
}

// SCAN Disk Scheduling Algorithm (Elevator Algorithm)
void scan(int requests[], int numRequests, int initialHead, int diskSize, char direction) {
    int sequence[MAX_REQUESTS + 3];
    int totalMovement = 0;
    int seqIndex = 0;
    
    printf("\n========================================\n");
    printf("    SCAN DISK SCHEDULING SIMULATION\n");
    printf("========================================\n");
    printf("Initial Head Position: %d\n", initialHead);
    printf("Disk Size: 0 to %d\n", diskSize - 1);
    printf("Initial Direction: %s\n", direction == 'r' ? "Right (Increasing)" : "Left (Decreasing)");
    printf("========================================\n");
    
    // Create a copy of requests and add head position
    int allPositions[MAX_REQUESTS + 1];
    for (int i = 0; i < numRequests; i++) {
        allPositions[i] = requests[i];
    }
    
    // Sort all positions
    sortRequests(allPositions, numRequests);
    
    printf("\nRequest Queue (sorted): ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", allPositions[i]);
    }
    printf("\n");
    
    // Separate requests into left and right of head
    int left[MAX_REQUESTS], right[MAX_REQUESTS];
    int leftCount = 0, rightCount = 0;
    
    for (int i = 0; i < numRequests; i++) {
        if (allPositions[i] < initialHead) {
            left[leftCount++] = allPositions[i];
        } else {
            right[rightCount++] = allPositions[i];
        }
    }
    
    sequence[seqIndex++] = initialHead;
    
    if (direction == 'r') {
        // Move right first
        for (int i = 0; i < rightCount; i++) {
            totalMovement += abs(right[i] - (seqIndex == 1 ? initialHead : sequence[seqIndex - 1]));
            sequence[seqIndex++] = right[i];
        }
        
        // Move to end if needed
        if (rightCount > 0) {
            totalMovement += abs((diskSize - 1) - sequence[seqIndex - 1]);
            sequence[seqIndex++] = diskSize - 1;
        }
        
        // Move left
        for (int i = leftCount - 1; i >= 0; i--) {
            totalMovement += abs(left[i] - sequence[seqIndex - 1]);
            sequence[seqIndex++] = left[i];
        }
    } else {
        // Move left first
        for (int i = leftCount - 1; i >= 0; i--) {
            totalMovement += abs(left[i] - (seqIndex == 1 ? initialHead : sequence[seqIndex - 1]));
            sequence[seqIndex++] = left[i];
        }
        
        // Move to beginning if needed
        if (leftCount > 0) {
            totalMovement += abs(0 - sequence[seqIndex - 1]);
            sequence[seqIndex++] = 0;
        }
        
        // Move right
        for (int i = 0; i < rightCount; i++) {
            totalMovement += abs(right[i] - sequence[seqIndex - 1]);
            sequence[seqIndex++] = right[i];
        }
    }
    
    printf("\n========================================\n");
    displaySequence(sequence, seqIndex, totalMovement);
    printf("========================================\n");
}

// C-SCAN Disk Scheduling Algorithm (Circular SCAN)
void cscan(int requests[], int numRequests, int initialHead, int diskSize) {
    int sequence[MAX_REQUESTS + 4];
    int totalMovement = 0;
    int seqIndex = 0;
    
    printf("\n========================================\n");
    printf("   C-SCAN DISK SCHEDULING SIMULATION\n");
    printf("========================================\n");
    printf("Initial Head Position: %d\n", initialHead);
    printf("Disk Size: 0 to %d\n", diskSize - 1);
    printf("Direction: Right (Circular)\n");
    printf("========================================\n");
    
    // Create a copy of requests
    int allPositions[MAX_REQUESTS];
    for (int i = 0; i < numRequests; i++) {
        allPositions[i] = requests[i];
    }
    
    // Sort all positions
    sortRequests(allPositions, numRequests);
    
    printf("\nRequest Queue (sorted): ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", allPositions[i]);
    }
    printf("\n");
    
    // Separate requests into left and right of head
    int left[MAX_REQUESTS], right[MAX_REQUESTS];
    int leftCount = 0, rightCount = 0;
    
    for (int i = 0; i < numRequests; i++) {
        if (allPositions[i] < initialHead) {
            left[leftCount++] = allPositions[i];
        } else {
            right[rightCount++] = allPositions[i];
        }
    }
    
    sequence[seqIndex++] = initialHead;
    
    // Move right first
    for (int i = 0; i < rightCount; i++) {
        totalMovement += abs(right[i] - (seqIndex == 1 ? initialHead : sequence[seqIndex - 1]));
        sequence[seqIndex++] = right[i];
    }
    
    // Move to end
    if (rightCount > 0 || leftCount > 0) {
        totalMovement += abs((diskSize - 1) - sequence[seqIndex - 1]);
        sequence[seqIndex++] = diskSize - 1;
        
        // Jump to beginning
        totalMovement += (diskSize - 1); // Jump doesn't count as movement in some implementations
        sequence[seqIndex++] = 0;
    }
    
    // Service remaining requests from the left
    for (int i = 0; i < leftCount; i++) {
        totalMovement += abs(left[i] - sequence[seqIndex - 1]);
        sequence[seqIndex++] = left[i];
    }
    
    printf("\n========================================\n");
    displaySequence(sequence, seqIndex, totalMovement);
    printf("Note: Jump from %d to 0 is included in movement\n", diskSize - 1);
    printf("========================================\n");
}

// Function to input disk requests
int inputRequests(int requests[], int *initialHead, int *diskSize) {
    int numRequests;
    
    printf("\n--- Enter Disk Request Information ---\n");
    
    printf("Enter total disk size (cylinders): ");
    scanf("%d", diskSize);
    
    printf("Enter initial head position: ");
    scanf("%d", initialHead);
    
    printf("Enter number of disk requests: ");
    scanf("%d", &numRequests);
    
    if (numRequests > MAX_REQUESTS) {
        printf("Error: Maximum requests allowed is %d\n", MAX_REQUESTS);
        return 0;
    }
    
    printf("Enter disk request queue:\n");
    for (int i = 0; i < numRequests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }
    
    return numRequests;
}

// Function to use example disk requests
int useExampleRequests(int requests[], int *initialHead, int *diskSize) {
    // Example: Disk size = 200, Initial head = 50
    // Requests: 82, 170, 43, 140, 24, 16, 190
    int example[] = {82, 170, 43, 140, 24, 16, 190};
    int numRequests = 7;
    
    *diskSize = 200;
    *initialHead = 50;
    
    for (int i = 0; i < numRequests; i++) {
        requests[i] = example[i];
    }
    
    printf("\nExample Disk Request Queue Loaded:\n");
    printf("Disk Size: %d cylinders (0 to %d)\n", *diskSize, *diskSize - 1);
    printf("Initial Head Position: %d\n", *initialHead);
    printf("Requests: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");
    
    return numRequests;
}

int main() {
    int choice, numRequests = 0, initialHead = 0, diskSize = 0;
    int requests[MAX_REQUESTS];
    char direction;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║   DISK SCHEDULING SIMULATOR            ║\n");
    printf("║   FCFS, SCAN, C-SCAN Algorithms        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    while (1) {
        printf("\n========================================\n");
        printf("             MAIN MENU\n");
        printf("========================================\n");
        printf("1. Enter disk request queue\n");
        printf("2. Use example disk request queue\n");
        printf("3. Simulate FCFS algorithm\n");
        printf("4. Simulate SCAN algorithm\n");
        printf("5. Simulate C-SCAN algorithm\n");
        printf("6. Compare all algorithms\n");
        printf("7. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                numRequests = inputRequests(requests, &initialHead, &diskSize);
                break;
                
            case 2:
                numRequests = useExampleRequests(requests, &initialHead, &diskSize);
                break;
                
            case 3:
                if (numRequests == 0) {
                    printf("\nPlease enter disk request queue first!\n");
                    break;
                }
                fcfs(requests, numRequests, initialHead);
                break;
                
            case 4:
                if (numRequests == 0) {
                    printf("\nPlease enter disk request queue first!\n");
                    break;
                }
                printf("\nEnter initial direction (l=left, r=right): ");
                scanf(" %c", &direction);
                
                if (direction != 'l' && direction != 'r') {
                    printf("Invalid direction! Using 'r' (right) as default.\n");
                    direction = 'r';
                }
                
                scan(requests, numRequests, initialHead, diskSize, direction);
                break;
                
            case 5:
                if (numRequests == 0) {
                    printf("\nPlease enter disk request queue first!\n");
                    break;
                }
                cscan(requests, numRequests, initialHead, diskSize);
                break;
                
            case 6:
                if (numRequests == 0) {
                    printf("\nPlease enter disk request queue first!\n");
                    break;
                }
                
                printf("\n╔════════════════════════════════════════╗\n");
                printf("║      ALGORITHM COMPARISON              ║\n");
                printf("╚════════════════════════════════════════╝\n");
                
                // FCFS
                fcfs(requests, numRequests, initialHead);
                
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                
                // SCAN (right direction)
                scan(requests, numRequests, initialHead, diskSize, 'r');
                
                printf("\nPress Enter to continue...");
                getchar();
                
                // C-SCAN
                cscan(requests, numRequests, initialHead, diskSize);
                
                printf("\n========================================\n");
                printf("Compare the total head movements above\n");
                printf("to determine the most efficient algorithm.\n");
                printf("========================================\n");
                break;
                
            case 7:
                printf("\nExiting program. Thank you!\n");
                exit(0);
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
