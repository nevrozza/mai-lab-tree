//
// Created by Артём on 13.03.2026.
//

#ifndef TREE_UTILS_H
#define TREE_UTILS_H
#include "tree.h"

typedef struct {
    Node *from;
    Node *target;
} PathResult;

// path НЕ будет изменён!!
// сделано для удобных тестов
PathResult getByPath(Node *root, const char *pathOriginal);

void deleteTreeComplexly(PathResult pathResult);

void printTreeDirectory(Node *root);

int nodeDegree(Node *node);

int countNodesDegreeEqValue(Node *root);

void initSampleTree(Node *root);

#endif //TREE_UTILS_H
