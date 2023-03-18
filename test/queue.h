// W tym pliku znajduje się struktura Priority Queue i prototypy funkcji

#ifndef QUEUE_H
#define QUEUE_H
#include "tree.h"


typedef struct queNode{    // Struktura pojedynczego elementu w kolejce
    struct queNode *next;
    treeNode *value;       // Kolejka zawiera poszczególne drzewa, w których są zapisane symbole
    int prior;             // Priorytet = liczba wystąpień danego znaku
} queNode;

typedef struct queue{      // Struktura "kolejki" - ma wskaźniki na początek i koniec
    queNode *head;
    queNode *tail;
} queue;

queue *initQue();
void addToQue(queue*, treeNode*);
int isEmpty();
void moveQueue(queue*);
#endif