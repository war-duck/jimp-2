// Ten kod poprawnie wczytuje bajty z pliku wejściowego i zapisuje je w wektorze unsigned char* c
// Kod można potem przekopiować (z dorbnymi edycjami) do większego programu

#include "wczytywanie.h"

unsigned long wczytaj(FILE* in, struct input_data_info* input){ // zwraca ilość wczytanych bajtów

    unsigned long i;
    unsigned long read;      // Aktualna ilość wczytanych bajtów (w tej iteracji)

    read = fread(input->data, sizeof(*input->data), input->BUFFER_SIZE, in);

    //printf("Wczytana tresc (tekstowa): %s\n", input->data);
    



    input->length += read;
    return read;
}

void licz (struct input_data_info* input, unsigned long length)
{
    
}