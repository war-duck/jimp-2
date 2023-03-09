#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    // Stwórz 7 testowe węzły drzewa
    printf("a");
    treeNode *a = addNode('a', 13);
    printf("b");
    treeNode *b = addNode('b', 10);
    printf("c");
    treeNode *c = addNode('c', 17);
    printf("d");
    treeNode *d = addNode('d', -5);
    treeNode *e = addNode('e', 22);
    treeNode *f = addNode('f', 1);
    treeNode *g = addNode('g', 1000);
    // Zainicjuj kolejkę
    queue *q = initQue();
    addToQue(q, a->count, a);
    addToQue(q, b->count, b);
    addToQue(q, c->count, c);
    addToQue(q, d->count, d);
    addToQue(q, e->count, e);
    addToQue(q, f->count, f);
    addToQue(q, g->count, g);

    printf("Queue: ");    

    while(q->head != NULL){
        printf("%d ",q->head->prior);
        q->head = q->head->next;
        //free(q->head);
    }

    return 0;
}