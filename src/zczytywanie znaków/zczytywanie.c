// Ten kod poprawnie zczytuje znaki z pliku wejściowego i zapisuje je w formie wektorów
// Kod można potem przekopiować (z dorbnymi edycjami) do większego programu

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

    int i;
    //int count[128] = {0}; // miejsce na każdy znak z tablicy ASCII
    int count[256] = {0};   // Często używane są znaki 8-bitowe
    char c;

    // Otwieranie pliku wejściowego
    FILE *in = fopen(argv[1], "r");
    if (in == NULL)
        return 1;

    while((c = fgetc(in)) && c != '\0' && c != EOF)
        count[c]++;
    
    // Wyświetl wyniki
    for(i = 0; i < 128; i++)
        printf("%d - %d\n", i, count[i]);

    return 0;
}