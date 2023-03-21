// Ten plik zawiera implementację stosu

#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Zwraca zainicjowany stos
stack_t *initialize_stack(){
    stack_t *stack = malloc(sizeof *stack);
    if(stack == NULL)
        return NULL;
    stack->index = 0;
    stack->size = 16;
    stack->vec = malloc(stack->size * sizeof *stack->vec);    
}

// Powiększa wielkość stosu o 16
static void resize_stack(stack_t* stack){
    stack->size += 16;
    stack->vec = realloc(stack->vec, stack->size * sizeof *stack->vec);
}

// Odkłada n na stos
void put(stack_t* stack, char c){
    if(stack->index == stack->size - 1)
        resize_stack(stack);
    
    stack->vec[stack->index++] = c;
}

// Zwraca element na górze stosu
char pop(stack_t* stack){
    if(stack->index == 0){
        fprintf(stderr, "Error: stack is empty.\n");
        return -1;
    }
    int tmp = stack->vec[stack->index];
    stack->index--;
    return tmp;
}

// Zwraca uzyskany kod
void get_code(stack_t *stack, char** dict[2], int index){
    printf("in: get_code %d\n", index);
    printf("index: %d\n", stack->index);
    dict[1][index] = malloc((stack->index + 1) * sizeof *dict[1][index]);
    printf("Allocated memory\n");
    //char* code = malloc((stack->index + 1) * sizeof *code);
    //strcpy(code, stack->vec);
    //strcpy(dict[1][index], code);
    //dict[1][index][stack->index + 1] = '\0';
    //free(code);
    printf("Coding: ");
    for(int i = 0; i < stack->index; i++){
        printf("%c", stack->vec[i]);
        dict[1][index][i] = stack->vec[i];
    }
    dict[1][index][stack->index] = '\0';
    printf("\nLength: %d\n", strlen(dict[1][index]));
    printf("out: get_code %d\n", index);
}

void free_stack(stack_t *stack){
    free(stack->vec);
    free(stack);
}