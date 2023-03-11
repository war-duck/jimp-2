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
    addToQue(q, a);
    addToQue(q, b);
    addToQue(q, c);
    addToQue(q, d);
    addToQue(q, e);
    addToQue(q, f);
    addToQue(q, g);
    addToQue(q, h);

    printf("Queue: ");    

    while(q->head != NULL){
        printf("%d ",q->head->prior);
        q->head = q->head->next;
        //free(q->head);
    }

    return 0;
}