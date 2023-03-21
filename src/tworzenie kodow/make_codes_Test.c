#include "make_codes.h"
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

    printf("size: %d\n", q->size);
    char ***dict;
    dict = malloc(2 * sizeof(char**));
    dict[0] = malloc(8 * sizeof(char*));
    dict[1] = malloc(8 * sizeof(char*));
    for(int i = 0; i < 8; i++){
        // dict[0][i] = malloc(20 * sizeof (char));
        //dict[1][i] = malloc(20 * sizeof (char));
    }

    make_codes(root, q->size, dict);
    for(int i = 0; i < q->size; i++)
        printf("%s - %s\n", dict[0][i], dict[1][i]);

    free(q->head);
    free(q);
    free(dict[0]);
    free(dict[1]);

    return 0;
}