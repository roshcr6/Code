/*
 * Day 9: Page Replacement Algorithms Simulation
 * 
 * This program simulates two page replacement algorithms:
 * a. FIFO (First In First Out) - Replace the oldest page
 * b. LRU (Least Recently Used) - Replace the page that hasn't been used for longest time
 * 
 * The program calculates page faults and hit ratio for performance evaluation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

// Function to check if page is in frame
int searchPage(int page, int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return i; // Return position if found
        }
    }
    return -1; // Not found
}

// Function to display current frame status
void displayFrames(int frames[], int numFrames) {
    printf("| ");
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == -1) {
            printf("  - ");
        } else {
            printf(" %2d ", frames[i]);
        }
    }
    printf("|");
}

// FIFO Page Replacement Algorithm
void fifo(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int pageHits = 0;
    int nextReplace = 0; // Index for next frame to replace
    
    // Initialize frames to -1 (empty)
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }
    
    printf("\n========================================\n");
    printf("    FIFO PAGE REPLACEMENT SIMULATION\n");
    printf("========================================\n");
    printf("Number of Frames: %d\n", numFrames);
    printf("========================================\n");
    printf("Page | Frames               | Status\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];
        printf(" %2d  ", currentPage);
        
        // Check if page is already in frame
        int position = searchPage(currentPage, frames, numFrames);
        
        if (position != -1) {
            // Page Hit
            displayFrames(frames, numFrames);
            printf(" HIT\n");
            pageHits++;
        } else {
            // Page Fault
            frames[nextReplace] = currentPage;
            displayFrames(frames, numFrames);
            printf(" FAULT\n");
            pageFaults++;
            
            // Move to next frame (circular)
            nextReplace = (nextReplace + 1) % numFrames;
        }
    }
    
    printf("========================================\n");
    printf("RESULTS:\n");
    printf("Total Page References: %d\n", numPages);
    printf("Page Faults: %d\n", pageFaults);
    printf("Page Hits: %d\n", pageHits);
    printf("Hit Ratio: %.2f%%\n", (pageHits * 100.0) / numPages);
    printf("Fault Ratio: %.2f%%\n", (pageFaults * 100.0) / numPages);
    printf("========================================\n");
}

// LRU Page Replacement Algorithm
void lru(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int lastUsed[MAX_FRAMES]; // Track when each frame was last used
    int pageFaults = 0;
    int pageHits = 0;
    int time = 0;
    
    // Initialize frames to -1 (empty) and lastUsed to 0
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
        lastUsed[i] = 0;
    }
    
    printf("\n========================================\n");
    printf("    LRU PAGE REPLACEMENT SIMULATION\n");
    printf("========================================\n");
    printf("Number of Frames: %d\n", numFrames);
    printf("========================================\n");
    printf("Page | Frames               | Status\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];
        printf(" %2d  ", currentPage);
        time++;
        
        // Check if page is already in frame
        int position = searchPage(currentPage, frames, numFrames);
        
        if (position != -1) {
            // Page Hit - Update last used time
            displayFrames(frames, numFrames);
            printf(" HIT\n");
            pageHits++;
            lastUsed[position] = time;
        } else {
            // Page Fault - Find victim page
            int replaceIndex = 0;
            
            // Check if there's an empty frame
            bool emptyFound = false;
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    emptyFound = true;
                    break;
                }
            }
            
            // If no empty frame, find LRU page
            if (!emptyFound) {
                int minTime = lastUsed[0];
                replaceIndex = 0;
                
                for (int j = 1; j < numFrames; j++) {
                    if (lastUsed[j] < minTime) {
                        minTime = lastUsed[j];
                        replaceIndex = j;
                    }
                }
            }
            
            // Replace the page
            frames[replaceIndex] = currentPage;
            lastUsed[replaceIndex] = time;
            
            displayFrames(frames, numFrames);
            printf(" FAULT\n");
            pageFaults++;
        }
    }
    
    printf("========================================\n");
    printf("RESULTS:\n");
    printf("Total Page References: %d\n", numPages);
    printf("Page Faults: %d\n", pageFaults);
    printf("Page Hits: %d\n", pageHits);
    printf("Hit Ratio: %.2f%%\n", (pageHits * 100.0) / numPages);
    printf("Fault Ratio: %.2f%%\n", (pageFaults * 100.0) / numPages);
    printf("========================================\n");
}

// Function to input page reference string
int inputPages(int pages[]) {
    int numPages;
    
    printf("\n--- Enter Page Reference String ---\n");
    printf("Enter number of page references: ");
    scanf("%d", &numPages);
    
    if (numPages > MAX_PAGES) {
        printf("Error: Maximum pages allowed is %d\n", MAX_PAGES);
        return 0;
    }
    
    printf("Enter page reference string:\n");
    for (int i = 0; i < numPages; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }
    
    printf("\nPage Reference String: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");
    
    return numPages;
}

// Function to use example page reference string
int useExamplePages(int pages[]) {
    // Example: 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1
    int example[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int numPages = 20;
    
    for (int i = 0; i < numPages; i++) {
        pages[i] = example[i];
    }
    
    printf("\nExample Page Reference String Loaded:\n");
    printf("Pages: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");
    
    return numPages;
}

// Function to compare both algorithms
void compareAlgorithms(int pages[], int numPages, int numFrames) {
    printf("\n========================================\n");
    printf("    ALGORITHM COMPARISON\n");
    printf("========================================\n");
    
    // Run FIFO
    fifo(pages, numPages, numFrames);
    
    printf("\n");
    
    // Run LRU
    lru(pages, numPages, numFrames);
    
    printf("\n========================================\n");
    printf("Compare the results above to see which\n");
    printf("algorithm performs better for this\n");
    printf("page reference string.\n");
    printf("========================================\n");
}

int main() {
    int choice, numPages = 0, numFrames;
    int pages[MAX_PAGES];
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║   PAGE REPLACEMENT SIMULATOR           ║\n");
    printf("║   FIFO & LRU Algorithms                ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    while (1) {
        printf("\n========================================\n");
        printf("             MAIN MENU\n");
        printf("========================================\n");
        printf("1. Enter page reference string\n");
        printf("2. Use example page reference string\n");
        printf("3. Simulate FIFO algorithm\n");
        printf("4. Simulate LRU algorithm\n");
        printf("5. Compare both algorithms\n");
        printf("6. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                numPages = inputPages(pages);
                break;
                
            case 2:
                numPages = useExamplePages(pages);
                break;
                
            case 3:
                if (numPages == 0) {
                    printf("\nPlease enter page reference string first!\n");
                    break;
                }
                printf("\nEnter number of frames: ");
                scanf("%d", &numFrames);
                
                if (numFrames > MAX_FRAMES) {
                    printf("Error: Maximum frames allowed is %d\n", MAX_FRAMES);
                    break;
                }
                
                fifo(pages, numPages, numFrames);
                break;
                
            case 4:
                if (numPages == 0) {
                    printf("\nPlease enter page reference string first!\n");
                    break;
                }
                printf("\nEnter number of frames: ");
                scanf("%d", &numFrames);
                
                if (numFrames > MAX_FRAMES) {
                    printf("Error: Maximum frames allowed is %d\n", MAX_FRAMES);
                    break;
                }
                
                lru(pages, numPages, numFrames);
                break;
                
            case 5:
                if (numPages == 0) {
                    printf("\nPlease enter page reference string first!\n");
                    break;
                }
                printf("\nEnter number of frames: ");
                scanf("%d", &numFrames);
                
                if (numFrames > MAX_FRAMES) {
                    printf("Error: Maximum frames allowed is %d\n", MAX_FRAMES);
                    break;
                }
                
                compareAlgorithms(pages, numPages, numFrames);
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
