#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void initializeTree(TreeNode** root);
void insert(TreeNode** root, int data);
void deleteNode(TreeNode** root, int data); 
TreeNode* findMin(TreeNode* node);
void inOrderTraversal(TreeNode* root);
void preOrderTraversal(TreeNode* root);
void postOrderTraversal(TreeNode* root);
TreeNode* search(TreeNode* root, int data);

int binaryTree[MAX_SIZE];
int currentIndex = 0;

int main() {
    TreeNode* root = NULL;
    int choice, data;
    
    initializeTree(&root);
    
    while (1) {
        printf("\nBinary Tree Operations\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. In-order Traversal\n");
        printf("4. Pre-order Traversal\n");
        printf("5. Post-order Traversal\n");
        printf("6. Search\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to be inserted: ");
                scanf("%d", &data);
                insert(&root, data);
                break;
            case 2:
                printf("Enter data to be deleted: ");
                scanf("%d", &data);
                deleteNode(&root, data);
                break;
            case 3:
                printf("In-order Traversal: ");
                inOrderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Pre-order Traversal: ");
                preOrderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Post-order Traversal: ");
                postOrderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Enter data to be searched: ");
                scanf("%d", &data);
                if (search(root, data) != NULL)
                    printf("Element found in the tree.\n");
                else
                    printf("Element not found in the tree.\n");
                break;
            case 7:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

void initializeTree(TreeNode** root) {
    *root = NULL;
}

void insert(TreeNode** root, int data) {
    if (currentIndex == MAX_SIZE) {
        printf("Binary tree is full. Cannot insert more elements.\n");
        return;
    }
    
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    
    binaryTree[currentIndex] = data;
    
    if (*root == NULL) {
        *root = newNode;
    } else {
        int parentIndex = (currentIndex - 1) / 2;
        if (currentIndex % 2 == 0) {
            (*root)->right = newNode;
        } else {
            (*root)->left = newNode;
        }
    }
    
    currentIndex++;
}

void deleteNode(TreeNode** root, int data) {
    TreeNode* nodeToDelete = search(*root, data);
    if (nodeToDelete == NULL) {
        printf("Element not found in the tree.\n");
        return;
    }
    
    TreeNode* parent = NULL;
    TreeNode* current = *root;
    while (current != nodeToDelete) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (nodeToDelete->left == NULL && nodeToDelete->right == NULL) {
        if (parent == NULL) {
            *root = NULL;
        } else if (parent->left == nodeToDelete) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    }

    else if (nodeToDelete->left == NULL || nodeToDelete->right == NULL) {
        TreeNode* child = (nodeToDelete->left != NULL) ? nodeToDelete->left : nodeToDelete->right;
        
        if (parent == NULL) {
            *root = child;
        } else if (parent->left == nodeToDelete) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }

    else {
        TreeNode* successor = findMin(nodeToDelete->right);
        int successorData = successor->data;
        
        deleteNode(root, successorData);
        nodeToDelete->data = successorData;
    }
    
    free(nodeToDelete);
}

TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

void inOrderTraversal(TreeNode* root) {
    if (root == NULL)
        return;
    
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

void preOrderTraversal(TreeNode* root) {
    if (root == NULL)
        return;
    
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void postOrderTraversal(TreeNode* root) {
    if (root == NULL)
        return;
    
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}

TreeNode* search(TreeNode* root, int data) {
    if (root == NULL || root->data == data)
        return root;
    
    if (data < root->data)
        return search(root->left, data);
    
    return search(root->right, data);
}
