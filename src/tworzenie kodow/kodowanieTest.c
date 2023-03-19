#include "kodowanie.h"
#include "queue.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    // Stwórz 7 testowych węzłów drzewa
    treeNode *a = makeTreeNode('a', 13);
    treeNode *b = makeTreeNode('b', 10);
    treeNode *c = makeTreeNode('c', 17);
    treeNode *d = makeTreeNode('d', 5);
    treeNode *e = makeTreeNode('e', 22);
    treeNode *f = makeTreeNode('f', 1);
    treeNode *g = makeTreeNode('g', 1000);
    treeNode *h = makeTreeNode('h', 5);
    
    // Zainicjuj kolejkę
    queue *q = initQue();
    addToQue(q, a);
    addToQue(q, b);
    addToQue(q, c);
    addToQue(q, d);
    addToQue(q, e);
    addToQue(q, f);
    addToQue(q, g);
    addToQue(q, h);

    // Utwórz i wyświetl drzewo
    treeNode *root = makeTree(q);
    printTree(root);

    char **dict[2] = make_codes;

    free(q->head);
    free(q);
    free(dict[0]);
    free(dict[1]);

    return 0;
}