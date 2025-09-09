#include <stdio.h>
#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1)
        printf("ERROR : Queue Overflow\n");
    else {
        if (front == -1) front = 0;
        queue[++rear] = value;
        printf("Added : %d to the queue\n", value);
        
    }
}

void dequeue() {
    if (front == -1 || front > rear)
        printf("Queue Underflow\n");
    else
        printf("Removed : %d from the queue\n", queue[front++]);
}

void display() {
    if (front == -1 || front > rear)
        printf("Queue is Empty\n");
    else {
        printf("Queue contents:\n");
        for (int i = front; i <= rear; i++)
            printf("%d ", queue[i]);
        printf("\n");
    }
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if(choice!=4)
        printf("Starting The Designated Program...\n");
        else
        printf("Exiting the program...\nByee...\n");

        switch (choice) {
            case 1:
                printf("Enter the value you wanna add to the queue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}

