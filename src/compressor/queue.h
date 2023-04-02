// W tym pliku znajduje się struktura Priority Queue i prototypy funkcji

#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"

struct treeNode;

typedef struct queNode{    // Struktura pojedynczego elementu w kolejce
    struct queNode *next;
    struct treeNode *tree; // Kolejka zawiera poszczególne drzewa, w których są zapisane symbole
    int prior;             // Priorytet = liczba wystąpień danego znaku
} queNode;

typedef struct queue{      // Struktura "kolejki" - ma wskaźniki na początek i koniec
    queNode *head;
    queNode *tail;
    int size;              // Liczba unikalnych znaków (liści drzewa)
} queue;

queue *initQue();
void addToQue(queue*, struct treeNode *tree);
void moveQueue(queue*);

#endif