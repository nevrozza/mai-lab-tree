#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include <stddef.h>

#include "../tree/tree.h"

typedef enum {
    NODE_NEW, // Смешарик
    NODE_CHILDREN_PROCESSED, // Дети были добавлены в стек
    NODE_PROCESSED // Братья тоже были добавлены – можно удалять и делать `up`
} NodeState;

typedef struct {
    Node *node;
    NodeState state;
} DataType;

typedef struct Stack Stack;


Stack *stackCreate(void);

void stackDestroy(Stack *s);

bool stackIsEmpty(const Stack *s);

size_t stackSize(const Stack *s);

void stackPush(Stack *s, DataType item);

DataType stackPop(Stack *s);

DataType stackPeek(const Stack *s);

// void stackPrint(const Stack *s);

#endif //STACK_H
