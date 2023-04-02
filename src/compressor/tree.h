// W tym pliku znajduje się struktura drzewa i prototypy funkcji na drzewie

#ifndef TREE_H
#define TREE_H

#include "queue.h"

struct queue;

typedef struct treeNode{
    unsigned char c;
    int is_leaf;
    int count;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

void get_char(treeNode*, unsigned char*** dict, int);
treeNode *makeTreeNode(unsigned char, int);
treeNode *joinNodes(treeNode*, treeNode*);
treeNode *makeTree(struct queue* q);
void printTree(treeNode*);
void freeTree(treeNode*);

#endif