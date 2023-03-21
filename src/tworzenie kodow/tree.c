// Ten plik zawiera implementację drzewa binarnego

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

// Tworzy węzeł drzewa
treeNode *makeTreeNode(unsigned char c, int num){
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

void get_char(treeNode *tree, char** dict[2], int index){
    dict[0][index] = malloc(sizeof *(dict[0][index]));
    dict[0][index][0] = tree->c;
}

// łączy 2 węzły drzewa w jeden
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

treeNode *makeTree(struct queue *q){

    treeNode *lowestPrior1 = NULL;
    treeNode *lowestPrior2 = NULL;

    while(q->head->next != NULL){   // Dopóki w kolejce są min 2 elementy
        lowestPrior1 = q->head->tree;
        lowestPrior2 = q->head->next->tree;
        // Połącz 2 elementy kolejki o najmniejszym priorytecie
        treeNode *newTree = joinNodes(lowestPrior1, lowestPrior2);
        moveQueue(q);
        addToQue(q, newTree);
    }

    return q->head->tree;
}

// Rekursywnie wyświetla zawartość węzła
static void printTreeRec(treeNode *node, int level){

    if(node == NULL){
        printTabs(level);
        printf("<pusty>\n");
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

// Inicjuje rekursywną funkcję wyświetlającą zawartość drzewa
void printTree(treeNode *root){
    printTreeRec(root, 0);
}

