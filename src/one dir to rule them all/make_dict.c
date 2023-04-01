// Plik zawiera funkcje tworzące słownik kodów na podstawie drzewa

#include "make_dict.h"
#include "stack.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Funkcja przechodzi rekurencyjnie po drzewie celem stworzenia kodów
static void traverse(treeNode *root, stack_t* stack, unsigned char*** dict, int* index){
    if(root->left != NULL){
        put(stack, '0');
        traverse(root->left, stack, dict, index);
    }        
    if(root->right != NULL){
        put(stack, '1');
        traverse(root->right, stack, dict, index);
    }
    if(root->is_leaf){  // Jeżeli wierzchołek jest liściem, dodaj symbol i kod do słownika
        get_char(root, dict, *index);
        get_code(stack, dict, *index);
        (*index)++;       
    }
    pop(stack);
}

// Funkcja inicjująca
unsigned char*** make_dict(treeNode *root, int code_num){
    int index = 0;  // Licznik kodów
    // Utwórz słownik
    char *** dict = malloc(2 * sizeof(char**));
    dict[0] = malloc(code_num * sizeof(char*));
    dict[1] = malloc(code_num * sizeof(char*));

    // Zainicjuj stos
    stack_t *stack = initialize_stack();
    if(stack == NULL){
        fprintf(stderr, "Error: no memory for making codes\n");
        return NULL;
    }

    traverse(root, stack, dict, &index);
    free_stack(stack);
    return dict;
}

// Zwalnia pamięć
void free_dict(char*** dict, int code_num){
    for(int i = 0; i < code_num; i++){
        free(dict[0][i]);
        free(dict[1][i]);
    }
    free(dict[0]);
    free(dict[1]);
    free(dict);
}