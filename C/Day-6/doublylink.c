#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node *prev, *next;
};

struct Node* head = NULL;

// Utility: Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

/* ===================== INSERTION ===================== */

// Insert at beginning
void insertAtBeginning(int data) {
    struct Node* newNode = createNode(data);
    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }
    head = newNode;
    printf("Inserted %d at beginning.\n", data);
}

// Insert at end
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

// Insert after a specific node
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

/* ===================== DELETION ===================== */

// Delete at beginning
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

// Delete at end
void deleteAtEnd() {
    if (head == NULL) {
        printf("List empty!\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    if (temp->prev != NULL) temp->prev->next = NULL;
    else head = NULL; // only one node
    printf("Deleted %d from end.\n", temp->data);
    free(temp);
}

// Delete a specific node
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

/* ===================== DISPLAY ===================== */

// Display forward
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

// Display backward
void displayBackward() {
    if (head == NULL) {
        printf("List empty!\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next; // move to last
    printf("List (Backward): ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

/* ===================== MAIN MENU ===================== */

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
        case 1: // Insertion submenu
            while (1) {
                printf("\n-- Insertion Menu --\n");
                printf("1. Insert at Beginning\n");
                printf("2. Insert at End\n");
                printf("3. Insert After a Node\n");
                printf("4. Go Back\n");
                printf("5. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &subChoice);

                if (subChoice == 1) {
                    printf("Enter data: ");
                    scanf("%d", &data);
                    insertAtBeginning(data);
                }
                else if (subChoice == 2) {
                    printf("Enter data: ");
                    scanf("%d", &data);
                    insertAtEnd(data);
                }
                else if (subChoice == 3) {
                    printf("Enter key: ");
                    scanf("%d", &key);
                    printf("Enter data: ");
                    scanf("%d", &data);
                    insertAfter(key, data);
                }
                else if (subChoice == 4) break; // go back
                else if (subChoice == 5) exit(0);
                else printf("Invalid choice!\n");
            }
            break;

        case 2: // Deletion submenu
            while (1) {
                printf("\n-- Deletion Menu --\n");
                printf("1. Delete at Beginning\n");
                printf("2. Delete at End\n");
                printf("3. Delete Specific Node\n");
                printf("4. Go Back\n");
                printf("5. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &subChoice);

                if (subChoice == 1) deleteAtBeginning();
                else if (subChoice == 2) deleteAtEnd();
                else if (subChoice == 3) {
                    printf("Enter key: ");
                    scanf("%d", &key);
                    deleteNode(key);
                }
                else if (subChoice == 4) break; // go back
                else if (subChoice == 5) exit(0);
                else printf("Invalid choice!\n");
            }
            break;

        case 3: // Display submenu
            while (1) {
                printf("\n-- Display Menu --\n");
                printf("1. Forward\n");
                printf("2. Backward\n");
                printf("3. Go Back\n");
                printf("4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &subChoice);

                if (subChoice == 1) displayForward();
                else if (subChoice == 2) displayBackward();
                else if (subChoice == 3) break; // go back
                else if (subChoice == 4) exit(0);
                else printf("Invalid choice!\n");
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
