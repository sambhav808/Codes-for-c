#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
    printf("Node inserted successfully at the beginning.\n");
}

// Function to insert a node at the end
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    printf("Node inserted successfully at the end.\n");
}

// Function to delete a node by value
void deleteNode(struct Node** head, int value) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete node.\n");
        return;
    }
    struct Node* current = *head;
    struct Node* prevNode = NULL;

    // Check if the node to be deleted is the first node
    if (current->data == value) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(current);
        printf("Node deleted successfully.\n");
        return;
    }

    // Find the node to be deleted
    while (current != NULL && current->data != value) {
        prevNode = current;
        current = current->next;
    }

    // Node not found
    if (current == NULL) {
        printf("Node with value %d not found.\n", value);
        return;
    }

    // Update pointers and free memory
    prevNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = prevNode;
    }
    free(current);
    printf("Node deleted successfully.\n");
}

// Function to perform linear search
void linearSearch(struct Node* head, int key) {
    struct Node* current = head;
    int position = 0;
    while (current != NULL) {
        if (current->data == key) {
            printf("Element %d found at position %d.\n", key, position);
            return;
        }
        position++;
        current = current->next;
    }
    printf("Element %d not found in the list.\n", key);
}

// Function to display the doubly linked list
void displayList(struct Node* head) {
    struct Node* current = head;
    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Doubly linked list:\n");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free memory occupied by the doubly linked list
void freeList(struct Node** head) {
    struct Node* current = *head;
    struct Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}

int main() {
    struct Node* head = NULL;
    int choice, data, value;

    while (1) {
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Delete a node\n");
        printf("4. Linear search\n");
        printf("5. Display the list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;
            case 2:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 3:
                printf("Enter the value of the node to delete: ");
                scanf("%d", &value);
                deleteNode(&head, value);
                break;
            case 4:
                printf("Enter the element to search: ");
                scanf("%d", &value);
                linearSearch(head, value);
                break;
            case 5:
                displayList(head);
                break;
            case 6:
                freeList(&head);
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
