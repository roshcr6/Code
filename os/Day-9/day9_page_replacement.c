/*
 * Day 9: Page Replacement Algorithms Simulation
 * 
 * This program simulates two page replacement algorithms:
 * a. FIFO (First In First Out) - Replace the oldest page
 * b. LRU (Least Recently Used) - Replace the page that hasn't been used for longest time
 * 
 * The program calculates page faults and hit ratio for performance evaluation.
 */

#include <stdio.h>      // For input/output functions like printf, scanf
#include <stdlib.h>     // For exit() function
#include <stdbool.h>    // For bool, true, false data types

#define MAX_PAGES 50    // Maximum number of pages in reference string
#define MAX_FRAMES 10   // Maximum number of frames in memory

// Function to check if a page is already present in frames (searching for page hit)
int searchPage(int page, int frames[], int numFrames) {  // Takes page number, frame array, and frame count
    for (int i = 0; i < numFrames; i++) {  // Loop through all frames
        if (frames[i] == page) {            // If page found in frame i
            return i;                       // Return position/index where found
        }
    }
    return -1;                              // Return -1 if page not found (page fault)
}

// Function to display current state of all frames in a formatted way
void displayFrames(int frames[], int numFrames) {  // Takes frame array and frame count
    printf("| ");                          // Print left border
    for (int i = 0; i < numFrames; i++) {  // Loop through all frames
        if (frames[i] == -1) {             // If frame is empty (-1 indicates empty)
            printf("  - ");                // Display dash for empty frame
        } else {                           // If frame contains a page
            printf(" %2d ", frames[i]);    // Display page number (right-aligned, 2 digits)
        }
    }
    printf("|");                           // Print right border
}

// FIFO Page Replacement Algorithm - Replace oldest page in memory
void fifo(int pages[], int numPages, int numFrames) {  // Takes page reference string, page count, frame count
    int frames[MAX_FRAMES];              // Array to store current pages in frames
    int pageFaults = 0;                  // Counter for page faults
    int pageHits = 0;                    // Counter for page hits
    int nextReplace = 0;                 // Index of next frame to replace (circular queue pointer)
    
    // Initialize all frames to -1 (indicating empty frames)
    for (int i = 0; i < numFrames; i++) {  // Loop through all frames
        frames[i] = -1;                  // Set frame to empty
    }
    
    printf("\n========================================\n");  // Display header separator
    printf("    FIFO PAGE REPLACEMENT SIMULATION\n");       // Display algorithm name
    printf("========================================\n");    // Display separator
    printf("Number of Frames: %d\n", numFrames);            // Display frame count
    printf("========================================\n");    // Display separator
    printf("Page | Frames               | Status\n");       // Display column headers
    printf("----------------------------------------\n");   // Display column separator
    
    for (int i = 0; i < numPages; i++) {  // Loop through each page in reference string
        int currentPage = pages[i];      // Get current page number
        printf(" %2d  ", currentPage);   // Display current page number
        
        // Check if page is already present in a frame (page hit check)
        int position = searchPage(currentPage, frames, numFrames);  // Search for page
        
        if (position != -1) {            // If page found in frames (page hit)
            displayFrames(frames, numFrames);  // Display current frame state
            printf(" HIT\n");            // Display "HIT" status
            pageHits++;                  // Increment hit counter
        } else {                         // If page not found (page fault)
            frames[nextReplace] = currentPage;  // Place page in next frame position
            displayFrames(frames, numFrames);   // Display updated frame state
            printf(" FAULT\n");          // Display "FAULT" status
            pageFaults++;                // Increment fault counter
            
            // Move to next frame in circular fashion (FIFO behavior)
            nextReplace = (nextReplace + 1) % numFrames;  // Wrap around using modulo
        }
    }
    
    printf("========================================\n");  // Display results separator
    printf("RESULTS:\n");                                 // Display results header
    printf("Total Page References: %d\n", numPages);     // Display total pages processed
    printf("Page Faults: %d\n", pageFaults);             // Display total page faults
    printf("Page Hits: %d\n", pageHits);                 // Display total page hits
    printf("Hit Ratio: %.2f%%\n", (pageHits * 100.0) / numPages);      // Calculate and display hit percentage
    printf("Fault Ratio: %.2f%%\n", (pageFaults * 100.0) / numPages);  // Calculate and display fault percentage
    printf("========================================\n");  // Display end separator
}

// LRU Page Replacement Algorithm - Replace least recently used page
void lru(int pages[], int numPages, int numFrames) {  // Takes page reference string, page count, frame count
    int frames[MAX_FRAMES];              // Array to store current pages in frames
    int lastUsed[MAX_FRAMES];            // Array to track when each frame was last accessed (timestamp)
    int pageFaults = 0;                  // Counter for page faults
    int pageHits = 0;                    // Counter for page hits
    int time = 0;                        // Time counter (increments with each page reference)
    
    // Initialize all frames to -1 (empty) and lastUsed to 0 (never used)
    for (int i = 0; i < numFrames; i++) {  // Loop through all frames
        frames[i] = -1;                  // Set frame to empty
        lastUsed[i] = 0;                 // Set last used time to 0
    }
    
    printf("\n========================================\n");  // Display header separator
    printf("    LRU PAGE REPLACEMENT SIMULATION\n");        // Display algorithm name
    printf("========================================\n");    // Display separator
    printf("Number of Frames: %d\n", numFrames);            // Display frame count
    printf("========================================\n");    // Display separator
    printf("Page | Frames               | Status\n");       // Display column headers
    printf("----------------------------------------\n");   // Display column separator
    
    for (int i = 0; i < numPages; i++) {  // Loop through each page in reference string
        int currentPage = pages[i];      // Get current page number
        printf(" %2d  ", currentPage);   // Display current page number
        time++;                          // Increment time counter for each page reference
        
        // Check if page is already present in a frame (page hit check)
        int position = searchPage(currentPage, frames, numFrames);  // Search for page
        
        if (position != -1) {            // If page found in frames (page hit)
            displayFrames(frames, numFrames);  // Display current frame state
            printf(" HIT\n");            // Display "HIT" status
            pageHits++;                  // Increment hit counter
            lastUsed[position] = time;   // Update last used time for this frame (important for LRU)
        } else {                         // If page not found (page fault)
            int replaceIndex = 0;        // Variable to store which frame to replace
            
            // First check if there's an empty frame available
            bool emptyFound = false;     // Flag to track if empty frame found
            for (int j = 0; j < numFrames; j++) {  // Loop through all frames
                if (frames[j] == -1) {   // If frame is empty
                    replaceIndex = j;    // Use this empty frame
                    emptyFound = true;   // Set flag that empty frame found
                    break;               // Exit loop (no need to search further)
                }
            }
            
            // If no empty frame found, find least recently used page to replace
            if (!emptyFound) {           // If all frames are full
                int minTime = lastUsed[0];  // Assume first frame is LRU (smallest time)
                replaceIndex = 0;        // Start with first frame as candidate
                
                for (int j = 1; j < numFrames; j++) {  // Loop through remaining frames
                    if (lastUsed[j] < minTime) {  // If this frame used earlier than current minimum
                        minTime = lastUsed[j];    // Update minimum time
                        replaceIndex = j;         // Update replacement candidate
                    }
                }
            }
            
            // Replace the page at selected index
            frames[replaceIndex] = currentPage;  // Put new page in selected frame
            lastUsed[replaceIndex] = time;       // Update last used time for this frame
            
            displayFrames(frames, numFrames);    // Display updated frame state
            printf(" FAULT\n");          // Display "FAULT" status
            pageFaults++;                // Increment fault counter
        }
    }
    
    printf("========================================\n");  // Display results separator
    printf("RESULTS:\n");                                 // Display results header
    printf("Total Page References: %d\n", numPages);     // Display total pages processed
    printf("Page Faults: %d\n", pageFaults);             // Display total page faults
    printf("Page Hits: %d\n", pageHits);                 // Display total page hits
    printf("Hit Ratio: %.2f%%\n", (pageHits * 100.0) / numPages);      // Calculate and display hit percentage
    printf("Fault Ratio: %.2f%%\n", (pageFaults * 100.0) / numPages);  // Calculate and display fault percentage
    printf("========================================\n");  // Display end separator
}
    printf("Page Faults: %d\n", pageFaults);
    printf("Page Hits: %d\n", pageHits);
    printf("Hit Ratio: %.2f%%\n", (pageHits * 100.0) / numPages);
    printf("Fault Ratio: %.2f%%\n", (pageFaults * 100.0) / numPages);
    printf("========================================\n");
}

// Function to get page reference string from user input
int inputPages(int pages[]) {           // Takes array to store pages, returns number of pages entered
    int numPages;                        // Variable to store count of pages
    
    printf("\n--- Enter Page Reference String ---\n");  // Display input section header
    printf("Enter number of page references: ");        // Prompt for count
    scanf("%d", &numPages);              // Read number of pages from user
    
    if (numPages > MAX_PAGES) {          // Check if exceeds maximum limit
        printf("Error: Maximum pages allowed is %d\n", MAX_PAGES);  // Display error message
        return 0;                        // Return 0 to indicate error
    }
    
    printf("Enter page reference string:\n");  // Prompt for page numbers
    for (int i = 0; i < numPages; i++) { // Loop to input each page
        printf("Page %d: ", i + 1);      // Prompt for specific page (1-based display)
        scanf("%d", &pages[i]);          // Read page number into array
    }
    
    printf("\nPage Reference String: ");  // Display confirmation header
    for (int i = 0; i < numPages; i++) { // Loop through all pages
        printf("%d ", pages[i]);         // Display each page number
    }
    printf("\n");                        // New line after displaying all pages
    
    return numPages;                     // Return count of pages entered
}

// Function to load predefined example page reference string for quick testing
int useExamplePages(int pages[]) {      // Takes array to store pages, returns number of pages
    // Predefined example page reference string (commonly used pattern)
    int example[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int numPages = 20;                   // Number of pages in example
    
    for (int i = 0; i < numPages; i++) { // Loop to copy example data
        pages[i] = example[i];           // Copy each page to main array
    }
    
    printf("\nExample Page Reference String Loaded:\n");  // Display confirmation
    printf("Pages: ");                   // Display label
    for (int i = 0; i < numPages; i++) { // Loop through all pages
        printf("%d ", pages[i]);         // Display each page number
    }
    printf("\n");                        // New line at end
    
    return numPages;                     // Return count of pages loaded
}

// Function to run and compare both FIFO and LRU algorithms side-by-side
void compareAlgorithms(int pages[], int numPages, int numFrames) {  // Takes pages, page count, frame count
    printf("\n========================================\n");  // Display comparison header
    printf("    ALGORITHM COMPARISON\n");                  // Display title
    printf("========================================\n");    // Display separator
    
    // Run FIFO algorithm first
    fifo(pages, numPages, numFrames);    // Call FIFO function
    
    printf("\n");                        // Blank line separator between algorithms
    
    // Run LRU algorithm second
    lru(pages, numPages, numFrames);     // Call LRU function
    
    printf("\n========================================\n");  // Display footer separator
    printf("Compare the results above to see which\n");     // Display comparison instruction
    printf("algorithm performs better for this\n");          // Continuation of instruction
    printf("page reference string.\n");                     // End of instruction
    printf("========================================\n");    // Display end separator
}

int main() {                             // Main function - program execution starts here
    int choice, numPages = 0, numFrames; // choice: menu option, numPages: count of pages (init to 0), numFrames: frame count
    int pages[MAX_PAGES];                // Array to store page reference string
    
    printf("\n╔════════════════════════════════════════╗\n");  // Display top border
    printf("║   PAGE REPLACEMENT SIMULATOR           ║\n");    // Display program title
    printf("║   FIFO & LRU Algorithms                ║\n");    // Display subtitle
    printf("╚════════════════════════════════════════╝\n");    // Display bottom border
    
    while (1) {                          // Infinite loop for menu system (until exit)
        printf("\n========================================\n");  // Display menu separator
        printf("             MAIN MENU\n");                     // Display menu title
        printf("========================================\n");    // Display menu separator
        printf("1. Enter page reference string\n");             // Option 1: Manual input
        printf("2. Use example page reference string\n");       // Option 2: Load example
        printf("3. Simulate FIFO algorithm\n");                 // Option 3: Run FIFO only
        printf("4. Simulate LRU algorithm\n");                  // Option 4: Run LRU only
        printf("5. Compare both algorithms\n");                 // Option 5: Run both and compare
        printf("6. Exit\n");                                    // Option 6: Exit program
        printf("========================================\n");    // Display menu separator
        printf("Enter your choice: ");                          // Prompt for choice
        scanf("%d", &choice);            // Read user's menu choice
        
        switch (choice) {                // Check which option user selected
            case 1:                      // If user chose to enter pages manually
                numPages = inputPages(pages);  // Call input function and store count
                break;                   // Exit switch statement
                
            case 2:                      // If user chose to use example
                numPages = useExamplePages(pages);  // Call example function and store count
                break;                   // Exit switch statement
                
            case 3:                      // If user chose FIFO simulation
                if (numPages == 0) {     // Check if page string has been entered
                    printf("\nPlease enter page reference string first!\n");  // Display error
                    break;               // Exit case
                }
                printf("\nEnter number of frames: ");  // Prompt for frame count
                scanf("%d", &numFrames); // Read frame count
                
                if (numFrames > MAX_FRAMES) {  // Check if exceeds maximum
                    printf("Error: Maximum frames allowed is %d\n", MAX_FRAMES);  // Display error
                    break;               // Exit case
                }
                
                fifo(pages, numPages, numFrames);  // Call FIFO algorithm
                break;                   // Exit switch statement
                
            case 4:                      // If user chose LRU simulation
                if (numPages == 0) {     // Check if page string has been entered
                    printf("\nPlease enter page reference string first!\n");  // Display error
                    break;               // Exit case
                }
                printf("\nEnter number of frames: ");  // Prompt for frame count
                scanf("%d", &numFrames); // Read frame count
                
                if (numFrames > MAX_FRAMES) {  // Check if exceeds maximum
                    printf("Error: Maximum frames allowed is %d\n", MAX_FRAMES);  // Display error
                    break;               // Exit case
                }
                
                lru(pages, numPages, numFrames);  // Call LRU algorithm
                break;                   // Exit switch statement
                
            case 5:                      // If user chose to compare algorithms
                if (numPages == 0) {     // Check if page string has been entered
                    printf("\nPlease enter page reference string first!\n");  // Display error
                    break;               // Exit case
                }
                printf("\nEnter number of frames: ");  // Prompt for frame count
                scanf("%d", &numFrames); // Read frame count
                
                if (numFrames > MAX_FRAMES) {  // Check if exceeds maximum
                    printf("Error: Maximum frames allowed is %d\n", MAX_FRAMES);  // Display error
                    break;               // Exit case
                }
                
                compareAlgorithms(pages, numPages, numFrames);  // Call comparison function
                break;                   // Exit switch statement
                
            case 6:                      // If user chose to exit
                printf("\nExiting program. Thank you!\n");  // Display exit message
                exit(0);                 // Terminate program with success code
                
            default:                     // If user entered invalid option
                printf("\nInvalid choice! Please try again.\n");  // Display error message
        }
    }
    
    return 0;                            // Return 0 to indicate successful execution (unreachable)
}
