#include "tree.h"
#include "../priotiry queue/queue.h"
#include <stdlib.h>
#include <stdio.h>

// tworzy węzeł
treeNode *addNode(unsigned char c, int num){
    treeNode *node = malloc(sizeof *node);
    if(node != NULL){
        node->c = c;
        node->count = num;
        node->left = NULL;
        node->right = NULL;
        node->is_leaf = 1;
    }
    return node;
}

// łączy 2 węzły w jeden
treeNode *joinNodes(treeNode *first, treeNode *second){
    treeNode *newNode = malloc(sizeof *newNode);
    if(newNode == NULL)
        return NULL;
    
    newNode->c = 0;     
    newNode->is_leaf = 0;   // Oznaczenie, że nowy węzeł nie jest liściem
    newNode->count = first->count + second->count;
    newNode->left = first;
    newNode->right = second;

    return newNode;
}

// Wypisuje odpowiednią ilość tabów
static void printTabs(int level){
    for(int i = 0; i < level; i++)
        printf("\t");
}

// Rekursywnie wyświetla zawartość węzła
static void printTreeRec(treeNode *node, int level){
    if(node == NULL){
        printTabs(level);
        printf("<empty>\n");
        return;
    }
    printTabs(level);
    if(node->is_leaf)
        printf("znak: [%c]\n", node->c);
    else   
        printf("<wezel>\n");
    printTabs(level);
    printf("count: %d\n", node->count);
    printTabs(level);
    printf("left:\n");
    printTreeRec(node->left, level+1);
    printTabs(level);
    printf("right:\n");
    printTreeRec(node->right, level+1);
}

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

// Inicjuje rekursywną funkcję wyświetlającą zawartość drzewa
void printTree(treeNode *root){
    printTreeRec(root, 0);
}

