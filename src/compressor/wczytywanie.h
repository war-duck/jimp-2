#include <stdio.h>
#include <stdlib.h>

struct input_data_info
{
    unsigned char *data;   // Wskaźnik na wczytaną treść
    unsigned int *num;  // Liczba występowania poszczególnych bajtów
    unsigned long length;        // Długość pliku w bajtach. wsm nie jest nigdzie potrzebna, ale można przechować
    unsigned long BUFFER_SIZE;
};