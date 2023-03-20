// Ten plik zawiera deklaracje stosu, potrzebnego do tworzenia kodów z drzewa binarnego
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>

typedef struct{
    char* vec;
    size_t size;
    int index;
} stack_t;

stack_t *initialize_stack();
void put(stack_t*, char);
char pop(stack_t*);
char* get_code(stack_t*);
void free_stack(stack_t*);

#endif