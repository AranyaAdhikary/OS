#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Structure to represent a file or directory
struct Node {
    char name[MAX_NAME_LENGTH];
    struct Node* child;
    struct Node* sibling;
};

// Function to create a new node (file or directory)
struct Node* createNode(const char* name) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        strncpy(newNode->name, name, MAX_NAME_LENGTH - 1);
        newNode->name[MAX_NAME_LENGTH - 1] = '\0';
        newNode->child = NULL;
        newNode->sibling = NULL;
    }
    return newNode;
}

// Function to create a directory or file in the hierarchy
void createItem(struct Node* parent, const char* name, int isDirectory) {
    struct Node* newItem = createNode(name);
    if (newItem == NULL) {
        printf("Memory allocation failed for %s\n", name);
        exit(EXIT_FAILURE);
    }

    if (isDirectory) {
        newItem->sibling = parent->child;
        parent->child = newItem;
    } else {
        struct Node* current = parent->child;
        if (current == NULL) {
            parent->child = newItem;
        } else {
            while (current->sibling != NULL) {
                current = current->sibling;
            }
            current->sibling = newItem;
        }
    }
}

// Function to display the hierarchy as a tree
void displayTree(struct Node* root, int depth) {
    if (root != NULL) {
        int i;
        for (i = 0; i < depth; ++i) {
            printf("  "); // Indentation for hierarchy visualization
        }
        printf("|-- %s\n", root->name);
        displayTree(root->child, depth + 1);
        displayTree(root->sibling, depth);
    }
}

int main() {
    struct Node* root = createNode("Root");

    int choice;
    do {
        printf("\n1. Create Directory\n2. Create File\n3. Display Hierarchy\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[MAX_NAME_LENGTH];
                printf("Enter directory name: ");
                scanf("%s", name);
                createItem(root, name, 1);
                break;
            }
            case 2: {
                char name[MAX_NAME_LENGTH];
                printf("Enter file name: ");
                scanf("%s", name);
                createItem(root, name, 0);
                break;
            }
            case 3:
                printf("File System Hierarchy:\n");
                displayTree(root, 0);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    // Free allocated memory (not included in this simple example for brevity)
    // In a real-world scenario, you should free the memory when the program exits.

    return 0;
}
