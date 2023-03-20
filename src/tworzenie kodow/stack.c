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
char* get_code(stack_t *stack){
    char* code = malloc((stack->index + 1) * sizeof *code);
    strcpy(code, stack->vec);
    code[stack->index + 1] = '\0';
    return code;
}

void free_stack(stack_t *stack){
    free(stack->vec);
    free(stack);
}