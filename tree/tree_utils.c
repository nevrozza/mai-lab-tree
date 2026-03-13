//
// Created by Артём on 13.03.2026.
//

#include "tree_utils.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PathResult getByPath(Node *root, const char *pathOriginal) {
    const PathResult errorReturn = {NULL, NULL};
    if (root == NULL || pathOriginal == NULL) return errorReturn;

    if (strcmp(pathOriginal, "root") == 0 || strcmp(pathOriginal, "root/") == 0
        || strcmp(pathOriginal, ".") == 0 || strcmp(pathOriginal, "./") == 0) {
        return (PathResult){NULL, root};
    }

    char *path = strdup(pathOriginal);
    if (path == NULL) {
        memoryError();
        return errorReturn;
    }


    Node *current = root;
    Node *parent = NULL;

    char *token = strtok(path, "/");


    // skip root
    if (strcmp(token, "root") == 0 || strcmp(token, ".") == 0) {
        token = strtok(NULL, "/");
    }

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

void deleteTreeComplexly(const PathResult pathResult) {
    unboundNode(pathResult.from, pathResult.target);
    deleteTree(pathResult.target);
}

// internal fun uses only for printTree
void downPrint(Node *node, void *context) {
    int *depth = context;

    (*depth)++;

    for (int i = 0; i < *depth; i++) printf("  ");
    printf("- %d\n", node->value);
}

// internal fun uses only for printTree
void sidePrint(Node *node, void *context) {
    int *depth = context;

    for (int i = 0; i < *depth; i++) printf("  ");
    printf("- %d\n", node->nextBrat->value);
}

// internal fun uses only for printTree
void upPrint(Node *_, void *context) {
    int *depth = context;
    (*depth)--;
}

void printTreeDirectory(Node *root) {
    if (root == 0) return;
    printf("- root\n");
    int depth = 0;
    traversePostOrder(root, downPrint, sidePrint, upPrint, &depth);
}

int nodeDegree(Node *node) {
    int degree = 0;
    Node *child = node->firstChild;
    while (child) {
        degree++;
        child = child->nextBrat;
    }
    return degree;
}

// internal fun for countNodeDegreeEqValue
void countUp_CountNodeDegreeEqValue(Node *node, void *context) {
    int *count = context;
    if (nodeDegree(node) == node->value) {
        (*count)++;
    }
}

int countNodesDegreeEqValue(Node *root) {
    if (root == NULL) return 0;
    int count = 0;
    traversePostOrder(root, NULL, NULL, countUp_CountNodeDegreeEqValue, &count);
    return count;
}

void initSampleTree(Node *root) {
    Node *n1 = createNode(1);
    Node *n2 = createNode(2);
    addNode(root, n1);
    addNode(root, n2);

    // Node *n1 = addNode(z).target;
    // Node *n2 = getByPath(root, "2").target;

    if (n1 != NULL) {
        Node *n3 = createNode(3);
        addNode(n1, n3);
        addNode(n1, createNode(4));

        addNode(n3, createNode(6));
    }
    if (n2 != NULL) {
        addNode(n2, createNode(3));
        addNode(n2, createNode(4));
    }
}
