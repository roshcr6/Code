#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

void findDuplicates(struct Node* head) {
    struct Node *ptr1, *ptr2;
    int found = 0;

    for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->next) {
        ptr2 = ptr1->next;
        while (ptr2 != NULL) {
            if (ptr1->data == ptr2->data) {
                printf("Duplicate: %d\n", ptr1->data);
                found = 1;
                break;
            }
            ptr2 = ptr2->next;
        }
    }
    if (!found)
        printf("No duplicates found.");
}

int main() {
    struct Node* head = NULL;
    int n, data;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertEnd(&head, data);
    }

    findDuplicates(head);
    return 0;
}

