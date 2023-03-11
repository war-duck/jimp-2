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

// łączy 2 węzły w jeden
treeNode *joinNodes(treeNode *first, treeNode *second){
    treeNode *newNode = malloc(sizeof *newNode);
    if(newNode == NULL)
        return NULL;
    
    newNode->c = -1;    // oznaczenie, że nowy węzeł nie zawiera żadnego znaku
                        // znaki zawierają jedynie liście drzewa
    newNode->count = first->count + second->count;
    newNode->left = first;
    newNode->right = second;

    return newNode;
}