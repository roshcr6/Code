#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
int opStack[MAX];
int top = -1;
void push(int x) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        exit(1);
    }opStack[++top] = x;}

int pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);}return opStack[top--];}

int peek() {
    if (top == -1) return -1;
    return opStack[top];}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;}

void infixToPostfix(char *infix, char *postfix) {
    int i = 0, k = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }postfix[k++] = ' '; 
            continue;}
        else if (infix[i] == '(') {
            push(infix[i]);}
        else if (infix[i] == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
                postfix[k++] = ' ';}
            pop();  }
        else {
            while (top != -1 && precedence(peek()) >= precedence(infix[i])) {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }push(infix[i]);}i++;}
    while (top != -1) {
        postfix[k++] = pop();
        postfix[k++] = ' ';
    }postfix[k] = '\0';}

int evaluatePostfix(char *postfix) {
    int evalStack[MAX];
    int evalTop = -1;
    int i = 0;

    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }evalStack[++evalTop] = num;}
        else if (postfix[i] == '+' || postfix[i] == '-' || 
                 postfix[i] == '*' || postfix[i] == '/' || 
                 postfix[i] == '^') {
            int val2 = evalStack[evalTop--];
            int val1 = evalStack[evalTop--];
            int res;
            switch (postfix[i]) {
                case '+': res = val1 + val2; break;
                case '-': res = val1 - val2; break;
                case '*': res = val1 * val2; break;
                case '/': res = val1 / val2; break;
                case '^': {
                    res = 1;
                    for (int j = 0; j < val2; j++) res *= val1;
                    break;}}evalStack[++evalTop] = res;}i++;}
    return evalStack[evalTop];}

int main() {
    char infix[MAX], postfix[MAX];
    int choice;
    do {
        printf("\n==== MENU ====\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Evaluate Postfix Expression\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0';
                top = -1; // reset stack
                infixToPostfix(infix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;
            case 2:
                printf("Enter postfix expression (space-separated): ");
                fgets(postfix, MAX, stdin);
                postfix[strcspn(postfix, "\n")] = '\0';
                printf("Evaluation Result: %d\n", evaluatePostfix(postfix));
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }} while (choice != 3);return 0;}
