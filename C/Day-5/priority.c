#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    int priority;
    struct Node* next;};

struct Node* front = NULL;
struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

void enqueue(int data, int priority) {
    struct Node* newNode = createNode(data, priority);
    if (front == NULL || priority < front->priority) {
        newNode->next = front;
        front = newNode;
    } else {
        struct Node* temp = front;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;}
        newNode->next = temp->next;
        temp->next = newNode;
    }printf("Inserted element %d with priority %d\n", data, priority);}

void dequeue() {
    if (front == NULL) {
        printf("Priority Queue is empty. Nothing to delete.\n");
        return;}
    struct Node* temp = front;
    printf("Deleted element %d with priority %d\n", temp->data, temp->priority);
    front = front->next;
    free(temp);}

void display() {
    if (front == NULL) {
        printf("Priority Queue is empty.\n");
        return;}
    struct Node* temp = front;
    printf("Priority Queue (data:priority): ");
    while (temp != NULL) {
        printf("%d:%d ", temp->data, temp->priority);
        temp = temp->next;
    }printf("\n");}

int main() {
    int choice, data, priority;
    while (1) {
        printf("\n===== PRIORITY QUEUE MENU =====\n");
        printf("1. Add an element\n");
        printf("2. Delete an element\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &data);
                printf("Enter priority (lower number = higher priority): ");
                scanf("%d", &priority);
                enqueue(data, priority);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }}return 0;}
