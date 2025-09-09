#include <stdio.h>
#define MAX 100

int stack[MAX];
int top = -1;

void push(int value) {//choice 1 push into the stack
    if (top == MAX - 1)
        printf("ERROR : Stack Overflow\n");
    else {
        stack[++top] = value;
        printf("inserted : %d to the array\n", value);
        printf("Continue The Work...\n");
    }
}

void pop() {//choice 2 pop the last element
    if (top == -1)
        printf("ERROR : Stack Underflow\n");
    else
    	{printf("Deleting the last entered value from the array...\n");
        printf("Deleted : %d from the array\n", stack[top--]);
        printf("Continue The Work...\n");}
}

void display() {//choice 3 display all elements in the stack
    if (top == -1)
        printf("Stack is Empty\n");
    else {
        printf("Stack contents:\n");
        for (int i = top; i >= 0; i--)
            printf("%d\n", stack[i]);
    }
}

int main() {//main program with menu
    int choice, value;

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if(choice!=4)
        printf("Starting The Designated Program...\n");
        else
        printf("Exiting the program...\nByee...\n");

        switch (choice) {
            case 1:
                printf("Enter the value you wanna insert to the array: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid Input\n");
        }
    }
}

