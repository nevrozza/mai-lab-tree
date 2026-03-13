#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslimits.h>

#include "cli/cli.h"
#include "tree/tree.h"
#include "tree/tree_utils.h"
#include "utils/utils.h"


void printHelp() {
    printf("Команды:\n");
    printf("  sample               - заменить корень на заранее готовое дерево\n");
    printf("  add <path> <value>   - добавить узел с value по пути\n");
    printf("  del <path>           - удалить узел по пути\n");
    printf("  print                - печать дерева\n");
    printf("  solve                - подсчет узлов, где степень == value\n");
    printf("  exit                 - выход\n");
}

int main(void) {
    Node *root = createNode(0); // корень дерева
    if (root == NULL) {
        memoryError();
        return 1;
    }

    char input[1024];

    printHelp();

    while (true) {
        printf(">>> ");

        scanf("%1023s", input);

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strcmp(input, "add") == 0) {
            char path[1024];
            int value;
            scanf("%1000s %d", path, &value);

            addChildValueToPath(root, path, value);
        } else if (strcmp(input, "del") == 0) {
            char path[1024];
            scanf("%1000s", path);

            deleteNodeByPath(root, path);
        } else if (strcmp(input, "print") == 0) {
            printTree(root);
        } else if (strcmp(input, "solve") == 0) {
            solve(root);
        } else if (strcmp(input, "sample") == 0) {
            deleteTree(root);
            root = createNode(0);
            initSampleTree(root);
        } else if (strcmp(input, "help") == 0) {
            printHelp();
        } else {
            printf("Такой команды нет – введите 'help', чтобы вывести список команд\n");
        }
    }

    return 0;
}
