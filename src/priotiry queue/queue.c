#include "queue.h"
#include <stdlib.h>

int isEmpty(queue *q){
    return q->head == NULL;
}

queue *initQue(){
    queue *newQue = malloc(sizeof *newQue);
    if (newQue != NULL){
        newQue->head = NULL;
        newQue->tail = NULL;
    }
    return newQue;
}

void *addToQue(queue *q, int prior, treeNode *tree){
    queNode *newNode = malloc(sizeof *newNode);
    if(newNode == NULL)
        return NULL;
    
    newNode->prior = prior;

    // TO-DO wpisywanie nodea w zależności od isEmpty i innych nodeów (jeżeli są w niej elementy)
    if(isEmpty(q)){
        q->head = newNode;
        q->tail = newNode;
        return;
    }
}