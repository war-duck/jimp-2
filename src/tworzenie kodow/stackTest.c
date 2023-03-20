#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    stack_t *stos = initialize_stack();
    put(stos, 1);
    put(stos, 2);
    put(stos, 3);
    put(stos, 4);
    put(stos, 5);

    put(stos, 5);
    put(stos, 5);
    put(stos, 5);
    put(stos, 5);
    put(stos, 5);

    put(stos, 5);
    put(stos, 5);
    put(stos, 5);
    put(stos, 5);
    put(stos, 5);

    put(stos, 6);
    put(stos, 7);
    for(int i = 0; i < 20; i++)
        printf("%d ", pop(stos));
    return 0;
}