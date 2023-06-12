#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LEVEL 100
typedef struct Node {
    int value;
    struct Node** forward;
} Node;
typedef struct SkipList {
    int level;
    Node* header;
} SkipList;
Node* createNode(int value, int level) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->forward = (Node**)malloc((level + 1) * sizeof(Node*));
    for (int i = 0; i <= level; ++i) {
        newNode->forward[i] = NULL;
    }
    return newNode;
}
int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}
SkipList* createSkipList() {
    SkipList* skipList = (SkipList*)malloc(sizeof(SkipList));
    skipList->level = 0;
    skipList->header = createNode(0, MAX_LEVEL);
    return skipList;
}
void insert(SkipList* skipList, int value) {
    Node* update[MAX_LEVEL + 1];
    Node* current = skipList->header;
    for (int i = skipList->level; i >= 0; --i) {
        while (current->forward[i] != NULL && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
    if (current == NULL || current->value != value) {
        int newLevel = randomLevel();
        if (newLevel > skipList->level) {
            for (int i = skipList->level + 1; i <= newLevel; ++i) {
                update[i] = skipList->header;
            }
            skipList->level = newLevel;
        }
        Node* newNode = createNode(value, newLevel);

        for (int i = 0; i <= newLevel; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}
bool search(SkipList* skipList, int value) {
    Node* current = skipList->header;
    for (int i = skipList->level; i >= 0; --i) {
        while (current->forward[i] != NULL && current->forward[i]->value < value) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    return (current != NULL && current->value == value);
}
void printSkipList(SkipList* skipList) {
    for (int i = skipList->level; i >= 0; --i) {
        Node* current = skipList->header->forward[i];
        printf("Level %d: ", i);
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->forward[i];
        }
        printf("\n");
    }
}
int main() {
    SkipList* skipList = createSkipList();
    int choice;
    int value;
    bool running = true;
    while (running) {
        printf("\nSkip List Operations:\n");
        printf("1. Insert a value\n");
        printf("2. Search for a value\n");
        printf("3. Print the skip list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insert(skipList, value);
                printf("Value inserted successfully.\n");
                break;
            case 2:
                printf("Enter the value to search: ");
                scanf("%d", &value);
                if (search(skipList, value)) {
                    printf("Value %d found in the skip list.\n", value);
                } else {
                    printf("Value %d not found in the skip list.\n", value);
                }
                break;
            case 3:
                printf("Skip List:\n");
                printSkipList(skipList);
                break;
            case 4:
                running = false;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
