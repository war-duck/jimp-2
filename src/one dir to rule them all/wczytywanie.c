/// Ten kod poprawnie wczytuje bajty z pliku wejściowego i zapisuje je w wektorze unsigned char* c
// Kod można potem przekopiować (z dorbnymi edycjami) do większego programu

#include "wczytywanie.h"

unsigned long wczytaj(FILE* in, struct input_data_info* input){ // zwraca ilość wczytanych bajtów

    unsigned long i;
    unsigned long read = 0;      // Aktualna ilość wczytanych bajtów (w tej iteracji)
    input->num = calloc(256, sizeof *input->num);

    read = fread(input->data, sizeof(*input->data), input->BUFFER_SIZE, in);
    if (read == 0)
        return read;
#ifdef DEBUG
    printf ("\nread: %ld\n", read);
    
    printf("\nWczytana tresc (tekstowa): %s\n", input->data);
#endif
    for(i = 0; i < read; i++)
        input->num[input->data[i]]++;    // Zlicz występowanie znaków

#ifdef DEBUG
    printf("\nCzestotliwosc wystepowania konkretnych bajtow:\n");
    for(i = 0; i < 256; i++)
        if (input->num[i])
            printf("%c - %d\n", (char)i, input->num[i]);
#endif
    input->length += read;
    return read;
}