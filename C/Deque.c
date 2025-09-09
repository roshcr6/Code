#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int deque[SIZE];
int front = -1, rear = -1;
void insertRear(int value) {
    if ((front == 0 && rear == SIZE - 1) || (front == rear + 1)) {
        printf("Deque Overflow!\n");
    } else {
        if (front == -1) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }
        deque[rear] = value;
        printf("%d inserted at rear.\n", value);
    }
}
void insertFront(int value) {
    if ((front == 0 && rear == SIZE - 1) || (front == rear + 1)) {
        printf("Deque Overflow!\n");
    } else {
        if (front == -1) {
            front = rear = 0;
        } else {
            front = (front - 1 + SIZE) % SIZE;
        }
        deque[front] = value;
        printf("%d inserted at front.\n", value);
    }
}
void deleteFront() {
    if (front == -1) {
        printf("Deque Underflow!\n");
    } else {
        printf("Deleted from front: %d\n", deque[front]);
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }}}
void deleteRear() {
    if (front == -1) {
        printf("Deque Underflow!\n");
    } else {
        printf("Deleted from rear: %d\n", deque[rear]);
        if (front == rear) {
            front = rear = -1;
        } else {
            rear = (rear - 1 + SIZE) % SIZE;
        }}}

void display() {
    if (front == -1) {
        printf("Deque is Empty.\n");
    } else {
        printf("Deque elements: ");
        int i = front;
        while (1) {
            printf("%d ", deque[i]);
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        printf("\n");
    }
}

int main() {
    int choice, value, type;
    printf("\nChoose Deque Type:\n1. Input Restricted\n2. Output Restricted\nEnter: ");
    scanf("%d", &type);

    while (1) {
        printf("\n--- Deque Menu ---\n");
        if (type == 1) {
            printf("1. Insert Rear\n2. Delete Front\n3. Delete Rear\n4. Display\n5. Exit\n");
        } else {
            printf("1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Display\n5. Exit\n");
        }
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (type == 1) {
                    printf("Enter value: ");
                    scanf("%d", &value);
                    insertRear(value);
                } else {
                    printf("Enter value: ");
                    scanf("%d", &value);
                    insertFront(value);
                }
                break;
            case 2:
                if (type == 1) {
                    deleteFront();
                } else {
                    printf("Enter value: ");
                    scanf("%d", &value);
                    insertRear(value);
                }
                break;
            case 3:
                if (type == 1) {
                    deleteRear();
                } else {
                    deleteFront();
                }
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
