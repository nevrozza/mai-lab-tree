//
// Created by Артём on 12.03.2026.
//

#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

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

void traversePostOrderRelease(Node *root, const Fun down, const Fun side, const Fun release, void *context) {
    if (root == NULL) { return; }

    Stack *s = stackCreate();
    stackPush(s, (DataType){root, NODE_NEW});

    while (!stackIsEmpty(s)) {
        const DataType item = stackPeek(s); // не указатель
        Node *node = item.node;


        if (item.state == NODE_NEW) {
            updateCopiedStackItem(s, (DataType){node, NODE_CHILDREN_PROCESSED});
            if (node->firstChild != NULL) {
                stackPush(s, (DataType){node->firstChild, NODE_NEW});
                if (down != NULL) down(node->firstChild, context);
            }
        } else if (item.state == NODE_CHILDREN_PROCESSED) {
            updateCopiedStackItem(s, (DataType){node, NODE_PROCESSED});
            if (node->nextBrat != NULL) {
                stackPush(s, (DataType){node->nextBrat, NODE_NEW});
                if (side != NULL) side(node->nextBrat, context);
            }
        } else {
            stackPop(s);
            if (release != NULL) { release(node, context); }
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
    traversePostOrderRelease(root, NULL, NULL, freeNode, NULL);
}
