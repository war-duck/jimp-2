// Ten plik zawiera implementację drzewa binarnego

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

// Tworzy węzeł drzewa
treeNode *makeTreeNode(unsigned char c, int is_leaf){
    treeNode *node = malloc(sizeof *node);
    if(node != NULL){
        node->c = c;
        node->offspring[0] = NULL;
        node->offspring[1] = NULL;
        node->is_leaf = is_leaf;
    }
    return node;
}

int addCharCode(treeNode* tree, unsigned char c, unsigned char* code, int len, int byte_pos) // tworzy odpowiednie galezie prowadzace do podanego c
{
    char bit_val = *code & (0x80 >> byte_pos);
    if (len > 0)
    {
        if (tree->offspring[bit_val] == NULL)
            tree->offspring[bit_val] = makeTreeNode('\0', 0);
        addCharCode(tree->offspring[bit_val], c, (byte_pos == 7) ? code + 1 : code, len - 1, (byte_pos + 1) % 8);
    }
    else
    {
        tree->offspring[bit_val] = makeTreeNode(c, 1);
    }
    return 0;
}
// Łączy 2 węzły drzewa w jeden
/*
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

// Tworzy pełne drzewo w oparciu o kolejkę
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
*/
static void printTabs(int level){
    for(int i = 0; i < level; i++)
        printf("\t");
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

    printTabs(level);
    printf("left:\n");
    printTreeRec(node->offspring[0], level+1);

    printTabs(level);
    printf("right:\n");
    printTreeRec(node->offspring[1], level+1);
}

// Inicjuje rekursywną funkcję wyświetlającą zawartość drzewa
void printTree(treeNode *root){
    printTreeRec(root, 0);
}

// Zwalnia pamięć
void freeTree(treeNode *root){
    if(root != NULL){
        freeTree(root->offspring[0]);
        freeTree(root->offspring[1]);
        free(root);
    }
}