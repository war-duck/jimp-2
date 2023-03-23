// Ten kod poprawnie wczytuje bajty z pliku wejściowego i zapisuje je w wektorze unsigned char* c
// Kod można potem przekopiować (z dorbnymi edycjami) do większego programu

#include <stdio.h>
#include <stdlib.h>
#include "wczytywanie.h"

#define BUFFOR_SIZE 52428800 // 50 MB
#define DEBUG
void wczytaj(FILE *in, unsigned char *c, unsigned int *num) {
    int i;
    long length;        // Długość pliku w bajtach
    long read = 0;      // Aktualna ilość wczytanych bajtów

    fseek(in, 0, SEEK_END);     // Ustaw wskaźnik na koniec pliku
    length = ftell(in);
#ifdef DEBUG   
    printf("Wielkosc pliku w bajtach: %d\n", length);   // Komunikat testowy
#endif
    fseek(in, 0, SEEK_SET);     // Ustaw wskaźnik z powrotem na początek pliku

    c = malloc(BUFFOR_SIZE * sizeof *c);  // Zaalokuj 50 MB pamięci
    num = calloc(256, sizeof *num);

    // Przeczytaj treść
    while(read != length){
        if((length - read) > BUFFOR_SIZE){
            read += fread(c, sizeof(*c), BUFFOR_SIZE, in);
            for(i = 0; i < BUFFOR_SIZE; i++)
                num[c[i]]++;    // Zlicz występowanie znaków
        }
        else{
            read += fread(c, sizeof(*c), (length - read), in);
            for(i = 0; i < (length - read); i++)
                num[c[i]]++;    // Zlicz występowanie znaków
        }
    }

#ifdef DEBUG
    printf("Liczba odczytanych bajtow: %d\n", read);
    printf("Czestotliwosc wystepowania konkretnych bajtow:\n");
    for(i = 0; i < 256; i++)
        printf("%x - %d\n", i, num[i]);
#endif
}