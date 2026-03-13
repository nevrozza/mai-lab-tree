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
// down -> спуск глубже, указывает на первого ребёнка
// side –> проход по братьям слева-направо, начиная с 1 по предпоследний (важно: он указывает на node, а не node->nextBrat) !!!
// up -> поднятие вверх, указывает на последний элемент
void traversePostOrder(Node *root, Fun down, Fun side, Fun up, void *context);

void unboundNode(Node *from, Node *target);

void deleteTree(Node *root);


#endif //TREE_H
