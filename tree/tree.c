//
// Created by Артём on 12.03.2026.
//

#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/utils.h"
#include "../stack/stack.h"

Node *createNode(const int value) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        memoryError();
        return NULL;
    }

    newNode->value = value;
    newNode->firstChild = NULL;
    newNode->nextBrat = NULL;
    return newNode;
}

PathResult getByPath(Node *root, const char *pathOriginal) {
    const PathResult errorReturn = {NULL, NULL};
    if (root == NULL || pathOriginal == NULL) return errorReturn;

    char *path = strdup(pathOriginal);
    if (path == NULL) {
        memoryError();
        return errorReturn;
    }

    Node *current = root;
    Node *parent = NULL;

    char *token = strtok(path, "/");

    while (token) {
        int targetValue = 0, targetNumber = 1;
        char *quote = strchr(token, '\'');
        if (quote) {
            *quote = '\0';
            targetValue = atoi(token);
            targetNumber = atoi(quote + 1);
        } else {
            targetValue = atoi(token);
        }

        Node *child = current->firstChild;
        Node *prev = NULL;
        int count = 0;
        Node *found = NULL;

        while (child) {
            if (child->value == targetValue) {
                count++;
                if (count == targetNumber) {
                    found = child;
                    break;
                }
            }
            prev = child;
            child = child->nextBrat;
        }

        if (found == NULL) {
            free(path);
            return errorReturn;
        }

        parent = current;

        if (found != current->firstChild) { parent = prev; }

        current = found;
        token = strtok(NULL, "/");
    }

    free(path);
    return (PathResult){parent, current};
}

void addNode(Node *parent, Node *newNode) {
    if (parent == NULL || newNode == NULL) return;

    if (parent->firstChild == NULL) {
        parent->firstChild = newNode;
    } else {
        Node *prevBrat = parent->firstChild;
        while (prevBrat->nextBrat != NULL) {
            prevBrat = prevBrat->nextBrat;
        }
        prevBrat->nextBrat = newNode;
    }
}

// internal fun uses only for traversePostOrder
void updateCopiedStackItem(Stack *stack, DataType item) {
    stackPop(stack);
    stackPush(stack, item);
}

void traversePostOrder(Node *root, const Fun down, const Fun side, const Fun up, void *context) {
    if (root == NULL) { return; }

    Stack *s = stackCreate();
    stackPush(s, (DataType){root, NODE_NEW});

    while (!stackIsEmpty(s)) {
        const DataType item = stackPeek(s); // не указатель
        Node *node = item.node;


        if (node->firstChild != NULL && item.state == NODE_NEW) {
            updateCopiedStackItem(s, (DataType){node, NODE_CHILDREN_PROCESSED});

            stackPush(s, (DataType){node->firstChild, NODE_NEW});
            if (down != NULL) down(node->firstChild, context);
        } else if (node->nextBrat != NULL && item.state != NODE_PROCESSED) {
            updateCopiedStackItem(s, (DataType){node, NODE_PROCESSED});

            stackPush(s, (DataType){node->nextBrat, NODE_NEW});
            if (side != NULL) side(node->nextBrat, context);
        } else {
            stackPop(s);
            if (up != NULL) { up(node, context); }
        }
    }
    stackDestroy(s);
}

void unboundNode(Node *from, Node *target) {
    if (from == NULL) return;

    if (target == NULL) return;

    if (from->firstChild == target) {
        from->firstChild = target->nextBrat;
    } else {
        from->nextBrat = target->nextBrat;
    }

    target->nextBrat = NULL;
}

// internal fun uses only for deleteNode
void freeNode(Node *node, void *_) {
    if (node != NULL) {
        free(node);
    }
}

void deleteTree(Node *root) {
    traversePostOrder(root, NULL, NULL, freeNode, NULL);
}

void deleteTreeComplexly(const PathResult pathResult) {
    unboundNode(pathResult.from, pathResult.target);
    deleteTree(pathResult.target);
}

// internal fun uses only for printTree
void downPrint(Node *node, void *context) {
    int *depth = context;
    for (int i = 0; i < *depth; i++) printf("  ");
    printf("- %d\n", node->value);
    (*depth)++; // Теперь мы на уровне глубже
}

// internal fun uses only for printTree
void sidePrint(Node *node, void *context) {
    int *depth = context;
    for (int i = 0; i < (*depth) - 1; i++) printf("  ");
    printf("- %d\n", node->value);
}

// internal fun uses only for printTree
void upPrint(Node *_, void *context) {
    int *depth = context;
    (*depth)--;
}

void printTreeDirectory(Node *root) {
    if (root == 0) return;
    printf("- %d\n", root->value);
    int depth = 1;
    traversePostOrder(root, downPrint, sidePrint, upPrint, &depth);
}
