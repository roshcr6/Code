#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100


char opStack[MAX];
int valStack[MAX];
int topOp = -1;
int topVal = -1;


void pushOp(char c) {
    if (topOp == MAX - 1)
        printf("Operator Stack Overflow\n");
    else
        opStack[++topOp] = c;
}

char popOp() {
    if (topOp == -1)
        return '\0';
    else
        return opStack[topOp--];
}

char peekOp() {
    if (topOp == -1) return '\0';
    return opStack[topOp];
}

void pushVal(int x) {
    if (topVal == MAX - 1)
        printf("Value Stack Overflow\n");
    else
        valStack[++topVal] = x;
}

int popVal() {
    if (topVal == -1) {
        printf("Value Stack Underflow\n");
        return 0;
    }
    return valStack[topVal--];
}


int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}


void InfixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char ch;

    for (i = 0; i < strlen(infix); i++) {
        ch = infix[i];

        if (isalnum(ch)) { 
            postfix[k++] = ch;
        }
        else if (ch == '(') {
            pushOp(ch);
        }
        else if (ch == ')') {
            while (peekOp() != '(' && topOp != -1) {
                postfix[k++] = popOp();
            }
            popOp(); 
        }
        else { 
            while (topOp != -1 && precedence(peekOp()) >= precedence(ch)) {
                postfix[k++] = popOp();
            }
            pushOp(ch);
        }
    }


    while (topOp != -1) {
        postfix[k++] = popOp();
    }
    postfix[k] = '\0';
}

int EvaluatePostfix(char postfix[]) {
    int i;
    char ch;
    int op1, op2, result;

    for (i = 0; i < strlen(postfix); i++) {
        ch = postfix[i];

        if (isdigit(ch)) {
            pushVal(ch - '0'); 
        }
        else {
            op2 = popVal();
            op1 = popVal();

            switch (ch) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '^': result = pow(op1, op2); break;
            }
            pushVal(result);
        }
    }
    return popVal();
}

int main() {
    char infix[MAX], postfix[MAX];
    int choice, result;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Enter Infix Expression\n");
        printf("2. Convert Infix to Postfix\n");
        printf("3. Evaluate Postfix Expression\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                break;
            case 2:
                InfixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;
            case 3:
                result = EvaluatePostfix(postfix);
                printf("Result: %d\n", result);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}

