// W tym pliku znajduje się struktura drzewa i prototypy funkcji na drzewie

#ifndef TREE_H
#define TREE_H


typedef struct treeNode{
    unsigned char c;
    int is_leaf;
    int count;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

treeNode *addNode(unsigned char, int);
treeNode *joinNodes(treeNode*, treeNode*);

void printTree(treeNode*);

#endif