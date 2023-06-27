#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        struct Node* curr = *head;
        while (curr->next != *head) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->next = *head;
    }
    printf("Node with data %d inserted.\n", data);
}

void deleteNode(struct Node** head, int key) {
    if (*head == NULL) {
        printf("List is empty. Deletion failed.\n");
        return;
    }
    
    struct Node* curr = *head;
    struct Node* prev = NULL;
    while (curr->next != *head) {
        if (curr->data == key) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    
    if (curr->data != key) {
        printf("Node with data %d not found. Deletion failed.\n", key);
        return;
    }
    
    if (curr == *head && curr->next == *head) {
        *head = NULL;
        free(curr);
        printf("Node with data %d deleted.\n", key);
        return;
    }
    
    if (curr == *head) {
        while (curr->next != *head) {
            curr = curr->next;
        }
        *head = (*head)->next;
        curr->next = *head;
    } else {
        prev->next = curr->next;
    }
    
    free(curr);
    printf("Node with data %d deleted.\n", key);
}

void searchNode(struct Node* head, int key) {
    if (head == NULL) {
        printf("List is empty. Search failed.\n");
        return;
    }
    
    struct Node* curr = head;
    int position = 1;
    while (curr->next != head) {
        if (curr->data == key) {
            printf("Node with data %d found at position %d.\n", key, position);
            return;
        }
        curr = curr->next;
        position++;
    }
    
    if (curr->data == key) {
        printf("Node with data %d found at position %d.\n", key, position);
        return;
    }
    
    printf("Node with data %d not found.\n", key);
}

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    struct Node* curr = head;
    printf("Circular Linked List: ");
    do {
        printf("%d ", curr->data);
        curr = curr->next;
    } while (curr != head);
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data, key;
    
    while (1) {
        printf("\nCircular Linked List Operations:\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. Display List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the data to be inserted: ");
                scanf("%d", &data);
                insertNode(&head, data);
                break;
                
            case 2:
                printf("Enter the data to be deleted: ");
                scanf("%d", &key);
                deleteNode(&head, key);
                break;
                
            case 3:
                printf("Enter the data to be searched: ");
                scanf("%d", &key);
                searchNode(head, key);
                break;
                
            case 4:
                displayList(head);
                break;
                
            case 5:
                printf("Exiting...\n");
                exit(0);
                
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    
    return 0;
}
