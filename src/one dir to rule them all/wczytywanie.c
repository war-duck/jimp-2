// Ten kod poprawnie wczytuje bajty z pliku wejściowego i zapisuje je w wektorze unsigned char* c
// Kod można potem przekopiować (z dorbnymi edycjami) do większego programu

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

    int i;
    unsigned char *c;
    unsigned int *num;  // Liczba występowania poszczególnych bajtów
    long length;        // Długość pliku w bajtach

    // Otwieranie pliku wejściowego
    FILE *in = fopen(argv[1], "rb");
    if (in == NULL)
        return 1;

    fseek(in, 0, SEEK_END);     // Ustaw wskaźnik na koniec pliku
    length = ftell(in);         
    printf("Wielkosc pliku w bajtach: %d\n", length);   // Komunikat testowy
    fseek(in, 0, SEEK_SET);     // Ustaw wskaźnik z powrotem na początek pliku

    c = malloc(length * sizeof(*c));
    size_t liczba_odczyt = fread(c, sizeof(*c), length, in);   // Wczytaj treść pliku

    printf("Liczba odczytanych bajtów: %d\n", liczba_odczyt);
    printf("Wczytana tresc (tekstowa): %s\n", c);

    num = calloc(256, sizeof *num);

    // Policz występowanie poszczególnych bajtów
    for(i = 0; i < length; i++){
        num[c[i]]++;
    }

    printf("Czestotliwosc wystepowania konkretnych bajtow:\n");
    for(i = 0; i < 256; i++)
        printf("%x - %d\n", i, i, num[i]);
    
    free(c);
    free(num);
    fclose(in);

    return 0;
}