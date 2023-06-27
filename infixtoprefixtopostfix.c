#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_SIZE 100

// Function to check if a given character is an operator or not
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get the precedence of an operator
int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Function to convert an infix expression to a postfix expression
void infix_to_postfix(char infix[], char postfix[]) {
    char stack[MAX_EXPRESSION_SIZE];
    int top = -1, i, j;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
        } else if (is_operator(infix[i])) {
            while (top >= 0 && stack[top] != '(' && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
        } else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top >= 0 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--;
        }
    }

    while (top >= 0) {
        postfix[j++] = stack[top--];
    }

    postfix[j] = '\0';
}

// Function to convert an infix expression to a prefix expression
void infix_to_prefix(char infix[], char prefix[]) {
    char reversed_infix[MAX_EXPRESSION_SIZE], reversed_postfix[MAX_EXPRESSION_SIZE];
    int i, j;

    // Reverse the infix expression
    for (i = strlen(infix) - 1, j = 0; i >= 0; i--, j++) {
        if (infix[i] == '(') {
            reversed_infix[j] = ')';
        } else if (infix[i] == ')') {
            reversed_infix[j] = '(';
        } else {
            reversed_infix[j] = infix[i];
        }
    }
    reversed_infix[j] = '\0';

    // Convert the reversed infix expression to a reversed postfix expression
    infix_to_postfix(reversed_infix, reversed_postfix);

    // Reverse the postfix expression to get the prefix expression
    for (i = strlen(reversed_postfix) - 1, j = 0; i >= 0; i--, j++) {
        prefix[j] = reversed_postfix[i];
    }
    prefix[j] = '\0';
}

int main() {
    char infix[MAX_EXPRESSION_SIZE], prefix[MAX_EXPRESSION_SIZE], postfix[MAX_EXPRESSION_SIZE];

    printf("Enter an infix expression: ");
    fgets(infix, MAX_EXPRESSION_SIZE, stdin);
    infix[strlen(infix) - 1] = '\0';

    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    infix_to_prefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    return 0;
}
