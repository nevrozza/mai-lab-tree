//
// Created by Артём on 12.03.2026.
//

#ifndef TREE_H
#define TREE_H
#include <stdbool.h>


typedef struct Node {
    int value;
    struct Node *firstChild, *nextBrat;
} Node;

typedef struct {
    Node *from;
    Node *target;
} PathResult;

typedef void (*Fun)(Node *, void *);

Node *createNode(int value);

// path НЕ будет изменён!!
// сделано для удобных тестов
PathResult getByPath(Node *root, const char *pathOriginal);

void addNode(Node *parent, Node *newNode);

// Нельзя удалять ноду в down!!
void traversePostOrder(Node *root, Fun down, Fun side, Fun up, void *context);

void unboundNode(Node *from, Node *target);

void deleteTree(Node *root);

void deleteTreeComplexly(PathResult pathResult);

void printTreeDirectory(Node *root);


#endif //TREE_H
