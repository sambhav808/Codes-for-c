#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Global variable to keep track of the top of the stack
struct Node* top = NULL;

// Function to push an element onto the stack
void push(int value) {
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed. Stack overflow.\n");
        return;
    }

    // Set the data of the new node and update the next pointer
    newNode->data = value;
    newNode->next = top;

    // Update the top to point to the new node
    top = newNode;

    printf("Pushed %d onto the stack.\n", value);
}

// Function to pop an element from the stack
int pop() {
    if (top == NULL) {
        printf("Stack is empty. Cannot perform pop operation.\n");
        return -1;
    }

    // Store the data of the top node
    int poppedValue = top->data;

    // Update the top to point to the next node
    struct Node* temp = top;
    top = top->next;

    // Free the memory of the previous top node
    free(temp);

    return poppedValue;
}

// Function to display the elements in the stack
void display() {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Elements in the stack: ");
    struct Node* current = top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                value = pop();
                if (value != -1)
                    printf("Popped value: %d\n", value);
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
