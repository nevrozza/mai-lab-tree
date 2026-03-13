//
// Created by Артём on 12.03.2026.
//

#ifndef TREE_H
#define TREE_H


typedef struct Node {
    int value;
    struct Node *firstChild, *nextBrat;
} Node;

typedef void (*Fun)(Node *, void *);

Node *createNode(int value);


void addNode(Node *parent, Node *newNode);

// Нельзя удалять ноду в down!!
// release, т.к. вызывается после "обработки ноды", т.е. сначала был проход слева-направо (side),
// а потом справа-налево (release – отпускаем элемент (его можно удалять))
void traversePostOrder(Node *root, Fun down, Fun side, Fun up, void *context);

void unboundNode(Node *from, Node *target);

void deleteTree(Node *root);


#endif //TREE_H
