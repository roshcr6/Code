/*
 * Day 8: Memory Allocation Methods for Fixed Partition using Linked List
 * 
 * This program implements three memory allocation strategies:
 * a. First Fit - Allocate the first block that is big enough
 * b. Worst Fit - Allocate the largest available block
 * c. Best Fit - Allocate the smallest block that is big enough
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //for while boolean just used because terminal asked 

struct Block { //linked list struct
    int block_id;
    int block_size;
    int allocated;          
    int process_id;
    int process_size;
    int internal_frag; //leftover
    struct Block* next; //nxt node
};
struct Block* head = NULL; //node creation first node

void createBlocks(int n) { //creates partitions
    struct Block *temp, *newNode;
    int size;
    for(int i = 1; i <= n; i++) {
        newNode = (struct Block*)malloc(sizeof(struct Block));
        printf("Enter size of Block %d: ", i);
        scanf("%d", &size);
        newNode->block_id = i; //saves block id 
        newNode->block_size = size; //saves block size
        newNode->allocated = 0; //saves allocated memory
        newNode->process_id = -1; //saves pid
        newNode->process_size = 0; //saves p size
        newNode->internal_frag = 0; //saves leftover
        newNode->next = NULL; //last node points to null
        if(head == NULL)
            head = newNode;
        else {
            temp = head;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

void resetBlocks() {
    struct Block* temp = head;
    while(temp != NULL) {
        temp->allocated = 0;
        temp->process_id = -1;
        temp->process_size = 0;
        temp->internal_frag = 0;
        temp = temp->next;
    }
}

void display() {
    struct Block* temp = head;
    int total_frag = 0;
    printf("\n\n%-10s %-10s %-15s %-15s %-20s\n", 
           "Process", "Block", "Process Size", "Block Size", "Internal Frag");
    printf("-----------------------------------------------------------------------\n");
    while(temp != NULL) {
        if(temp->allocated) {
            printf("P%-9d %-10d %-15d %-15d %-20d\n",
                   temp->process_id,
                   temp->block_id,
                   temp->process_size,
                   temp->block_size,
                   temp->internal_frag);
            total_frag += temp->internal_frag;
        }
        temp = temp->next;
    }
    printf("-----------------------------------------------------------------------\n");
    printf("Total Internal Fragmentation: %d KB\n", total_frag);
}

void firstFit(int processes[], int m) {
    printf("\n========== FIRST FIT ==========\n");
    for(int i = 0; i < m; i++) {
        struct Block* temp = head;
        int allocated = 0;
        while(temp != NULL) {
            if(temp->allocated == 0 &&
               temp->block_size >= processes[i]) {
                temp->allocated = 1;
                temp->process_id = i+1;
                temp->process_size = processes[i];
                temp->internal_frag =
                    temp->block_size - processes[i];
                allocated = 1;
                break;
            }
            temp = temp->next;
        }
        if(!allocated)
            printf("Process P%d (%d KB) not allocated\n", i+1, processes[i]);
    }
    display();
}

void bestFit(int processes[], int m) {
    printf("\n========== BEST FIT ==========\n");
    for(int i = 0; i < m; i++) {
        struct Block* temp = head;
        struct Block* best = NULL;
        int min = 999999;
        while(temp != NULL) {
            if(temp->allocated == 0 &&
               temp->block_size >= processes[i]) {
                int diff = temp->block_size - processes[i];
                if(diff < min) {
                    min = diff;
                    best = temp;
                }
            }
            temp = temp->next;
        }
        if(best != NULL) {
            best->allocated = 1;
            best->process_id = i+1;
            best->process_size = processes[i];
            best->internal_frag =
                best->block_size - processes[i];
        } else {
            printf("Process P%d (%d KB) not allocated\n", i+1, processes[i]);
        }
    }
    display();
}

void worstFit(int processes[], int m) {
    printf("\n========== WORST FIT ==========\n");
    for(int i = 0; i < m; i++) {
        struct Block* temp = head;
        struct Block* worst = NULL;
        int max = -1;
        while(temp != NULL) {
            if(temp->allocated == 0 &&
               temp->block_size >= processes[i]) {
                int diff = temp->block_size - processes[i];
                if(diff > max) {
                    max = diff;
                    worst = temp;
                }
            }
            temp = temp->next;
        }
        if(worst != NULL) {
            worst->allocated = 1;
            worst->process_id = i+1;
            worst->process_size = processes[i];
            worst->internal_frag =
                worst->block_size - processes[i];
        } else {
            printf("Process P%d (%d KB) not allocated\n", i+1, processes[i]);
        }
    }
    display();
}
           
int main() { //starts here
    int n, m, choice;
    printf("Enter number of memory blocks: "); //takes user inputs about no of memory block
    scanf("%d", &n);
    createBlocks(n); //block creation function call with n 
    printf("\nEnter number of processes: "); //takes user inputs about no of processes
    scanf("%d", &m);
    int processes[m]; //array of processes
    for(int i = 0; i < m; i++) { //size allocation
        printf("Enter size of Process P%d: ", i+1);
        scanf("%d", &processes[i]);
    }
    
    while(true) { //choices here menu section
        printf("\n========================================\n");
        printf("             MAIN MENU\n");
        printf("========================================\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        resetBlocks(); //to reset blocks for next menu
        
        switch(choice) {
            case 1:
                firstFit(processes, m);
                break;
            case 2:
                bestFit(processes, m);
                break;
            case 3:
                worstFit(processes, m);
                break;
            case 4:
                printf("\nExiting program. Thank you!\n");
                return 0;
            default:
                printf("Invalid Choice\n");
        }
    }   
    return 0;
}