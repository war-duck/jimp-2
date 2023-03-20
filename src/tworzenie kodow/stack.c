// Ten plik zawiera implementację stosu

#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

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
    stack->vec = realloc(stack->size, stack->vec);
}

// Odkłada n na stos
void put(stack_t* stack, int n){
    if(stack->index == stack->size)
        resize_stack(stack);
    
    stack->vec[stack->index] = n;
    stack->index++;
}

// Zwraca element na górze stosu
int pop(stack_t* stack){
    if(stack->index == 0){
        fprintf(stderr, "Error: stack is empty.\n");
        return -1;
    }
    int tmp = stack->vec[stack->index];
    stack->index--;
    return tmp;
}