#include "tree.h"
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
    queNode *current = q->head;
    queNode *previous = NULL;
    queNode *highestPrior = current;

    queNode *lowestPrior1 = NULL;
    queNode *lowestPrior2 = NULL;

    while(current->next != NULL){  // Dopóki wielkość kolejki nie jest równa 1

        while(current != NULL){ // Dopóki nie dojdzie do końca kolejki
            if(current->prior < highestPrior->prior){
                highestPrior = current;
                lowestPrior2 = lowestPrior1;
                lowestPrior1 = current;
            }
            else if (lowestPrior2 == NULL || current->prior < lowestPrior2->prior) {
            lowestPrior2 = current;
            }

            current = current->next;
        }

        // połącz dwa drzewa (first i second) w nowe drzewo
        // usuń dwa elementy (drzewa) z kolejki
        // wstaw nowy element (drzewo) do kolejki

        // wróć na początek kolejki
        current = q->head;
    }
}

// Inicjuje rekursywną funkcję wyświetlającą zawartość drzewa
void printTree(treeNode *root){
    printTreeRec(root, 0);
}

