// Ten plik testuje poprawnie działającą kolejkę priorytetową

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    // Stwórz 7 testowych węzłów drzewa
    treeNode *a = addNode('a', 13);
    treeNode *b = addNode('b', 10);
    treeNode *c = addNode('c', 17);
    treeNode *d = addNode('d', -5);
    treeNode *e = addNode('e', 22);
    treeNode *f = addNode('f', 1);
    treeNode *g = addNode('g', 1000);
    treeNode *h = addNode('h', -5);
    
    // Zainicjuj kolejkę
    queue *q = initQue();
    addToQue(q, a->count, a);
    addToQue(q, b->count, b);
    addToQue(q, c->count, c);
    addToQue(q, d->count, d);
    addToQue(q, e->count, e);
    addToQue(q, f->count, f);
    addToQue(q, g->count, g);
    addToQue(q, h->count, h);

    printf("Queue: ");    

    while(q->head != NULL){
        printf("%d ",q->head->prior);
        q->head = q->head->next;
        //free(q->head);
    }

    return 0;
}