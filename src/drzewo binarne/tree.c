#include "tree.h"
#include <stdlib.h>

// tworzy węzeł
treeNode *addNode(char c, int num){
    treeNode *node = malloc(sizeof *node);
    if(node != NULL){
        node->c = c;
        node->count = num;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}