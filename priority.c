#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the priority queue
struct Node {
    int data;             // Data stored in the node
    int priority;         // Priority of the node
    struct Node* next;    // Pointer to the next node
};

// Function to create a new node
struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new element into the priority queue
void enqueue(struct Node** head, int data, int priority) {
    struct Node* newNode = createNode(data, priority);
    if (*head == NULL || priority < (*head)->priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    printf("Enqueued %d with priority %d\n", data, priority);
}

// Function to remove the element with the highest priority from the priority queue
void dequeue(struct Node** head) {
    if (*head == NULL) {
        printf("Priority queue is empty. Cannot dequeue.\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    printf("Dequeued %d with priority %d\n", temp->data, temp->priority);
    free(temp);
}

// Function to display the elements in the priority queue
void display(struct Node* head) {
    if (head == NULL) {
        printf("Priority queue is empty.\n");
        return;
    }
    struct Node* temp = head;
    printf("Priority queue: ");
    while (temp != NULL) {
        printf("(%d, %d) ", temp->data, temp->priority);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data, priority;

    while (1) {
        printf("\nPriority Queue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to enqueue: ");
                scanf("%d", &data);
                printf("Enter the priority: ");
                scanf("%d", &priority);
                enqueue(&head, data, priority);
                break;
            case 2:
                dequeue(&head);
                break;
            case 3:
                display(head);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
