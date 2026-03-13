//
// Created by Артём on 12.03.2026.
//

#include "cli.h"

#include <stddef.h>
#include <stdio.h>

#include "../tree/tree.h"
#include "../tree/tree_utils.h"


void WarnPathNotFound(char *path) {
    printf("Path '%s' not found!!\n", path);
}

void WarnEmptyTree() {
    printf("Tree is empty\n");
}

void addChildValueToPath(Node *root, char *path, int value) {
    if (root == NULL) {
        WarnEmptyTree();
        return;
    }

    PathResult res = getByPath(root, path);
    if (res.target == NULL) {
        WarnPathNotFound(path);
        return;
    }

    Node *newNode = createNode(value);
    if (newNode == NULL) return;

    addNode(res.target, newNode);
    printf("Added %d to '%s'\n", value, path);
}

void deleteNodeByPath(Node *root, char *path) {
    PathResult res = getByPath(root, path);
    if (res.target == root) {
        printf("I don't think that delete root it's good idea 0_o\n", path);
    }

    if (root == NULL || root->firstChild == NULL) {
        WarnEmptyTree();
        return;
    }

    if (res.target == NULL) {
        WarnPathNotFound(path);
        return;
    }

    deleteTreeComplexly(res);
    printf("Deleted '%s'\n", path);
}

void printTree(Node *root) {
    if (root == NULL || root->firstChild == NULL) {
        WarnEmptyTree();
        return;
    }

    printTreeDirectory(root);
}

void solve(Node *root) {
    if (root == NULL || root->firstChild == NULL) {
        WarnEmptyTree();
        return;
    }

    int count = countNodesDegreeEqValue(root);
    printf("Количество вершин, где степень == значению элемента: %d\n", count);
}
