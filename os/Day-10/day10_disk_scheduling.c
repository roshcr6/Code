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

#include <stdio.h>      // For input/output functions like printf, scanf
#include <stdlib.h>     // For abs() function and exit()
#include <stdbool.h>    // For bool, true, false data types

#define MAX_REQUESTS 50 // Maximum number of disk requests that can be handled

// Function to display the sequence of disk head movements
void displaySequence(int sequence[], int count, int totalMovement) {  // Takes sequence array, count, total movement
    printf("\nDisk Head Movement Sequence:\n");  // Display sequence header
    for (int i = 0; i < count; i++) {    // Loop through all positions in sequence
        printf("%d", sequence[i]);       // Display cylinder number
        if (i < count - 1) {             // If not the last element
            printf(" -> ");              // Add arrow separator
        }
    }
    printf("\n");                        // New line after sequence
    printf("Total Head Movement: %d cylinders\n", totalMovement);  // Display total movement
    printf("Average Seek Time: %.2f cylinders\n", (float)totalMovement / (count - 1));  // Calculate and display average
}

// Function to sort disk requests in ascending order (Bubble Sort)
void sortRequests(int requests[], int n) {  // Takes array and size
    for (int i = 0; i < n - 1; i++) {    // Outer loop for passes
        for (int j = 0; j < n - i - 1; j++) {  // Inner loop for comparisons
            if (requests[j] > requests[j + 1]) {  // If current element is greater than next
                int temp = requests[j];   // Swap elements using temporary variable
                requests[j] = requests[j + 1];  // Move smaller element forward
                requests[j + 1] = temp;   // Move larger element backward
            }
        }
    }
}

// FCFS Disk Scheduling Algorithm - Service requests in the order they arrive
void fcfs(int requests[], int numRequests, int initialHead) {  // Takes request array, count, initial head position
    int sequence[MAX_REQUESTS + 1];      // Array to store sequence of head positions (+1 for initial position)
    int totalMovement = 0;               // Variable to accumulate total head movement
    int currentHead = initialHead;       // Variable to track current head position
    
    printf("\n========================================\n");  // Display header separator
    printf("    FCFS DISK SCHEDULING SIMULATION\n");       // Display algorithm name
    printf("========================================\n");    // Display separator
    printf("Initial Head Position: %d\n", initialHead);    // Display starting position
    printf("========================================\n");    // Display separator
    
    sequence[0] = initialHead;           // Store initial head position in sequence
    
    printf("\nRequest Queue: ");         // Display request queue header
    for (int i = 0; i < numRequests; i++) {  // Loop through all requests
        printf("%d ", requests[i]);      // Display each request
    }
    printf("\n");                        // New line after queue
    
    printf("\n%-10s %-15s %-15s\n", "Request", "Head Move", "Total Move");  // Display column headers
    printf("----------------------------------------------\n");  // Display column separator
    
    for (int i = 0; i < numRequests; i++) {  // Loop through each request in order
        int movement = abs(requests[i] - currentHead);  // Calculate distance moved (absolute value)
        totalMovement += movement;       // Add to total movement
        
        printf("%-10d %-15d %-15d\n", requests[i], movement, totalMovement);  // Display request details
        
        sequence[i + 1] = requests[i];   // Store request in sequence array
        currentHead = requests[i];       // Update current head position
    }
    
    printf("\n========================================\n");  // Display results separator
    displaySequence(sequence, numRequests + 1, totalMovement);  // Call function to display sequence
    printf("========================================\n");    // Display end separator
}

// SCAN Disk Scheduling Algorithm (Elevator Algorithm) - Move in one direction, then reverse
void scan(int requests[], int numRequests, int initialHead, int diskSize, char direction) {  // Takes requests, count, head, disk size, direction
    int sequence[MAX_REQUESTS + 3];      // Array to store sequence (+3 for initial, end points)
    int totalMovement = 0;               // Variable to accumulate total head movement
    int seqIndex = 0;                    // Index to track position in sequence array
    
    printf("\n========================================\n");  // Display header separator
    printf("    SCAN DISK SCHEDULING SIMULATION\n");       // Display algorithm name
    printf("========================================\n");    // Display separator
    printf("Initial Head Position: %d\n", initialHead);    // Display starting position
    printf("Disk Size: 0 to %d\n", diskSize - 1);          // Display disk range
    printf("Initial Direction: %s\n", direction == 'r' ? "Right (Increasing)" : "Left (Decreasing)");  // Display direction
    printf("========================================\n");    // Display separator
    
    // Create a copy of requests array
    int allPositions[MAX_REQUESTS + 1];  // Array to hold copy of all requests
    for (int i = 0; i < numRequests; i++) {  // Loop through all requests
        allPositions[i] = requests[i];   // Copy each request
    }
    
    // Sort all positions in ascending order
    sortRequests(allPositions, numRequests);  // Call sort function
    
    printf("\nRequest Queue (sorted): ");  // Display sorted queue header
    for (int i = 0; i < numRequests; i++) {  // Loop through sorted requests
        printf("%d ", allPositions[i]);  // Display each request
    }
    printf("\n");                        // New line after queue
    
    // Separate requests into two arrays: left (< head) and right (>= head)
    int left[MAX_REQUESTS], right[MAX_REQUESTS];  // Arrays for left and right requests
    int leftCount = 0, rightCount = 0;   // Counters for each side
    
    for (int i = 0; i < numRequests; i++) {  // Loop through all sorted requests
        if (allPositions[i] < initialHead) {  // If request is to the left of head
            left[leftCount++] = allPositions[i];  // Add to left array and increment counter
        } else {                         // If request is to the right of or at head
            right[rightCount++] = allPositions[i];  // Add to right array and increment counter
        }
    }
    
    sequence[seqIndex++] = initialHead;  // Store initial head position in sequence
    
    if (direction == 'r') {              // If moving right (increasing cylinder numbers)
        // Move right first - service all requests on the right
        for (int i = 0; i < rightCount; i++) {  // Loop through right requests
            totalMovement += abs(right[i] - (seqIndex == 1 ? initialHead : sequence[seqIndex - 1]));  // Calculate movement
            sequence[seqIndex++] = right[i];  // Add to sequence
        }
        
        // Move to end of disk if there were right requests
        if (rightCount > 0) {            // If we serviced right requests
            totalMovement += abs((diskSize - 1) - sequence[seqIndex - 1]);  // Move to disk end
            sequence[seqIndex++] = diskSize - 1;  // Add disk end to sequence
        }
        
        // Reverse direction and move left - service all requests on the left
        for (int i = leftCount - 1; i >= 0; i--) {  // Loop through left requests (reverse order)
            totalMovement += abs(left[i] - sequence[seqIndex - 1]);  // Calculate movement
            sequence[seqIndex++] = left[i];  // Add to sequence
        }
    } else {                             // If moving left (decreasing cylinder numbers)
        // Move left first - service all requests on the left
        for (int i = leftCount - 1; i >= 0; i--) {  // Loop through left requests (reverse order)
            totalMovement += abs(left[i] - (seqIndex == 1 ? initialHead : sequence[seqIndex - 1]));  // Calculate movement
            sequence[seqIndex++] = left[i];  // Add to sequence
        }
        
        // Move to beginning of disk if there were left requests
        if (leftCount > 0) {             // If we serviced left requests
            totalMovement += abs(0 - sequence[seqIndex - 1]);  // Move to disk beginning
            sequence[seqIndex++] = 0;    // Add disk beginning to sequence
        }
        
        // Reverse direction and move right - service all requests on the right
        for (int i = 0; i < rightCount; i++) {  // Loop through right requests
            totalMovement += abs(right[i] - sequence[seqIndex - 1]);  // Calculate movement
            sequence[seqIndex++] = right[i];  // Add to sequence
        }
    }
    
    printf("\n========================================\n");  // Display results separator
    displaySequence(sequence, seqIndex, totalMovement);  // Call function to display sequence
    printf("========================================\n");    // Display end separator
}

// C-SCAN Disk Scheduling Algorithm (Circular SCAN) - Move in one direction, jump back, continue
void cscan(int requests[], int numRequests, int initialHead, int diskSize) {  // Takes requests, count, head, disk size
    int sequence[MAX_REQUESTS + 4];      // Array to store sequence (+4 for initial, end, beginning points)
    int totalMovement = 0;               // Variable to accumulate total head movement
    int seqIndex = 0;                    // Index to track position in sequence array
    
    printf("\n========================================\n");  // Display header separator
    printf("   C-SCAN DISK SCHEDULING SIMULATION\n");       // Display algorithm name
    printf("========================================\n");    // Display separator
    printf("Initial Head Position: %d\n", initialHead);    // Display starting position
    printf("Disk Size: 0 to %d\n", diskSize - 1);          // Display disk range
    printf("Direction: Right (Circular)\n");               // Display direction (always right for C-SCAN)
    printf("========================================\n");    // Display separator
    
    // Create a copy of requests array
    int allPositions[MAX_REQUESTS];      // Array to hold copy of all requests
    for (int i = 0; i < numRequests; i++) {  // Loop through all requests
        allPositions[i] = requests[i];   // Copy each request
    }
    
    // Sort all positions in ascending order
    sortRequests(allPositions, numRequests);  // Call sort function
    
    printf("\nRequest Queue (sorted): ");  // Display sorted queue header
    for (int i = 0; i < numRequests; i++) {  // Loop through sorted requests
        printf("%d ", allPositions[i]);  // Display each request
    }
    printf("\n");                        // New line after queue
    
    // Separate requests into two arrays: left (< head) and right (>= head)
    int left[MAX_REQUESTS], right[MAX_REQUESTS];  // Arrays for left and right requests
    int leftCount = 0, rightCount = 0;   // Counters for each side
    
    for (int i = 0; i < numRequests; i++) {  // Loop through all sorted requests
        if (allPositions[i] < initialHead) {  // If request is to the left of head
            left[leftCount++] = allPositions[i];  // Add to left array and increment counter
        } else {                         // If request is to the right of or at head
            right[rightCount++] = allPositions[i];  // Add to right array and increment counter
        }
    }
    
    sequence[seqIndex++] = initialHead;  // Store initial head position in sequence
    
    // Move right first - service all requests on the right
    for (int i = 0; i < rightCount; i++) {  // Loop through right requests
        totalMovement += abs(right[i] - (seqIndex == 1 ? initialHead : sequence[seqIndex - 1]));  // Calculate movement
        sequence[seqIndex++] = right[i]; // Add to sequence
    }
    
    // Move to end of disk, then jump to beginning (circular behavior)
    if (rightCount > 0 || leftCount > 0) {  // If there are any requests
        totalMovement += abs((diskSize - 1) - sequence[seqIndex - 1]);  // Move to disk end
        sequence[seqIndex++] = diskSize - 1;  // Add disk end to sequence
        
        // Jump to beginning of disk (circular jump)
        totalMovement += (diskSize - 1); // Count the jump distance in total movement
        sequence[seqIndex++] = 0;        // Add disk beginning to sequence
    }
    
    // Service remaining requests from the left (starting from beginning)
    for (int i = 0; i < leftCount; i++) {  // Loop through left requests (forward order)
        totalMovement += abs(left[i] - sequence[seqIndex - 1]);  // Calculate movement
        sequence[seqIndex++] = left[i];  // Add to sequence
    }
    
    printf("\n========================================\n");  // Display results separator
    displaySequence(sequence, seqIndex, totalMovement);  // Call function to display sequence
    printf("Note: Jump from %d to 0 is included in movement\n", diskSize - 1);  // Note about circular jump
    printf("========================================\n");    // Display end separator
}

// Function to get disk request information from user input
int inputRequests(int requests[], int *initialHead, int *diskSize) {  // Takes arrays for requests, head, size (pointers for output)
    int numRequests;                     // Variable to store count of requests
    
    printf("\n--- Enter Disk Request Information ---\n");  // Display input section header
    
    printf("Enter total disk size (cylinders): ");  // Prompt for disk size
    scanf("%d", diskSize);               // Read disk size (using pointer to modify original variable)
    
    printf("Enter initial head position: ");  // Prompt for starting head position
    scanf("%d", initialHead);            // Read initial head (using pointer)
    
    printf("Enter number of disk requests: ");  // Prompt for number of requests
    scanf("%d", &numRequests);           // Read number of requests
    
    if (numRequests > MAX_REQUESTS) {    // Check if exceeds maximum limit
        printf("Error: Maximum requests allowed is %d\n", MAX_REQUESTS);  // Display error message
        return 0;                        // Return 0 to indicate error
    }
    
    printf("Enter disk request queue:\n");  // Prompt for request queue
    for (int i = 0; i < numRequests; i++) {  // Loop to input each request
        printf("Request %d: ", i + 1);   // Prompt for specific request (1-based display)
        scanf("%d", &requests[i]);       // Read cylinder number into array
    }
    
    return numRequests;                  // Return count of requests entered
}

// Function to load predefined example disk requests for quick testing
int useExampleRequests(int requests[], int *initialHead, int *diskSize) {  // Takes arrays (pointers for output)
    // Predefined example: disk size 200, initial head at 50
    // Request queue: 82, 170, 43, 140, 24, 16, 190
    int example[] = {82, 170, 43, 140, 24, 16, 190};  // Example request array
    int numRequests = 7;                 // Number of requests in example
    
    *diskSize = 200;                     // Set disk size (using pointer)
    *initialHead = 50;                   // Set initial head position (using pointer)
    
    for (int i = 0; i < numRequests; i++) {  // Loop to copy example data
        requests[i] = example[i];        // Copy each request to main array
    }
    
    printf("\nExample Disk Request Queue Loaded:\n");  // Display confirmation header
    printf("Disk Size: %d cylinders (0 to %d)\n", *diskSize, *diskSize - 1);  // Display disk range
    printf("Initial Head Position: %d\n", *initialHead);  // Display starting position
    printf("Requests: ");                // Display requests label
    for (int i = 0; i < numRequests; i++) {  // Loop through all requests
        printf("%d ", requests[i]);      // Display each request
    }
    printf("\n");                        // New line at end
    
    return numRequests;                  // Return count of requests loaded
}

int main() {                             // Main function - program execution starts here
    int choice, numRequests = 0, initialHead = 0, diskSize = 0;  // Variables for menu, requests, head, disk size
    int requests[MAX_REQUESTS];          // Array to store disk request queue
    char direction;                      // Variable to store direction for SCAN algorithm
    
    printf("\n╔════════════════════════════════════════╗\n");  // Display top border
    printf("║   DISK SCHEDULING SIMULATOR            ║\n");    // Display program title
    printf("║   FCFS, SCAN, C-SCAN Algorithms        ║\n");    // Display subtitle
    printf("╚════════════════════════════════════════╝\n");    // Display bottom border
    
    while (1) {                          // Infinite loop for menu system (until exit)
        printf("\n========================================\n");  // Display menu separator
        printf("             MAIN MENU\n");                     // Display menu title
        printf("========================================\n");    // Display menu separator
        printf("1. Enter disk request queue\n");                // Option 1: Manual input
        printf("2. Use example disk request queue\n");          // Option 2: Load example
        printf("3. Simulate FCFS algorithm\n");                 // Option 3: Run FCFS only
        printf("4. Simulate SCAN algorithm\n");                 // Option 4: Run SCAN only
        printf("5. Simulate C-SCAN algorithm\n");               // Option 5: Run C-SCAN only
        printf("6. Compare all algorithms\n");                  // Option 6: Run all and compare
        printf("7. Exit\n");                                    // Option 7: Exit program
        printf("========================================\n");    // Display menu separator
        printf("Enter your choice: ");                          // Prompt for choice
        scanf("%d", &choice);            // Read user's menu choice
        
        switch (choice) {                // Check which option user selected
            case 1:                      // If user chose to enter requests manually
                numRequests = inputRequests(requests, &initialHead, &diskSize);  // Call input function
                break;                   // Exit switch statement
                
            case 2:                      // If user chose to use example
                numRequests = useExampleRequests(requests, &initialHead, &diskSize);  // Call example function
                break;                   // Exit switch statement
                
            case 3:                      // If user chose FCFS simulation
                if (numRequests == 0) {  // Check if request queue has been entered
                    printf("\nPlease enter disk request queue first!\n");  // Display error
                    break;               // Exit case
                }
                fcfs(requests, numRequests, initialHead);  // Call FCFS algorithm
                break;                   // Exit switch statement
                
            case 4:                      // If user chose SCAN simulation
                if (numRequests == 0) {  // Check if request queue has been entered
                    printf("\nPlease enter disk request queue first!\n");  // Display error
                    break;               // Exit case
                }
                printf("\nEnter initial direction (l=left, r=right): ");  // Prompt for direction
                scanf(" %c", &direction);  // Read direction (space before %c to skip whitespace)
                
                if (direction != 'l' && direction != 'r') {  // Validate direction input
                    printf("Invalid direction! Using 'r' (right) as default.\n");  // Display warning
                    direction = 'r';     // Set default direction
                }
                
                scan(requests, numRequests, initialHead, diskSize, direction);  // Call SCAN algorithm
                break;                   // Exit switch statement
                
            case 5:                      // If user chose C-SCAN simulation
                if (numRequests == 0) {  // Check if request queue has been entered
                    printf("\nPlease enter disk request queue first!\n");  // Display error
                    break;               // Exit case
                }
                cscan(requests, numRequests, initialHead, diskSize);  // Call C-SCAN algorithm
                break;                   // Exit switch statement
                
            case 6:                      // If user chose to compare all algorithms
                if (numRequests == 0) {  // Check if request queue has been entered
                    printf("\nPlease enter disk request queue first!\n");  // Display error
                    break;               // Exit case
                }
                
                printf("\n╔════════════════════════════════════════╗\n");  // Display comparison header
                printf("║      ALGORITHM COMPARISON              ║\n");    // Display title
                printf("╚════════════════════════════════════════╝\n");    // Display bottom border
                
                // Run FCFS algorithm
                fcfs(requests, numRequests, initialHead);  // Call FCFS
                
                printf("\nPress Enter to continue...");  // Prompt to continue
                getchar();               // Clear input buffer
                getchar();               // Wait for Enter key
                
                // Run SCAN algorithm (right direction by default)
                scan(requests, numRequests, initialHead, diskSize, 'r');  // Call SCAN
                
                printf("\nPress Enter to continue...");  // Prompt to continue
                getchar();               // Wait for Enter key
                
                // Run C-SCAN algorithm
                cscan(requests, numRequests, initialHead, diskSize);  // Call C-SCAN
                
                printf("\n========================================\n");  // Display comparison footer
                printf("Compare the total head movements above\n");     // Display instruction
                printf("to determine the most efficient algorithm.\n"); // Continuation
                printf("========================================\n");    // Display separator
                break;                   // Exit switch statement
                
            case 7:                      // If user chose to exit
                printf("\nExiting program. Thank you!\n");  // Display exit message
                exit(0);                 // Terminate program with success code
                
            default:                     // If user entered invalid option
                printf("\nInvalid choice! Please try again.\n");  // Display error message
        }
    }
    
    return 0;                            // Return 0 to indicate successful execution (unreachable)
}
