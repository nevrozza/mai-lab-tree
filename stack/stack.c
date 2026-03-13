#include "stack.h"
#include "../utils/utils.h"

#include <stdlib.h>

#define INITIAL_CAPACITY 4

struct Stack {
    DataType *data;
    size_t capacity;
    size_t count;
};

Stack *stackCreate(void) {
    Stack *s = malloc(sizeof(Stack));
    DataType *data = malloc(INITIAL_CAPACITY * sizeof(DataType));

    if (s == NULL || data == NULL) {
        memoryError();
        return NULL; // suppress IDE
    }

    s->data = data;
    s->capacity = INITIAL_CAPACITY;
    s->count = 0;

    return s;
}

void stackDestroy(Stack *s) {
    if (s != NULL) {
        free(s->data);
        free(s);
    }
}

static void stackRealloc(Stack *s, size_t new_capacity) {
    DataType *new_data = realloc(s->data, new_capacity * sizeof(DataType));

    if (new_data == NULL) { memoryError(); }

    s->data = new_data;
    s->capacity = new_capacity;
}

bool stackIsEmpty(const Stack *s) {
    return s->count == 0;
}

size_t stackSize(const Stack *s) {
    return s->count;
}

void stackPush(Stack *s, DataType item) {
    if (s->count == s->capacity) {
        stackRealloc(s, s->capacity * 2);
    }
    s->data[s->count++] = item;
}

DataType stackPop(Stack *s) {
    if (stackIsEmpty(s)) { error("Stack is empty"); }
    return s->data[--s->count];
}

DataType stackPeek(const Stack *s) {
    if (stackIsEmpty(s)) { error("Stack is empty"); }
    return (s->data[s->count - 1]);
}

// void stack_print(const Stack *s) {
//     if (stack_is_empty(s)) {
//         printf("[]\n");
//         return;
//     }
//
//     printf("[");
//     for (size_t i = 0; i < s->count; i++) {
//         if (i > 0) printf(", ");
//         printf("%d", s->data[i].node->value);
//     }
//     printf("]  <-- вершина\n");
// }
