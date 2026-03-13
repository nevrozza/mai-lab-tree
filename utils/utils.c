//
// Created by nevrozq on 25.12.2025.
//

#include <stdio.h>
#include <stdlib.h>

void error(char msg[]) {
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

void memoryError() {
    error("MemoryError");
}
