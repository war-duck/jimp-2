#include "makeTree.h"
#include <stdlib.h>
// Na podstawie priority queue tworzy pełne drzewo binarne
treeNode *makeTree(queue *q){

    treeNode *lowestPrior1 = NULL;
    treeNode *lowestPrior2 = NULL;

    while(q->head->next != NULL){   // Dopóki w kolejce są min 2 elementy
        lowestPrior1 = q->head->value;
        lowestPrior2 = q->head->next->value;
        treeNode *newTree = joinNodes(lowestPrior1, lowestPrior2);
        moveQueue(q);
        addToQue(q, newTree);
    }

    return q->head->value;
}
