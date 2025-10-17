#include <stdio.h>
#define SIZE 10

int hashTable[SIZE];

void init() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;
}

void insertLinear(int key) {
    int index = key % SIZE;
    int i = index;
    while (hashTable[i] != -1)
        i = (i + 1) % SIZE;
    hashTable[i] = key;
}

void insertQuadratic(int key) {
    int index = key % SIZE;
    int i = 0;
    while (hashTable[(index + i*i) % SIZE] != -1)
        i++;
    hashTable[(index + i*i) % SIZE] = key;
}

void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d -> %d\n", i, hashTable[i]);
}

int main() {
    int choice, key;
    init();
    while (1) {
        printf("\n1. Insert (Linear Probing)\n2. Insert (Quadratic Probing)\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                insertLinear(key);
                break;
            case 2:
                printf("Enter key: ");
                scanf("%d", &key);
                insertQuadratic(key);
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
        }
    }
}
