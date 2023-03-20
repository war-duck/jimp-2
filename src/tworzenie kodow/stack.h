// Ten plik zawiera deklaracje stosu, potrzebnego do tworzenia kodów z drzewa binarnego
#ifndef STACK_H
#define STACK_H

typedef struct{
    int* vec;
    int size;
    int index;
} stack_t;

stack_t *initialize_stack();
void put(stack_t*, int);
int pop(stack_t*);

#endif