#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
// tworzy węzeł
treeNode *addNode(char c, int num){
    treeNode *node = malloc(sizeof *node);
    if(node != NULL){
        node->c = c;
        node->count = num;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

// łączy 2 węzły w jeden
treeNode *joinNodes(treeNode *first, treeNode *second){
    treeNode *newNode = malloc(sizeof *newNode);
    if(newNode == NULL)
        return NULL;
    
    newNode->c = -1;    // oznaczenie, że nowy węzeł nie zawiera żadnego znaku
                        // znaki zawierają jedynie liście drzewa
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
    printf("char: %d\n", node->c);
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

