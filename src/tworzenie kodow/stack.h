// Ten plik zawiera deklaracje stosu, potrzebnego do tworzenia kodów z drzewa binarnego
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>

typedef struct{
    int* vec;
    size_t size;
    int index;
} stack_t;

stack_t *initialize_stack();
void put(stack_t*, int);
int pop(stack_t*);

#endif