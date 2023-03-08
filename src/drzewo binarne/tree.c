#include "tree.h"
#include <stdlib.h>

treeNode *addNode(char c){
    treeNode *node = malloc(sizeof node);
    if(node != NULL){
        node->c = c;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}