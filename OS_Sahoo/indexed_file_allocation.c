#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_BLOCKS 10

// Structure to represent a file block
struct Block {
    char data[MAX_NAME_LENGTH];
};

// Structure to represent a directory or file
struct Node {
    char name[MAX_NAME_LENGTH];
    int index[MAX_BLOCKS];
    int numBlocks;
    struct Node* child;
    struct Node* sibling;
};

// Function to create a new node (directory or file)
struct Node* createNode(const char* name) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        strncpy(newNode->name, name, MAX_NAME_LENGTH - 1);
        newNode->name[MAX_NAME_LENGTH - 1] = '\0';
        newNode->numBlocks = 0;
        newNode->child = NULL;
        newNode->sibling = NULL;
    }
    return newNode;
}

// Function to create a directory or file in the hierarchy
void createItem(struct Node* parent, const char* name) {
    struct Node* newItem = createNode(name);
    if (newItem == NULL) {
        printf("Memory allocation failed for %s\n", name);
        exit(EXIT_FAILURE);
    }

    newItem->sibling = parent->child;
    parent->child = newItem;
}

// Function to allocate a block to a file
void allocateBlock(struct Node* file, const char* data) {
    if (file->numBlocks < MAX_BLOCKS) {
        // Simulating index allocation
        file->index[file->numBlocks] = file->numBlocks;
        ++file->numBlocks;

        // Simulating block allocation
        strncpy(file->child->name, data, MAX_NAME_LENGTH - 1);
        file->child->name[MAX_NAME_LENGTH - 1] = '\0';
    } else {
        printf("File %s is full. Cannot allocate more blocks.\n", file->name);
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

        if (root->numBlocks > 0) {
            for (i = 0; i <= depth; ++i) {
                printf("  "); // Indentation for file blocks
            }
            printf("|-- Blocks: ");
            for (i = 0; i < root->numBlocks; ++i) {
                printf("%d ", root->index[i]);
            }
            printf("\n");
        }

        displayTree(root->child, depth + 1);
        displayTree(root->sibling, depth);
    }
}

int main() {
    struct Node* root = createNode("Root");

    int choice;
    do {
        printf("\n1. Create Directory\n2. Create File\n3. Allocate Block\n4. Display Hierarchy\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[MAX_NAME_LENGTH];
                printf("Enter directory name: ");
                scanf("%s", name);
                createItem(root, name);
                break;
            }
            case 2: {
                char name[MAX_NAME_LENGTH];
                printf("Enter file name: ");
                scanf("%s", name);
                createItem(root, name);
                break;
            }
            case 3: {
                char data[MAX_NAME_LENGTH];
                printf("Enter data for block: ");
                scanf("%s", data);
                allocateBlock(root->child, data);
                break;
            }
            case 4:
                printf("File System Hierarchy:\n");
                displayTree(root, 0);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    // Free allocated memory (not included in this simple example for brevity)
    // In a real-world scenario, you should free the memory when the program exits.

    return 0;
}
