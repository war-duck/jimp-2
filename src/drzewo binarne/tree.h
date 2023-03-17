// W tym pliku znajduje się struktura drzewa i prototypy funkcji na drzewie

#ifndef TREE_H
#define TREE_H

#include "..\priotiry queue\queue.h"

typedef struct treeNode{
    unsigned char c;
    int is_leaf;
    int count;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

treeNode *addNode(unsigned char, int);
treeNode *joinNodes(treeNode*, treeNode*);
treeNode *makeTree(queNode*);
void printTree(treeNode*);

#endif