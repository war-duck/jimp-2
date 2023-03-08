// W tym pliku znajduje się struktura Priority Queue i prototypy funkcji

#ifndef QUEUE_H
#define QUEUE_H

#include "../drzewo binarne/tree.h"

typedef struct queNode{    // struktura pojedynczego obiektu w całej kolejce
    struct queNode *next;
    treeNode *value;       // kolejka zawiera poszczególne drzewa, w których są zapisane symbole
    int prior;             // priorytet = liczba wystąpień danego znaku
} queNode;

typedef struct queue{      // struktura "kolejki" - ma wskaźniki na początek i koniec
    queNode *head;
    queNode *tail;
} queue;

queue *initQue();
void *addToQue(queue*, int, treeNode*);
int isEmpty();
// TO-DO isEmpty
#endif