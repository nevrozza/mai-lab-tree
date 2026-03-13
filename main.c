#include <stdio.h>

#include "tree/tree.h"
#include "tree/tree_utils.h"

int main(void) {
    Node *root = createNode(2);
    addNode(root, createNode(1));
    addNode(root, createNode(2));
    addNode(root->firstChild, createNode(0));

    printTreeDirectory(root);
    int result = countNodesDegreeEqValue(root);
    printf("ans: %d", result);

    deleteTree(root);
    return 0;
}
