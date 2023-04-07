// W tym pliku znajduje się struktura drzewa i prototypy funkcji na drzewie

#ifndef TREE_H
#define TREE_H

typedef unsigned char uchar;
typedef struct treeNode{
    uchar c;
    int is_leaf;
    struct treeNode *offspring[2];
} treeNode;

void get_char(treeNode*, uchar*** dict, int);
treeNode *makeTreeNode(uchar, int is_leaf);
treeNode *joinNodes(treeNode*, treeNode*);
void printTree(treeNode*);
void freeTree(treeNode*);
void printTabs(int level);
int addCharCode(treeNode* tree, uchar c, uchar* code, int len, int byte_pos);
uchar get_bit (uchar code, int byte_pos);

#endif