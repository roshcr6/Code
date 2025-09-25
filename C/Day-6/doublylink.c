#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

struct Node* head = NULL;

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(int data) {
    struct Node* newNode = createNode(data);
    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }
    head = newNode;
    printf("Inserted %d at beginning.\n", data);
}

void insertAtEnd(int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        head = newNode;
    } else {
        struct Node* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
    printf("Inserted %d at end.\n", data);
}

void insertAfter(int key, int data) {
    struct Node* temp = head;
    while (temp != NULL && temp->data != key) temp = temp->next;
    if (temp == NULL) {
        printf("Node %d not found!\n", key);
        return;
    }
    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    if (temp->next != NULL) temp->next->prev = newNode;
    temp->next = newNode;
    newNode->prev = temp;
    printf("Inserted %d after %d.\n", data, key);
}

void deleteAtBeginning() {
    if (head == NULL) {
        printf("List empty!\n");
        return;
    }
    struct Node* temp = head;
    head = head->next;
    if (head != NULL) head->prev = NULL;
    printf("Deleted %d from beginning.\n", temp->data);
    free(temp);
}

void deleteAtEnd() {
    if (head == NULL) {
        printf("List empty!\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    if (temp->prev != NULL) temp->prev->next = NULL;
    else head = NULL;
    printf("Deleted %d from end.\n", temp->data);
    free(temp);
}

void deleteNode(int key) {
    struct Node* temp = head;
    while (temp != NULL && temp->data != key) temp = temp->next;
    if (temp == NULL) {
        printf("Node %d not found!\n", key);
        return;
    }
    if (temp->prev != NULL) temp->prev->next = temp->next;
    else head = temp->next;
    if (temp->next != NULL) temp->next->prev = temp->prev;
    printf("Deleted node with value %d.\n", key);
    free(temp);
}

void displayForward() {
    if (head == NULL) {
        printf("List empty!\n");
        return;
    }
    struct Node* temp = head;
    printf("List (Forward): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void displayBackward() {
    if (head == NULL) {
        printf("List empty!\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    printf("List (Backward): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int main() {
    int choice, subChoice, data, key;

    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\n-- Insertion Menu --\n");
            printf("1. Insert at Beginning\n");
            printf("2. Insert at End\n");
            printf("3. Insert After a Node\n");
            printf("Enter your choice: ");
            scanf("%d", &subChoice);

            switch (subChoice) {
                case 1:
                    printf("Enter data: ");
                    scanf("%d", &data);
                    insertAtBeginning(data);
                    break;
                case 2:
                    printf("Enter data: ");
                    scanf("%d", &data);
                    insertAtEnd(data);
                    break;
                case 3:
                    printf("Enter key: ");
                    scanf("%d", &key);
                    printf("Enter data: ");
                    scanf("%d", &data);
                    insertAfter(key, data);
                    break;
                default:
                    printf("Invalid choice!\n");
            }
            break;

        case 2:
            printf("\n-- Deletion Menu --\n");
            printf("1. Delete at Beginning\n");
            printf("2. Delete at End\n");
            printf("3. Delete Specific Node\n");
            printf("Enter your choice: ");
            scanf("%d", &subChoice);

            switch (subChoice) {
                case 1:
                    deleteAtBeginning();
                    break;
                case 2:
                    deleteAtEnd();
                    break;
                case 3:
                    printf("Enter key: ");
                    scanf("%d", &key);
                    deleteNode(key);
                    break;
                default:
                    printf("Invalid choice!\n");
            }
            break;

        case 3:
            printf("\n-- Display Menu --\n");
            printf("1. Forward\n");
            printf("2. Backward\n");
            printf("Enter your choice: ");
            scanf("%d", &subChoice);

            switch (subChoice) {
                case 1:
                    displayForward();
                    break;
                case 2:
                    displayBackward();
                    break;
                default:
                    printf("Invalid choice!\n");
            }
            break;

        case 4:
            printf("Exiting program...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
