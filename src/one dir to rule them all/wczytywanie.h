#ifndef WCZYTYWANIE_H
#define WCZYTYWANIE_H

#include <stdio.h>
#include <stdlib.h>

struct input_data_info
{
    unsigned char *data;   // Wskaźnik na wczytaną treść
    unsigned int *num;  // Liczba występowania poszczególnych bajtów
    unsigned long length;        // Długość pliku w bajtach
    unsigned long BUFFER_SIZE;
    unsigned long max_data_size;
};

unsigned long wczytaj(FILE* in, struct input_data_info* input);

#endif