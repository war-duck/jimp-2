// W tym pliku znajduje się struktura drzewa i prototypy funkcji na drzewie

#ifndef TREE_H
#define TREE_H

typedef struct treeNode{
    char c;
    int count;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

treeNode *addNode(char, int);

#endif