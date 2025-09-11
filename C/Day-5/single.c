#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertBeg(struct Node** head, int x) {
    struct Node* n = malloc(sizeof(struct Node));
    n->data = x;
    n->next = *head;
    *head = n;
}
void insertEnd(struct Node** head, int x) {
    struct Node* n = malloc(sizeof(struct Node));
    n->data = x;
    n->next = NULL;
    if (*head == NULL) {
        *head = n;
        return;
    }
    struct Node* t = *head;
    while (t->next) t = t->next;
    t->next = n;
}
void insertPos(struct Node** head, int x, int pos) {
    struct Node* n = malloc(sizeof(struct Node));
    n->data = x;
    if (pos == 1) {
        n->next = *head;
        *head = n;
        return;
    }
    struct Node* t = *head;
    for (int i = 1; i < pos - 1 && t; i++) t = t->next;
    if (!t) {
        printf("Invalid position\n");
        free(n);
        return;
    }
    n->next = t->next;
    t->next = n;
}
void delBeg(struct Node** head) {
    if (!*head) return;
    struct Node* t = *head;
    *head = (*head)->next;
    free(t);
}

void delEnd(struct Node** head) {
    if (!*head) return;
    if (!(*head)->next) {
        free(*head);
        *head = NULL;
        return;
    }
    struct Node* t = *head;
    while (t->next->next) t = t->next;
    free(t->next);
    t->next = NULL;
}

void delPos(struct Node** head, int pos) {
    if (!*head) return;
    if (pos == 1) {
        struct Node* t = *head;
        *head = (*head)->next;
        free(t);
        return;
    }
    struct Node* t = *head;
    for (int i = 1; i < pos - 1 && t; i++) t = t->next;
    if (!t || !t->next) {
        printf("Invalid position\n");
        return;
    }
    struct Node* d = t->next;
    t->next = d->next;
    free(d);
}

void display(struct Node* head) {
    if (!head) {
        printf("List is empty\n");
        return;
    }
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int ch, x, pos;

    while (1) {
        printf("\n--- Singly Linked List Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete from Position\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: 
                printf("Enter value: ");
                scanf("%d", &x);
                insertBeg(&head, x);
                break;
            case 2: 
                printf("Enter value: ");
                scanf("%d", &x);
                insertEnd(&head, x);
                break;
            case 3: 
                printf("Enter position: ");
                scanf("%d", &pos);
                printf("Enter value: ");
                scanf("%d", &x);
                insertPos(&head, x, pos);
                break;
            case 4: 
                delBeg(&head);
                break;
            case 5: 
                delEnd(&head);
                break;
            case 6: 
                printf("Enter position: ");
                scanf("%d", &pos);
                delPos(&head, pos);
                break;
            case 7: 
                display(head);
                break;
            case 8: 
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }}}
        
