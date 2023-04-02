// Ten plik zawiera implementację stosu

#include "stack.h"
#include <stdlib.h>

// Zwraca zainicjowany stos
stack_t *initialize_stack(){
    stack_t *stack = malloc(sizeof *stack);
    if(stack == NULL)
        return NULL;
    stack->index = 0;
    stack->size = 16;
    stack->vec = malloc(stack->size * sizeof *stack->vec);
    return stack;
}

// Powiększa wielkość stosu o 16
static void resize_stack(stack_t* stack){
    stack->size += 16;
    stack->vec = realloc(stack->vec, stack->size * sizeof *stack->vec);
}

// Odkłada 'c' na stos
void put(stack_t* stack, char c){
    if(stack->index == stack->size - 1)
        resize_stack(stack);
    
    stack->vec[stack->index++] = c;
}

// Zwraca element na górze stosu
char pop(stack_t* stack){
    if(stack->index == 0){
        return -1;
    }
    int tmp = stack->vec[stack->index];
    stack->index--;
    return tmp;
}

// Dopisuje kod do słownika
void get_code(stack_t *stack, unsigned char*** dict, int index){
    dict[1][index] = malloc((stack->index + 1) * sizeof *dict[1][index]);
    for(int i = 0; i < stack->index; i++){
        dict[1][index][i] = stack->vec[i];
    }
    dict[1][index][stack->index] = '\0';
}

// Zwalnia pamięć
void free_stack(stack_t *stack){
    free(stack->vec);
    free(stack);
}