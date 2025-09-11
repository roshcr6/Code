#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAX_SIZE 100


char char_stack[MAX_SIZE];
int char_top = -1;


int int_stack[MAX_SIZE];
int int_top = -1;


void char_push(char item) {
    if (char_top == MAX_SIZE - 1) {
        printf("Character stack overflow!\n");
        return;
    }
    char_stack[++char_top] = item;
}

char char_pop() {
    if (char_top == -1) {
        return '\0';
    }
    return char_stack[char_top--];
}

char char_peek() {
    if (char_top == -1) {
        return '\0'; 
    }
    return char_stack[char_top];
}

int is_char_stack_empty() {
    return char_top == -1;
}


void int_push(int item) {
    if (int_top == MAX_SIZE - 1) {
        printf("Integer stack overflow!\n");
        return;
    }
    int_stack[++int_top] = item;
}

int int_pop() {
    if (int_top == -1) {
        return -1;
    }
    return int_stack[int_top--];
}

int is_int_stack_empty() {
    return int_top == -1;
}
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

void infix_to_postfix(char infix[], char postfix[]) {
    int i, j;
    char item;
    char_top = -1;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        item = infix[i];
        if (isalnum(item)) { 
            postfix[j++] = item;
        } else if (item == '(') {
            char_push(item);
        } else if (item == ')') { 
            while (!is_char_stack_empty() && char_peek() != '(') {
                postfix[j++] = char_pop();
            }
            if (!is_char_stack_empty() && char_peek() == '(') {
                char_pop(); // Pop '('
            }
        } else { 
            while (!is_char_stack_empty() && precedence(item) <= precedence(char_peek())) {
                postfix[j++] = char_pop();
            }
            char_push(item);
        }
    }
    while (!is_char_stack_empty()) {
        postfix[j++] = char_pop();
    }
    postfix[j] = '\0';
    }
int evaluate_postfix(char postfix[]) {
    int i, op1, op2, result;
    int_top = -1; 

    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            int_push(postfix[i] - '0');
            
        } else {
            op2 = int_pop();
            op1 = int_pop();
            switch (postfix[i]) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '^': 
                    result = 1;
                    for (int k = 0; k < op2; k++) result *= op1;
                    break;
            }
            int_push(result);
        }
    }
    return int_pop();
}
int main() {
    int choice;
    char infix_expr[MAX_SIZE];
    char postfix_expr[MAX_SIZE];

    do {
        printf("\n--- Menu ---\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Evaluate Postfix Expression\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                fgets(infix_expr, MAX_SIZE, stdin);
                infix_expr[strcspn(infix_expr, "\n")] = 0; 
                infix_to_postfix(infix_expr, postfix_expr);
                printf("Postfix expression: %s\n", postfix_expr);
                break;
            case 2:
                printf("Enter postfix expression to evaluate : ");
                fgets(postfix_expr, MAX_SIZE, stdin);
                postfix_expr[strcspn(postfix_expr, "\n")] = 0; 
                printf("Result: %d\n", evaluate_postfix(postfix_expr));
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
