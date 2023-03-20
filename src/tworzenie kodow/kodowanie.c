#include "kodowanie.h"
#include "stack.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void traverse(treeNode *root, stack_t* stack, char*** dict, int* index){
    if(root->left != NULL){
        put(stack, '0');
        traverse(root->left, stack, dict, index);
    }        
    if(root->right != NULL){
        put(stack, '1');
        traverse(root->right, stack, dict, index);
    }
    if(root->is_leaf){
        char str[2] = {root->c, '\0'};
        strcpy(dict[0][*index], str);
        dict[1][*index] = get_code(stack);
        *index++;
    }
}

void make_codes(treeNode *root, int code_num, char** dict[2]){
    int index = 0;  // Licznik kodów
    // Zainicjuj stos
    stack_t *stack = initialize_stack();
    if(stack == NULL){
        fprintf(stderr, "Error: no memory for making codes\n");
        return;
    }

    traverse(root, stack, dict, &index);
}
