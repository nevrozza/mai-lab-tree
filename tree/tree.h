//
// Created by Артём on 12.03.2026.
//

#ifndef TREE_H
#define TREE_H

typedef struct {
    int value;
    struct Node *firstChild, *nextBrat;
} Node;

Node *createNode(int value);

Node *getByPath(Node *root, const char *path);

void addNode(Node *parent, const Node *newNode);

void deleteNode(Node *node);

void printTreeDirectoryType(const Node *root);

void printTreePretty(const Node *root);

#endif //TREE_H
