//
// Created by Артём on 12.03.2026.
//

#ifndef CLI_H
#define CLI_H
#include <stdbool.h>

#include "../tree/tree.h"

void addChildValueToPath(Node *root, const char *path, int value);

void deleteNodeByPath(Node *root, const char *path);

void printTree(Node *root, bool pretty);

// Определить число вершин дерева, степень которых совпадает со значением элемента.
void solve(Node *root);

#endif //CLI_H
