#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* top = NULL;
struct Node* front = NULL;
struct Node* rear = NULL;

void push(int x) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = top;
    top = newNode;
}

void pop() {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Popped: %d\n", top->data);
    struct Node* temp = top;
    top = top->next;
    free(temp);
}

void displayStack() {
    if (top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    struct Node* temp = top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void enqueue(int x) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("Dequeued: %d\n", front->data);
    struct Node* temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
}

void displayQueue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    struct Node* temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int ch, x;
    while (1) {
        printf("\n1.Push\n2.Pop\n3.Display Stack\n4.Enqueue\n5.Dequeue\n6.Display Queue\n7.Exit\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1: 
            printf("Enter number: ");
            scanf("%d", &x); 
            push(x); 
            break;
            case 2: 
            pop();
            break;
            case 3: 
            displayStack(); 
            break;
            case 4: 
            printf("Enter number: "); 
            scanf("%d", &x); 
            enqueue(x); 
            break;
            case 5: 
            dequeue(); 
            break;
            case 6: 
            displayQueue(); 
            break;
            case 7: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}

